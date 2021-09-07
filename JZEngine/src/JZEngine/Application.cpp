/*	__FILE HEADER__
*	File:	Application.cpp
	Author: JZ
	Date:	19/06/21
	Brief:	Defines an application class that runs the engine editor.
			See Application.h for more information on the class.	
*/

#include "PCH.h"
#include "EngineConfig.h"
#include "Application.h"
#include "ECS/ECSconfig.h"
#include "STL/Tuple.h"

#include <iostream>
#include <tuple>

#define UNREFERENCED_PARAMETER(P)(P)

namespace JZEngine
{
	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		engine_gui_(gl_instance_.window_, &ecs_instance_)
	{
		std::stringstream ss;
		ss << "[" << Settings::engine_name << "] Up and Running! v%.1f";
		Console::Log(ss.str().c_str(), 1.0f);

		ecs_instance_.Print();
	}

	void Application::Run()
	{
		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			engine_gui_.Update();
			ecs_instance_.Update();

			gl_instance_.FrameEnd();
		}
	}
}
