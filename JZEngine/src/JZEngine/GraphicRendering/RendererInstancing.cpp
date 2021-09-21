#include <PCH.h>
#include "RendererInstancing.h"
#include "../Math/JZMath.h"
#include "VertexBufferLayout.h"


namespace JZEngine
{
	JZEngine::Vec2f translations[100];

	RendererInstancing::RendererInstancing()
		:
		instance_vb( sizeof( JZEngine::Vec2f )* MAX_BUFFER_TRANSFORMS )
	{}

	void RendererInstancing::Init()
	{
		VertexBuffer vb( vertices.data(), static_cast< unsigned int >( vertices.size() * sizeof( float ) ) );

		VertexBufferLayout layout;
		layout.Push<float>( 2 );
		layout.Push<float>( 2 );
		va.AddBuffer( vb, layout );

		// also set instance data
		VertexBufferLayout instance_layout;
		// this attribute comes from a different vertex buffer
		instance_layout.Push<float>( 2 );
		/*instance_layout.Push<float>( 3 );
		instance_layout.Push<float>( 3 );*/
		va.AddBuffer( 2, instance_vb, instance_layout );
		// what makes this code interesting is the last line where we call glVertexAttribDivisor.
		glVertexAttribDivisor( 2, 1 ); // tell OpenGL this is an instanced vertex attribute.
		/*glVertexAttribDivisor( 4, 1 );
		glVertexAttribDivisor( 5, 1 );*/

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
		AddTransform( 0, 0, { 0.5f, 0.0f } );
		AddTransform( 0, 0, { 0.2f, -0.4f } );
		translations[0] = { 0.5f, 0.0f };
		Bind();
		for ( auto& gp : geometry_packets_ )
		{
			GeometryPacket& geometry = gp.second;
			// bind transforms MAX_BUFFER_TRANSFORMS at a time
			for ( int start = 0; start < geometry.transforms_.size(); start += MAX_BUFFER_TRANSFORMS )
			{
				assert( start < geometry.transforms_.size() );
				int size = std::min( MAX_BUFFER_TRANSFORMS, static_cast< unsigned int >( geometry.transforms_.size() - start ) );
				instance_vb.SetData( geometry.transforms_.data() + start, size * sizeof( JZEngine::Vec2f ) );
				glDrawArraysInstanced( GL_TRIANGLES, 0, 6, size ); // 100 triangles of 6 vertices each
			}
		}
		instance_vb.Unbind();
		Unbind();
		for ( auto& gp : geometry_packets_ )
		{
			gp.second.ClearTransforms();
		}
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

	void RendererInstancing::AddTransform( int shader, int texture, const JZEngine::Vec2f& transform )
	{
		geometry_packets_[{shader, texture}].AddTransform( transform );
	}
}