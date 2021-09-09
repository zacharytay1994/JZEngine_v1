#include <PCH.h>
#include <glad/glad.h>

#include "Renderer.h"
#include "OpenGLDebug.h"

namespace JZEngine
{

	/*const char* vertexShaderSource = "#version 450 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec3 vPos;"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	vPos = aPos;"
		"}\0";
	const char* fragmentShaderSource = "#version 450 core\n"
		"out vec4 FragColor;\n"
		"in vec3 vPos;"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vPos,1.0f);\n"
		"}\n\0";*/



	Renderer::Renderer ()
		:
		ib ( indices , 6 ) ,
		vb ( vertices , sizeof ( vertices ))
	{}

	void Renderer::Init ()
	{
		VertexBufferLayout layout ;
		layout.Push<float> ( 3 );
		va.AddBuffer ( vb , layout );
		va.Unbind ();
		vb.Unbind ();
		ib.Unbind ();

		shader_program.CompileShaderFromFile ( GL_VERTEX_SHADER , "Assets/Shaders/Vertex/VertexShader_Color_Testing.vs" );
		shader_program.CompileShaderFromFile ( GL_FRAGMENT_SHADER , "Assets/Shaders/Fragment/FragmentShader_Color_Testing.fs" );
		shader_program.Link ();

		if( GL_FALSE == shader_program.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}
	}

	void Renderer::Draw ()
	{
		Bind ( va , ib , shader_program );
	}

	void Renderer::Clear ()
	{
		glClear ( GL_COLOR_BUFFER_BIT ) ;
	}

	void Renderer::Bind ( const VertexArray& va , const IndexBuffer& ib , const Shader& shader ) const
	{
		va.Bind ();
		ib.Bind ();
		shader.Bind ();
		glDrawElements ( GL_TRIANGLES , ib.GetCount () , GL_UNSIGNED_INT , 0 );
	}

}
