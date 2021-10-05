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
#include "../DebugTools/Log.h"

namespace JZEngine
{
	GLFWwindow* GLFW_Instance::window_{ nullptr };
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

	void GLFW_Instance::Init()
	{
		Log::Info("Process", "[Global System] GLFW_Instance intitialized.");
	}

	void GLFW_Instance::FrameStart ()
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

	void GLFW_Instance::GetWindowPos(int& x, int& y)
	{
		if (window_)
		{
			glfwGetWindowPos(window_, &x, &y);
		}
	}

	void GLFW_Instance::SetWindowPos(int x, int y)
	{
		if (window_)
		{
			glfwSetWindowPos(window_, x, y);
		}
	}

	void GLFW_Instance::ResizeWindow(int width, int height)
	{
		if (window_)
		{
			glfwSetWindowSize(window_, width, height);
		}
	}

	void GLFW_Instance::Initialize ()
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
		window_ = glfwCreateWindow( Settings::window_width, Settings::window_height, JZEngine::Settings::engine_name.c_str(), NULL, NULL );
		if ( window_ == NULL )
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent( window_ );
		glfwSwapInterval(0);

		// test glad is working
		if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		// create opengl viewport
		glViewport( 0, 0, Settings::window_width, Settings::window_height);

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

		SetWindowPos(Settings::window_x, Settings::window_y);
	}

	void JZEngine::FramebufferSizeCallback( GLFWwindow* window, int width, int height )
	{
		UNREFERENCED_PARAMETER( window );
		UNREFERENCED_PARAMETER( window );
		glViewport( 0, 0, width, height );
		Settings::window_width = width;
		Settings::window_height = height;
	}
}