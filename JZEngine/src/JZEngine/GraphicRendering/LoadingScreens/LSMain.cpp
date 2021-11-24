/*	__FILE HEADER__
*	File:		LSMain.cpp
	Primary:	Jee Jia Min
	Date:		24/11/21
	Brief:		Jump Zero loading screen during the startup of the engine .
*/

#include "PCH.h"
#include "LSMain.h"
#include "../OpenGLDebug.h"
#include "../../JZGL/JZ_GL.h"
#include "../../EngineConfig.h"

namespace JZEngine
{
	LSMain::LSMain ()
		:
		ib ( indices.data () , static_cast < unsigned int > ( indices.size () ) ) ,
		vb ( vertices.data () , static_cast< unsigned int > ( vertices.size () * sizeof ( float ) ) )
	{
#ifdef LSMainDebug
		std::cout << "LSMain() " << std::endl;
#endif
	}

	LSMain::~LSMain ()
	{
#ifdef LSMainDebug
		std::cout << "~LSMain() " << std::endl;
#endif
	}

	void LSMain::PreDraw ()
	{
		std::cout << "LSMain::Draw() " << std::endl;

		VertexBufferLayout layout;
		layout.Push<float> ( 3 );
		layout.Push<float> ( 2 );
		va.AddBuffer ( vb , layout );
		ib.Bind ();

		glCheckError ();

		//  build and compile our shader program
		shader_program.CompileShaderFromFile ( GL_VERTEX_SHADER , vspath );
		shader_program.CompileShaderFromFile ( GL_FRAGMENT_SHADER , fspath );
		shader_program.Link ();

#ifdef LSMainDebug
		shader_program.ActiveUniformsList ();
#endif

		if( GL_FALSE == shader_program.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}
		shader_program.Bind ();

		// load and create a texture
		tex2d_path1.Texture2DLoad ( texpath1 );
		tex2d_path1.InitOpenGL ();
		tex2d_path2.Texture2DLoad ( texpath2 );
		tex2d_path2.InitOpenGL ();

		// make full viewport size
		glViewport ( 0 , 0 , Settings::window_width , Settings::window_height );
	}

	void LSMain::Draw ()
	{
		glCheckError ();
		glClearColor ( 0.5f , 0.5f , 0.5f , 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT );

		tex2d_path1.Bind ();
		shader_program.SetUniform ( "myAlpha" , 1.0f );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		myAlpha += 0.005;

		tex2d_path2.Bind ();
		shader_program.SetUniform ( "myAlpha" , abs ( sin ( myAlpha ) ) );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		//glfw: swap buffersand poll IO events.
		glfwSwapBuffers ( GLFW_Instance::window_ );
		glfwPollEvents ();
	}

	void LSMain::PostDraw ()
	{
		// reset viewport : make sure the viewport matches the new window dimensions
		glViewport ( static_cast< GLsizei >( 1.0 / 6.0 * Settings::window_width ) ,
					 static_cast< GLsizei >( 1.0 / 4.0 * Settings::window_height ) ,
					 static_cast< GLsizei >( 4.0 / 6.0 * Settings::window_width ) ,
					 static_cast< GLsizei >( 35.0 / 46.0 * Settings::window_height ) );

		// unbinding data
		va.Unbind ();
		ib.Unbind ();
		shader_program.Unbind ();
		tex2d_path1.Unbind ();
		tex2d_path2.Unbind ();
	}
}