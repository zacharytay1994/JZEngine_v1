#include <PCH.h>
#include "Renderer.h"

#include <glad/glad.h>

namespace JZEngine
{
	Renderer::Renderer()
		:
		ib( indices.data(), static_cast < unsigned int > ( indices.size() ) )
	{};

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

		shader_program.CompileShaderFromFile( GL_VERTEX_SHADER, "Assets/Shaders/Vertex/VertexShader_Color_Testing.vs" );
		shader_program.CompileShaderFromFile( GL_FRAGMENT_SHADER, "Assets/Shaders/Fragment/FragmentShader_Color_Testing.fs" );
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
		shader_program.Bind();
	}

	void Renderer::Unbind()
	{
		va.Unbind();
		ib.Unbind();
		shader_program.Unbind();
	}

	Shader Renderer::GetShaderProgram()
	{
		return shader_program;
	}
}
