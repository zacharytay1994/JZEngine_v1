/*	__FILE HEADER__
*	File:	Application.cpp
	Author: JZ
	Date:	19/06/21
	Brief:	Defines an application class that runs the engine editor.
			See Application.h for more information on the class.	
*/

#include <PCH.h>
#include "Application.h"
#include "EngineConfig.h"
#include "ECS/ECSconfig.h"
#include "DebugTools/Log.h"
#include "Scripting/MonoCSharp.h"

#include <iostream>
#include <tuple>

#define UNREFERENCED_PARAMETER(P)(P)

#include <memory>
#include <unordered_map>
#include <string>

namespace JZEngine
{
	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		ecs_instance_(new ECS::ECSInstance),
		engine_gui_(gl_instance_.window_, ecs_instance_)
	{
		Log::Instance().Initialize(engine_gui_.GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{} [MEM LEAKS BEGONE]", Settings::engine_name, Settings::version);
	}

	void Application::Free()
	{
		Log::Instance().Free();
		delete ecs_instance_;
	}

	void Application::Run()
	{
		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			gl_instance_.Draw ();

			engine_gui_.Update();
			
			ecs_instance_->Update();

			gl_instance_.FrameEnd();
		}
	}
}
