#include <PCH.h>
#include "RendererInstancing.h"
#include "../Math/JZMath.h"
#include "VertexBufferLayout.h"


namespace JZEngine
{
	JZEngine::Vec2f translations[100];

	RendererInstancing::RendererInstancing()
	{}

	void RendererInstancing::Init()
	{
		int index = 0;
		float offset = 0.1f;
		for ( int y = -10; y < 10; y += 2 )
		{
			for ( int x = -10; x < 10; x += 2 )
			{
				JZEngine::Vec2f translation;
				translation.x = ( float )x / 10.0f + offset;
				translation.y = ( float )y / 10.0f + offset;
				translations[index++] = translation;
			}
		}

		VertexBuffer instance_vb( &translations[0], sizeof( JZEngine::Vec2f ) * 100 );
		VertexBuffer vb( vertices.data(), static_cast< unsigned int >( vertices.size() * sizeof( float ) ) );
		VertexBufferLayout layout;
		layout.Push<float>( 2 );
		layout.Push<float>( 3 );
		va.AddBuffer( vb, layout );

		// also set instance data
		glEnableVertexAttribArray( 2 );
		glBindBuffer( GL_ARRAY_BUFFER, instance_vb.GetRendererId() ); // this attribute comes from a different vertex buffer
		glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), ( void* )0 );
		// what makes this code interesting is the last line where we call glVertexAttribDivisor.
		glVertexAttribDivisor( 2, 1 ); // tell OpenGL this is an instanced vertex attribute.
		va.Unbind();
		vb.Unbind();
		instance_vb.Unbind();

		shader_program.CompileShaderFromFile( GL_VERTEX_SHADER, "Assets/Shaders/Vertex/VertexShader_Instancing.vs" );
		shader_program.CompileShaderFromFile( GL_FRAGMENT_SHADER, "Assets/Shaders/Fragment/FragmentShader_Instancing.fs" );
		shader_program.Link();

		if ( GL_FALSE == shader_program.IsLinked() )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog() << std::endl;
			std::exit( EXIT_FAILURE );
		}
	}

	void RendererInstancing::Draw()
	{
		Bind();
		glDrawArraysInstanced( GL_TRIANGLES, 0, 6, 100 ); // 100 triangles of 6 vertices each
		Unbind();
	}

	void RendererInstancing::Bind()
	{
		va.Bind();
		shader_program.Bind();
	}

	void RendererInstancing::Unbind()
	{
		va.Unbind();
		shader_program.Unbind();
	}

	Shader RendererInstancing::GetShaderProgram()
	{
		return shader_program;
	}

}