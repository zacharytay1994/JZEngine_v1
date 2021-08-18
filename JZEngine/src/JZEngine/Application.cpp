/*	__FILE HEADER__
*	File:	Application.cpp
	Author: JZ
	Date:	19/06/21
	Brief:	Defines an application class that runs the engine editor.
			See Application.h for more information on the class.	
*/

#include "PCH.h"
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
		gl_instance_(800,600),
		tools_gui_(gl_instance_.window_)
	{
		/*ECS::ECSInstance::Instance().RegisterSystem<TestSystem>();
		ECS::ECSInstance::Instance().RegisterSystem<TestSystem2>();

		entity.AddSystems<TestSystem2>();
		entity.GetComponent<TestComponent>().x = 45;

		ECS::Entity entity2;
		entity2.AddSystems<TestSystem2>();
		entity2.AddSystem<TestSystem>();

		ECS::Entity entity3;
		entity3.AddSystems<TestSystem, TestSystem2>();

		entity.AddComponent<TestComponent2>();*/
		//std::cout << "com: " << ECS::ComponentManager::component_descriptions_<int>.bit_ << std::endl;
		entity.AddComponent<TestComponent>();
		entity.AddComponent<TestComponent3>();
		ECS::Entity entity2;
		entity2.AddComponent<TestComponent3>();

		auto y = Tuple::GetType<0, ECS::ECSConfig::Component>();
		std::cout << "tuple type: " << typeid(decltype(y)).name() << std::endl;
		std::cout << "entity ecs_id: " << entity2.ID() << std::endl;

		ECS::ECSInstance::Instance().Print();

		/*for (int i = 0; i < std::tuple_size<ECS::ECSConfig::Component>{}; ++i)
		{
			Tuple::LoopTuple(ECS::ECSConfig::Component(), i);
		}*/
	}

	void Application::Run()
	{
		std::cout << "ENGINE UP AND RUNNING!" << std::endl;
		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			tools_gui_.Update(entity);
			ECS::ECSInstance::Instance().Update();

			gl_instance_.FrameEnd();
		}
	}
}
