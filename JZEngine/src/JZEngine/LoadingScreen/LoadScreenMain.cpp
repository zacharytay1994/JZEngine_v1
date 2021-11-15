#include "PCH.h"
#include "LoadScreenMain.h"
#include <math.h>
#include "../JZGL/JZ_GL.h"
#include "../EngineConfig.h"
#include "../GraphicRendering/OpenGLDebug.h"


namespace JZEngine
{
	LoadScreenMain::LoadScreenMain ()
		:
		ib ( indices.data () , static_cast < unsigned int > ( indices.size () ) ) ,
		vb ( vertices.data () , static_cast< unsigned int >( vertices.size () * sizeof ( float ) ) )
	{}

	void LoadScreenMain::Draw ()
	{

		VertexBufferLayout layout;
		layout.Push<float> ( 3 );
		layout.Push<float> ( 2 );
		va.AddBuffer ( vb , layout );
		ib.Bind ();

		//  build and compile our shader program
		shader_program.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader_program.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader_program.Link ();
		shader_program.ActiveUniformsList ();
		if( GL_FALSE == shader_program.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}
		shader_program.Bind ();

		// load and create a texture
		tex2d_path1.Texture2DLoad ( texpath1 );
		tex2d_path2.Texture2DLoad ( texpath2 );

		// make full viewport size
		glViewport ( 0 , 0 , Settings::window_width , Settings::window_height );

		glCheckError ();

		float myAlpha{ 0.0f };

		// render loop
		while( DrawLoadScreenMain )
		{
			glClearColor ( 0.5f , 0.5f , 0.5f , 1.0f );
			glClear ( GL_COLOR_BUFFER_BIT );

			tex2d_path1.Bind ();
			shader_program.SetUniform ( "myAlpha" , 1.0f );
			glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

			myAlpha += 0.001;

			tex2d_path2.Bind ();
			shader_program.SetUniform ( "myAlpha" , abs ( sin ( myAlpha ) ) );
			glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );


			// glfw: swap buffers and poll IO events.
			glfwSwapBuffers ( GLFW_Instance::window_ );
			glfwPollEvents ();

		}

		// reset viewport : make sure the viewport matches the new window dimensions
		glViewport ( static_cast< GLsizei >( 1.0 / 6.0 * Settings::window_width ) , static_cast< GLsizei >( 1.0 / 4.0 * Settings::window_height ) , static_cast< GLsizei >( 4.0 / 6.0 * Settings::window_width ) , static_cast< GLsizei >( 35.0 / 46.0 * Settings::window_height ) );


		va.Unbind ();
		ib.Unbind ();
		shader_program.Unbind ();
		tex2d_path1.Unbind ();
		tex2d_path2.Unbind ();

	}

}
