#include <PCH.h>
#include "Renderer.h"

#include <glad/glad.h>

namespace JZEngine
{
	Renderer::Renderer(ResourceManager* rm)
		:
		ib(indices.data(), static_cast <unsigned int> (indices.size())),
		resource_manager_(rm)
	{
		// load all texture images
		textures_["unicorn"].Texture2DLoad("Assets/Textures/cute-unicorn.png");
	};

	void Renderer::Init()
	{
		VertexBuffer vb( vertices.data(), vertices.size() * sizeof( float ) );
		VertexBufferLayout layout;
		layout.Push<float>( 3 );
		layout.Push<float>( 3 );
		layout.Push<float>( 2 );
		va.AddBuffer( vb, layout );
		va.Unbind();
		vb.Unbind();
		ib.Unbind();

		shader_program.CompileShaderFromFile( GL_VERTEX_SHADER, "Assets/Shaders/Vertex/VertexShader_Tex.vs" );
		shader_program.CompileShaderFromFile( GL_FRAGMENT_SHADER, "Assets/Shaders/Fragment/FragmentShader_Tex.fs" );
		shader_program.Link();

		if ( GL_FALSE == shader_program.IsLinked() )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog() << std::endl;
			std::exit( EXIT_FAILURE );
		}
	}

	void Renderer::Draw()
	{
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		//glDrawElements( GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0 );
	}

	void Renderer::Clear()
	{
		glClear( GL_COLOR_BUFFER_BIT );
	}

	void Renderer::Bind()
	{
		va.Bind();
		ib.Bind();
		//shader_program.Bind();
	}

	void Renderer::Unbind()
	{
		va.Unbind();
		ib.Unbind();
		//shader_program.Unbind();
	}

	Shader& Renderer::GetShaderProgram(int shaderid)
	{
		return resource_manager_->shader_programs_[shaderid].shader_program_;
	}

	void Renderer::BindTexture(const std::string& name)
	{
		textures_[name].Bind();
	}
	
	void Renderer::BindTexture(int textureid)
	{
		resource_manager_->texture2ds_[textureid].texture2d_.Bind();
	}

	void Renderer::BindShader(int shaderid)
	{
		resource_manager_->shader_programs_[shaderid].shader_program_.Bind();
	}

	void Renderer::UnbindShader(int shaderid)
	{
		resource_manager_->shader_programs_[shaderid].shader_program_.Unbind();
	}

	/*std::unordered_map<std::string, Texture2D>* Renderer::GetTextures()
	{
		return &textures_;
	}*/
}
