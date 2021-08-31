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
#include "DebugTools/Log.h"

#include <iostream>
#include <tuple>

#define UNREFERENCED_PARAMETER(P)(P)

namespace JZEngine
{
	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		engine_gui_(gl_instance_.window_)
	{
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
	}

	void Application::Run()
	{
		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			engine_gui_.Update();
			ECS::ECSInstance::Instance().Update();

			gl_instance_.FrameEnd();
		}
	}
}
