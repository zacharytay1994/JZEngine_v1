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

#include <memory>
#include <unordered_map>
#include <string>

namespace JZEngine
{
	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		engine_gui_(gl_instance_.window_, &ecs_instance_)
	{
		Log::Instance().Initialize(engine_gui_.GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main2", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main1", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main21", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main11", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main211", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main111", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
		JZEngine::Log::Info("Main2111", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);
	}

	/*struct test
	{
		test()
			:
			data(std::make_shared<char[]>(1000))
		{

		}

		test& operator=(const test& rhs)
		{
			data = rhs.data;
			return *this;
		}

		std::shared_ptr<char[]> data{nullptr};
	};*/

	void Application::Run()
	{
		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			gl_instance_.Draw ();

			engine_gui_.Update();
			
			ecs_instance_.Update();

			gl_instance_.FrameEnd();

		}

		//std::unordered_map<std::string, test>* testmap = new std::unordered_map<std::string, test>();
		////(*testmap)["name"] = test();
		//delete testmap;

		Log::Instance().Free();
	}
}
