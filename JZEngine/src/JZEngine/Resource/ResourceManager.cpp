#include <PCH.h>
#include "ResourceManager.h"

namespace JZEngine
{
	std::vector<ResourceManager::InstancedShaderID> ResourceManager::instanced_shader_programs_;
	std::vector<ResourceManager::ShaderID> ResourceManager::shader_programs_;
	std::vector<ResourceManager::DebugShader> ResourceManager::debug_shaders_;
	std::vector<ResourceManager::Texture2DID> ResourceManager::texture2ds_;
	ResourceManager::ResourceManager ()
	{
		//add below so existing code dont need edit hehe
		// load textures
		LoadTexture2D("TextFile", "Assets/Textures/textfileicon.png");	
		LoadTexture2D ( "Unicorn" , "Assets/Textures/cute-unicorn.png" );//1
		LoadTexture2D ( "Square" , "Assets/Textures/square.jpg" );
		LoadTexture2D ( "TempB1" , "Assets/Textures/TempBackground-01.png" );
		LoadTexture2D ( "TempB2" , "Assets/Textures/TempBackground-02.png" );
		LoadTexture2D ( "TempB3" , "Assets/Textures/TempBackground-03.png" );
		LoadTexture2D ( "TempB4" , "Assets/Textures/TempBackground-04.png" );
		LoadTexture2D("Circle", "Assets/Textures/circle.png");	//7
		LoadTexture2D("CircleRed", "Assets/Textures/circlered.png");	//8
		LoadTexture2D("Square", "Assets/Textures/squareblue.png");//9



		// load shaders
		LoadShader ( "Default" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_Tex.fs" );
		LoadShader ( "Red Tint" ,
					 "Assets/Shaders/Vertex/VS_Sprite2D.vs" ,
					 "Assets/Shaders/Fragment/FS_TexRedTint.fs" );

		// load debug shaders
		LoadDebugShader("Point2D",
						"Assets/Shaders/Vertex/VS_Point2D.vs",
						"Assets/Shaders/Fragment/FS_Point2D.fs");
		LoadDebugShader("Line2D",
						"Assets/Shaders/Vertex/VS_Line2D.vs",
						"Assets/Shaders/Fragment/FS_Line2D.fs");

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

	unsigned int ResourceManager::LoadDebugShader(const std::string& name, const std::string& vspath, const std::string& fspath)
	{
		debug_shaders_.emplace_back(static_cast<unsigned int>(debug_shaders_.size()), name);
		Shader& shader = debug_shaders_.back().shader_program_;
		shader.CompileShaderFromFile(GL_VERTEX_SHADER, vspath);
		shader.CompileShaderFromFile(GL_FRAGMENT_SHADER, fspath);
		shader.Link();

		if (GL_FALSE == shader.IsLinked())
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog() << std::endl;
			std::exit(EXIT_FAILURE);
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
}