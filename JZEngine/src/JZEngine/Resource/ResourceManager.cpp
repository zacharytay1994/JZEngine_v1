#include <PCH.h>
#include "ResourceManager.h"
#include "../EngineConfig.h"

namespace JZEngine
{
	ResourceManager::ResourceManager ()
	{
		// load textures
		LoadTexture2D ( "Unicorn" , "Assets/Textures/cute-unicorn.png" );
		LoadTexture2D ( "Square" , "Assets/Textures/square.jpg" );
		//LoadTexture2D ( "Bomb" , "Assets/Textures/Bomb.png" );
		LoadTexture2D ( "TempB1" , "Assets/Textures/TempBackground-01.png" );
		LoadTexture2D ( "TempB2" , "Assets/Textures/TempBackground-02.png" );
		LoadTexture2D ( "TempB3" , "Assets/Textures/TempBackground-03.png" );
		LoadTexture2D ( "TempB4" , "Assets/Textures/TempBackground-04.png" );

		// load shaders
		LoadShader ( "Default" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_Tex.fs" );
		LoadShader ( "Red Tint" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_TexRedTint.fs" );

		// load font shaders
		LoadFont ( "Assets/Fonts/Weather Sunday.otf" , 100 , "Font1" , "Assets/Shaders/Vertex/VS_Font.vs" , "Assets/Shaders/Fragment/FS_Font.fs" );

		// load instanced shaders
		LoadInstancedShader ( "Default" ,
							  "Assets/Shaders/Vertex/VS_Instancing.vs" ,
							  "Assets/Shaders/Fragment/FS_Instancing.fs" );
	}

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

	unsigned int ResourceManager::LoadTexture2D ( const std::string& name , const std::string& path )
	{
		texture2ds_.emplace_back ( static_cast< unsigned int >( texture2ds_.size () ) , name );
		Texture2D& texture = texture2ds_.back ().texture2d_;
		texture.Texture2DLoad ( path );

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

		JZEngine::Mat3f camwin_to_ndc_xform = { {2.0f / ( Settings::aspect_ratio * Settings::window_height ), 0.0f, 0.0f},
												{0.0f, 2.0f / Settings::window_height, 0.0f},
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
		FT_Set_Char_Size ( face , fontSize << 6 , fontSize << 6 , 96 , 96 );

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
				JZEngine::Vec2f ( face->glyph->bitmap.width, face->glyph->bitmap.rows ),
				JZEngine::Vec2f ( face->glyph->bitmap_left, face->glyph->bitmap_top ),
				face->glyph->advance.x
			};

			characters.insert ( std::pair<char , Character> ( c , character ) );
		}
		glBindTexture ( GL_TEXTURE_2D , 0 );
		// destroy FreeType once we're finished
		FT_Done_Face ( face );
		FT_Done_FreeType ( ft );
	}
}