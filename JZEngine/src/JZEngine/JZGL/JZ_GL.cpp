/*	__FILE HEADER__
*	File:	JZ_GL.cpp
	Author: JZ
	Date:	01/07/21
	Brief:	Encapsulates all OpenGL initializations
			and updates using GLFW and glad.
*/

#include <PCH.h>
#include "JZ_GL.h"
#include "../Input/Input.h"
#include "../EngineConfig.h"
#include "../GraphicRendering/OpenGLDebug.h"

namespace JZEngine
{
	GLFW_Instance::GLFW_Instance( int width, int height )
		:
		window_width_( width ),
		window_height_( height )
	{
		Initialize();
	}

	GLFW_Instance::~GLFW_Instance()
	{
		glfwTerminate();
	}

	void GLFW_Instance::FrameStart()
	{
		glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
	}

	void GLFW_Instance::FrameEnd()
	{
		glfwPollEvents();
		glfwSwapBuffers( window_ );
	}

	bool GLFW_Instance::Active()
	{
		return !glfwWindowShouldClose( window_ );
	}

	void GLFW_Instance::Draw()
	{}

	void GLFW_Instance::Initialize()
	{
		glfwInit();
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#if defined(DEBUG) | defined(_DEBUG)
		// comment this line in a release build!
		glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, true );
#endif

		// create glfw window
		window_ = glfwCreateWindow( window_width_, window_height_, JZEngine::Settings::engine_name, NULL, NULL );
		if ( window_ == NULL )
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent( window_ );

		// test glad is working
		if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		// create opengl viewport
		glViewport( 0, 0, window_width_, window_height_ );

		// set resize window callback function
		glfwSetFramebufferSizeCallback( window_, FramebufferSizeCallback );


		if ( !InputHandler::init(window_))
		{
			std::cout << "Failed to initialize input handler" << std::endl;
		}
		



		int flags;
		// features of contexts can be detected via context flags
		glGetIntegerv( GL_CONTEXT_FLAGS, &flags );
		// check if the context is a debug context
		if ( flags & GL_CONTEXT_FLAG_DEBUG_BIT )
		{
			std::cout << "Debug Mode" << std::endl;
			EnableOpenGLDebugging();
		}

		// configure global opengl state
		// -----------------------------
		glCheckError();
		glEnable( GL_BLEND );
		glCheckError();
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glCheckError();
	}

	void JZEngine::FramebufferSizeCallback( GLFWwindow* window, int width, int height )
	{
		UNREFERENCED_PARAMETER( window );
		UNREFERENCED_PARAMETER( window );
		glViewport( 0, 0, width, height );
	}
}