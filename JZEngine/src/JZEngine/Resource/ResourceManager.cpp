#include <PCH.h>
#include "ResourceManager.h"

namespace JZEngine
{
	ResourceManager::ResourceManager()
	{
		// load textures
		LoadTexture2D("Unicorn", "Assets/Textures/cute-unicorn.png");
		LoadTexture2D("Square", "Assets/Textures/square.jpg");
		LoadTexture2D("Bomb", "Assets/Textures/Bomb.png");
		LoadTexture2D ( "TempB1" , "Assets/Textures/TempBackground-01.png" );
		LoadTexture2D ( "TempB2" , "Assets/Textures/TempBackground-02.png" );
		LoadTexture2D ( "TempB3" , "Assets/Textures/TempBackground-03.png" );
		LoadTexture2D ( "TempB4" , "Assets/Textures/TempBackground-04.png" );

		// load shaders
		LoadShader("Default", 
			"Assets/Shaders/Vertex/Sprite2D.vs", "Assets/Shaders/Fragment/TextureDefault.fs");
		LoadShader("Red Tint",
			"Assets/Shaders/Vertex/Sprite2D.vs", "Assets/Shaders/Fragment/TextureRedTint.fs");

		// load instanced shaders
		LoadInstancedShader( "Default",
					"Assets/Shaders/Vertex/VertexShader_Instancing.vs",
					"Assets/Shaders/Fragment/FragmentShader_Instancing.fs" );
	}

	unsigned int ResourceManager::LoadInstancedShader( const std::string& name, const std::string& vspath, const std::string& fspath )
	{
		instanced_shader_programs_.emplace_back( static_cast< unsigned int >( instanced_shader_programs_.size() ), name );
		Shader& shader = instanced_shader_programs_.back().shader_program_;
		shader.CompileShaderFromFile( GL_VERTEX_SHADER, vspath );
		shader.CompileShaderFromFile( GL_FRAGMENT_SHADER, fspath );
		shader.Link();

		if ( GL_FALSE == shader.IsLinked() )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader.GetLog() << std::endl;
			std::exit( EXIT_FAILURE );
		}

		return 1;
	}

	unsigned int ResourceManager::LoadShader(const std::string& name, const std::string& vspath, const std::string& fspath)
	{
		shader_programs_.emplace_back(static_cast<unsigned int>(shader_programs_.size()), name);
		Shader& shader = shader_programs_.back().shader_program_;
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

	unsigned int ResourceManager::LoadTexture2D(const std::string& name, const std::string& path)
	{
		texture2ds_.emplace_back(static_cast<unsigned int>(texture2ds_.size()), name);
		Texture2D& texture = texture2ds_.back().texture2d_;
		texture.Texture2DLoad(path);

		return 1;
	}
}