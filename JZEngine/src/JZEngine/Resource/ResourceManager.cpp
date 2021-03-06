/*	__FILE HEADER__
*	File:		ResourceManager.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Manages all external assets.
*/

#include <PCH.h>
#include "ResourceManager.h"
#include "../EngineConfig.h"
#include "../DebugTools/Log.h"

#include "../Threads/ThreadPool.h"

#include <atomic>

namespace JZEngine
{
	// one thread writes to an atomic object while another thread reads from it
	std::string thread_load_string;
	std::atomic<std::string*> thread_load_string_pointer = &thread_load_string;
	std::atomic<bool> thread_is_pool_done_ ( false );

	std::vector<ResourceManager::InstancedShaderID> ResourceManager::instanced_shader_programs_;
	std::vector<ResourceManager::ShaderID> ResourceManager::shader_programs_;
	std::vector<ResourceManager::DebugShader> ResourceManager::debug_shaders_;

	unsigned int ResourceManager::texture_unique_id_{ 0 };
	std::vector<ResourceManager::Texture2DID> ResourceManager::texture2ds_;
	std::unordered_map<std::string , int> ResourceManager::umap_texture2ds_;

	ResourceManager::FolderData ResourceManager::texture_folder_data_;
	std::unordered_map<std::string , std::vector<std::string>> ResourceManager::texture_folders_;

	ResourceManager::ResourceManager ()
		:
		load_screen_main_ ( this )
	{
		// intialised loading screen
		load_screen_main_.PreDraw ();

		// pooling on first initialization (singleton) and all tasks all tasks are performed on pool
		JZEngine::ThreadPool& pool_load_folder_tex = JZEngine::ThreadPool::Instance ();
		{
			pool_load_folder_tex.Parallel ( LoadAllTexturesInFolder , "Assets/Textures/" );
		}

		// calculate delta time
		double dt{ 0.0 };
		// draw loading screen if pool_load_folder_tex is not done yet
		while( !thread_is_pool_done_ )
		{
			auto start_time = std::chrono::high_resolution_clock::now ();
			// draw the loading screen and print out the intialised items 
			load_screen_main_.DrawLoadingScreen ( *thread_load_string_pointer, dt );
			// calculate delta time for this loading screen
			auto end_time = std::chrono::high_resolution_clock::now ();
			std::chrono::duration<double , std::milli> milli_dt = end_time - start_time;
			dt = milli_dt.count () / 1000.0;
		}

		// draw stagnent "NOW ENTERING" for frozen screen
		load_screen_main_.DrawExitScreen ();

		for( auto& tex : texture2ds_ )
		{	// initialised Opengl texture 
			tex.texture2d_.InitOpenGL ();
		}

		// load shaders
		LoadShader ( "Default" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_Tex.fs" );

		LoadShader ( "Black White" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_BlackWhite.fs" );

		LoadShader ( "Leaf Shader" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_TexSway.fs" );

		// load font shaders
		LoadFont ( "Assets/Fonts/Quicksand-SemiBold.ttf" , 100 , "Font1" , "Assets/Shaders/Vertex/VS_Font.vs" , "Assets/Shaders/Fragment/FS_Font.fs" );

		// load debug shaders
		LoadDebugShader ( "Point2D" ,
						  "Assets/Shaders/Vertex/VS_Point2D.vs" ,
						  "Assets/Shaders/Fragment/FS_Point2D.fs" );

		LoadDebugShader ( "Line2D" ,
						  "Assets/Shaders/Vertex/VS_Line2D.vs" ,
						  "Assets/Shaders/Fragment/FS_Line2D.fs" );

		// load instanced shaders
		LoadInstancedShader ( "Default" ,
							  "Assets/Shaders/Vertex/VS_Instancing.vs" ,
							  "Assets/Shaders/Fragment/FS_Instancing.fs" );

		texture_folder_data_.name_ = "Textures";

		// fade out "NOW ENTERING" loading screen
		load_screen_main_.DrawFadeOut ();
		
		// uninitialised loading screen
		load_screen_main_.PostDraw ();

		// exit thread
		pool_load_folder_tex.Free ();
	}

	void ResourceManager::PostInit ()
	{}

	unsigned int ResourceManager::LoadInstancedShader ( const std::string& name , const std::string& vspath , const std::string& fspath )
	{
		instanced_shader_programs_.emplace_back ( static_cast< unsigned int >( instanced_shader_programs_.size () ) , name );
		Shader& shader = instanced_shader_programs_.back ().shader_program_;
		shader.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader.Link ();

		if( GL_FALSE == shader.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}

		return 1;
	}

	unsigned int ResourceManager::LoadFontShader ( const std::string& name , const std::string& vspath , const std::string& fspath )
	{
		font_shader_programs_.emplace_back ( static_cast< unsigned int >( font_shader_programs_.size () ) , name );
		Shader& shader = font_shader_programs_.back ().shader_program_;
		shader.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader.Link ();

		if( GL_FALSE == shader.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}

		return 1;
	}

	unsigned int ResourceManager::LoadShader ( const std::string& name , const std::string& vspath , const std::string& fspath )
	{
		shader_programs_.emplace_back ( static_cast< unsigned int >( shader_programs_.size () ) , name );
		Shader& shader = shader_programs_.back ().shader_program_;
		shader.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader.Link ();

		if( GL_FALSE == shader.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}

		return 1;
	}

	unsigned int ResourceManager::LoadDebugShader ( const std::string& name , const std::string& vspath , const std::string& fspath )
	{
		debug_shaders_.emplace_back ( static_cast< unsigned int >( debug_shaders_.size () ) , name );
		Shader& shader = debug_shaders_.back ().shader_program_;
		shader.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader.Link ();

		if( GL_FALSE == shader.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}

		return 1;
	}

	void ResourceManager::LoadFont ( std::string font , unsigned int fontSize , const std::string& name , const std::string& vspath , const std::string& fspath )
	{
		font_shader_programs_.emplace_back ( static_cast< unsigned int >( font_shader_programs_.size () ) , name );
		Shader& shader = font_shader_programs_.back ().shader_program_;
		shader.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader.Link ();

		if( GL_FALSE == shader.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}

		shader.Bind ();

		JZEngine::Mat3f camwin_to_ndc_xform =
		{ {2.0f / ( Settings::aspect_ratio * Settings::window_height ), 0.0f, 0.0f},
		  {0.0f, -2.0f / Settings::window_height, 0.0f},
		  {0.0f, 0.0f, 1.0f} };

		shader.SetUniform ( "projection" , camwin_to_ndc_xform.Transpose () );


		shader.SetUniform ( "text" , 0 );
		//glCheckError ();

		// first clear the previously loaded Characters
		font_characters_.emplace_back ();
		auto& characters = font_characters_.back ();
		characters.clear ();

		// then initialize and load the FreeType library
		FT_Library ft;
		// all functions return a value different than 0 whenever an error occurred
		if( FT_Init_FreeType ( &ft ) )
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// load font as face 
		FT_Face face;
		// FT_Open_Face to open a font by its pathname
		// FT_New_Face ( Return : FreeType error code. 0~means success.)
		if( FT_New_Face ( ft , font.c_str () , 0 , &face ) )
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		//For some twisted reason, Freetype measures font size
		//in terms of 1/64ths of pixels.  Thus, to make a font
		//h pixels high, we need to request a size of h*64.
		//(h << 6 is just a prettier way of writting h*64)
		if( FT_Set_Char_Size ( face , fontSize << 6 , fontSize << 6 , 180 , 180 ) )
			std::cout << "ERROR::FREETYPE: Died on set char size function" << std::endl;


		// disable byte-alignment restriction
		glPixelStorei ( GL_UNPACK_ALIGNMENT , 1 );

		// then for the first 128 ASCII characters, pre-load/compile their characters and store them
		for( GLubyte c = 0; c < 128; c++ )
		{
			// load character glyph 
			if( FT_Load_Char ( face , c , FT_LOAD_RENDER ) )
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// generate texture
			unsigned int texture;
			glGenTextures ( 1 , &texture );
			glBindTexture ( GL_TEXTURE_2D , texture );
			glTexImage2D (
				GL_TEXTURE_2D ,
				0 ,
				GL_RED ,
				face->glyph->bitmap.width ,
				face->glyph->bitmap.rows ,
				0 ,
				GL_RED ,
				GL_UNSIGNED_BYTE ,
				face->glyph->bitmap.buffer
			);

			// set texture options
			glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE );
			glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE );
			glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
			glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );


			// now store character for later use
			Character character = {
				face,
				texture,
				JZEngine::Vec2f ( static_cast< float >( face->glyph->bitmap.width ),  static_cast< float >( face->glyph->bitmap.rows ) ),
				JZEngine::Vec2f ( static_cast< float >( face->glyph->bitmap_left ),  static_cast< float >( face->glyph->bitmap_top ) ),
				static_cast< unsigned int >( face->glyph->advance.x )
			};

			characters.insert ( std::pair<char , Character> ( c , character ) );
		}
		glBindTexture ( GL_TEXTURE_2D , 0 );
		// destroy FreeType once we're finished
		FT_Done_Face ( face );
		FT_Done_FreeType ( ft );
	}

	void ResourceManager::LoadAllTexturesInFolder ( const std::string& folder )
	{
		// check if folder exists else create it
		if( !std::filesystem::is_directory ( folder ) )
		{
			std::filesystem::create_directory ( folder );
		}

		texture_folder_data_ = ResourceManager::FolderData ();
		texture_folder_data_.path_ = "All Textures";
		texture_folder_data_.name_ = "Textures";
		texture_folders_ = std::unordered_map<std::string , std::vector<std::string>> ();
		RecursivelyLoadTexture ( folder , texture_folder_data_ );

		// informed loading screen to stop drawing after texture is done loaded
		thread_is_pool_done_ = true;
	}

	void ResourceManager::RecursivelyLoadTexture ( const std::string& folder , FolderData& folderData )
	{
		std::string path;
		std::string texture_name;
		std::unordered_map<std::string , bool> check;
		// create temp
		/*for (auto& c : umap_texture2ds_)
		{
			check[c.first] = false;
		}*/
		// read files
		Log::Info ( "Resources" , "\n Reading textures from {}:" , folder );
		for( const auto& file : std::filesystem::directory_iterator ( folder ) )
		{
			if( std::filesystem::is_directory ( file.path () ) )
			{
				folderData.folders_.emplace_back ();
				folderData.folders_.back ().path_ = file.path ().string ();
				folderData.folders_.back ().name_ = file.path ().filename ().string ();
				//texture_folders_[folderData.folders_.back().name_] = &folderData.files_;
				std::cout << file.path ().string () << std::endl;
				RecursivelyLoadTexture ( file.path ().string () , folderData.folders_.back () );
			}
			else
			{
				texture_name = file.path ().filename ().string ();
				texture_name = texture_name.substr ( 0 , texture_name.find_last_of ( '.' ) );
				std::cout << texture_name << std::endl;
				folderData.files_.emplace_back ( texture_name );
				texture_folders_[ folderData.name_ ].emplace_back ( texture_name );
				// check if texture not already loaded
				if( umap_texture2ds_.find ( texture_name ) == umap_texture2ds_.end () )
				{
					texture2ds_.emplace_back ( static_cast< int >( texture2ds_.size () ) );
					texture2ds_.back ().texture2d_.Texture2DLoad ( file.path ().string () );
					umap_texture2ds_[ texture_name ] = texture2ds_.back ().id_;
					//ThreadDataShare <std::string>::SaveTemperoryData ( texture_name );
					Log::Info ( "Resources" , "- Read [{}]." , file.path ().string () );
					*thread_load_string_pointer = file.path ().string ();
				}
				check[ texture_name ] = true;
			}
		}
	}

	Texture2D* ResourceManager::GetTexture ( int id )
	{
		if( id < texture2ds_.size () && id >= 0 )
		{
			return &texture2ds_[ id ].texture2d_;
		}
		return nullptr;
	}

	Texture2D* ResourceManager::GetTexture ( const std::string& name )
	{
		return GetTexture ( umap_texture2ds_[ name ] );
	}

	int ResourceManager::GetTextureID ( const std::string& name )
	{
		if( umap_texture2ds_.find ( name ) != umap_texture2ds_.end () )
		{
			return umap_texture2ds_[ name ];
		}
		Log::Warning ( "Warning" , "Getting texture that does not exist: {}." , name );
		return -1;
	}
}