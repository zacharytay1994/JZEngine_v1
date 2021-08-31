#include <PCH.h>
#include "Renderer.h"
#include "Shader.h"

namespace JZEngine
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	unsigned int shaderProgram;
	unsigned int VBO , VAO , EBO;
	Shader shader_program ;

	void Renderer::SetupVao ()
	{


		shader_program.CompileShaderFromString ( GL_VERTEX_SHADER , vertexShaderSource );
		shader_program.CompileShaderFromString ( GL_FRAGMENT_SHADER , fragmentShaderSource );
		shader_program.Link ();
		if( GL_FALSE == shader_program.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}


		/*set up vertex data ( and buffer ( s ) ) and configure vertex attributes
			------------------------------------------------------------------*/
		float vertices [] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices [] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		glGenVertexArrays ( 1 , &VAO );
		glGenBuffers ( 1 , &VBO );
		glGenBuffers ( 1 , &EBO );
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray ( VAO );

		glBindBuffer ( GL_ARRAY_BUFFER , VBO );
		glBufferData ( GL_ARRAY_BUFFER , sizeof ( vertices ) , vertices , GL_STATIC_DRAW );

		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , EBO );
		glBufferData ( GL_ELEMENT_ARRAY_BUFFER , sizeof ( indices ) , indices , GL_STATIC_DRAW );

		glVertexAttribPointer ( 0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof ( float ) , ( void* ) 0 );
		glEnableVertexAttribArray ( 0 );

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer ( GL_ARRAY_BUFFER , 0 );

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray ( 0 );


	}

	void Renderer::Draw ()
	{
		shader_program.Use ();

		glClear ( GL_COLOR_BUFFER_BIT );

		glBindVertexArray ( VAO ); 
		
		// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		glBindVertexArray ( 0 );

		shader_program.UnUse ();
	}
}
