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
#include "ECS/testecs.h"
#include "STL/Tuple.h"

#include <iostream>
#include <tuple>

#define UNREFERENCED_PARAMETER(P)(P)

namespace JZEngine
{
	ECS::Entity entity;

	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		engine_gui_(gl_instance_.window_)
	{
		std::stringstream ss;
		ss << "[" << Settings::engine_name << "] Up and Running! v%.1f";
		Console::Log(ss.str().c_str(), 1.0f);
		entity = ECS::ECSInstance::Instance().CreateEntity();

		ECS::Entity& e0 = ECS::ECSInstance::Instance().CreateEntity();
		ECS::ECSInstance::Instance().CreateEntity(e0.entity_id_);

		//entity.AddSystem(0);
		ECS::ECSInstance::Instance().Print();
	}

	void Application::Run()
	{
		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			engine_gui_.Update(entity);
			ECS::ECSInstance::Instance().Update();

			gl_instance_.FrameEnd();
		}
	}
}
