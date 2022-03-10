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

#include "../Renderers/Renderer.h"

#include "../Renderers/RendererText.h"
#include "../../Resource/ResourceManager.h"

namespace JZEngine
{
	LSMain::LSMain ( ResourceManager* ResourceManager )
		:
		ib ( indices.data () , static_cast < unsigned int > ( indices.size () ) ) ,
		vb ( vertices.data () , static_cast< unsigned int > ( vertices.size () * sizeof ( float ) ) ) ,
		resource_manager_ ( ResourceManager ) ,
		renderer_text_ ( std::make_unique<TextRenderer> () )
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
#ifdef LSMainDebug
		std::cout << "LSMain::Draw() " << std::endl;
#endif

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
		tex2d_path3.Texture2DLoad ( texpath3 );
		tex2d_path3.InitOpenGL ();
		tex2d_path4.Texture2DLoad ( texpath4 );
		tex2d_path4.InitOpenGL ();

		// make full viewport size
		if ( GLFW_Instance::window_ )
		{
			glfwGetWindowSize ( GLFW_Instance::window_ , &window_width_ , &window_height_ );
			glViewport ( 0 , 0 , window_width_ , window_height_ );
		}

		// load font data
		resource_manager_->LoadFont ( "Assets/Fonts/arlrdbd.ttf" , 100 , "Font1" , "Assets/Shaders/Vertex/VS_Font.vs" , "Assets/Shaders/Fragment/FS_Font.fs" );
	}

	void LSMain::DrawLoadingScreen ( std::string Information , double DeltaTime )
	{
		if ( GLFW_Instance::window_ )
		{
			glfwGetWindowSize ( GLFW_Instance::window_ , &window_width_ , &window_height_ );
			glViewport ( 0 , 0 , window_width_ , window_height_ );
		}
		glCheckError ();
		glClearColor ( 0.0f , 0.0f , 0.0f , 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT );

		float loading_speed = 2.0f * (float)DeltaTime;

		if( !reverse_dot_ )
		{
			if( dot_2_alpha_ >= 1.0f )
			{
				if( dot_3_alpha_ >= 1.0f )
				{
					reverse_dot_ = true;
				}
				else
				{
					dot_3_alpha_ += loading_speed;
				}
			}
			else
			{
				dot_2_alpha_ += loading_speed;
			}
		}
		else
		{
			if( dot_3_alpha_ > 0.0f )
			{
				dot_3_alpha_ -= loading_speed;
			}
			else
			{
				if( dot_2_alpha_ > 0.0f )
				{
					dot_2_alpha_ -= loading_speed;
				}
				else
				{
					reverse_dot_ = false;
				}
			}
		}

		va.Bind ();
		ib.Bind ();
		shader_program.Bind ();

		tex2d_path1.Bind ();
		shader_program.SetUniform ( "myAlpha" , dot_1_alpha_ );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		tex2d_path2.Bind ();
		shader_program.SetUniform ( "myAlpha" , dot_2_alpha_ );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		tex2d_path3.Bind ();
		shader_program.SetUniform ( "myAlpha" , dot_3_alpha_ );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		/*if( resource_manager_ )
		{
			if( renderer_text_ )
			{
				renderer_text_->RenderText ( resource_manager_ , Information , 0 , -( Settings::window_height / 2.5f ) , 0.5 , { 1.0f , 1.0f , 1.0f } , 1.0f , 2.0f , Paragraph::AlignCenter );
			}
		}*/

		//glfw: swap buffersand poll IO events.
		glfwSwapBuffers ( GLFW_Instance::window_ );
		glfwPollEvents ();
	}

	void LSMain::DrawExitScreen ()
	{
		glCheckError ();
		glClearColor ( 0.0f , 0.0f , 0.0f , 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT );

		if ( GLFW_Instance::window_ )
		{
			glfwGetWindowSize ( GLFW_Instance::window_ , &window_width_ , &window_height_ );
			glViewport ( 0 , 0 , window_width_ , window_height_ );
		}

		va.Bind ();
		ib.Bind ();
		shader_program.Bind ();

		tex2d_path4.Bind ();
		shader_program.SetUniform ( "myAlpha" , 1.0f );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

		//glfw: swap buffersand poll IO events.
		glfwSwapBuffers ( GLFW_Instance::window_ );
		glfwPollEvents ();
	}

	void LSMain::DrawFadeOut ()
	{
		// slow fade out 
		for( float i = 1.0f; i > 0.0f ; i -= 0.005f )
		{
			glCheckError ();
			glClearColor ( 0.0f , 0.0f , 0.0f , 1.0f );
			glClear ( GL_COLOR_BUFFER_BIT );

			if ( GLFW_Instance::window_ )
			{
				glfwGetWindowSize ( GLFW_Instance::window_ , &window_width_ , &window_height_ );
				glViewport ( 0 , 0 , window_width_ , window_height_ );
			}

			va.Bind ();
			ib.Bind ();
			shader_program.Bind ();

			tex2d_path4.Bind ();
			shader_program.SetUniform ( "myAlpha" , i );
			glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );

			//glfw: swap buffersand poll IO events.
			glfwSwapBuffers ( GLFW_Instance::window_ );
			glfwPollEvents ();
		}
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
		tex2d_path3.Unbind ();
		tex2d_path4.Unbind ();
	}
}