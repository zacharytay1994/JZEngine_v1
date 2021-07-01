/*	__FILE HEADER__
*	File:	Application.cpp
	Author: JZ
	Date:	19/06/21
	Brief:	Defines an application class that runs the engine editor.
			See Application.h for more information on the class.	
*/

#include "PCH.h"
#include "Application.h"

#include <iostream>

#define UNREFERENCED_PARAMETER(P)(P)

namespace JZEngine
{
	Application::Application()
		:
		gl_instance_(800,600),
		tools_gui_(gl_instance_.window_)
	{
	}

	void Application::Run()
	{
		std::cout << "ENGINE UP AND RUNNING!" << std::endl;

		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			tools_gui_.Update();

			gl_instance_.FrameEnd();
		}
	}
}
