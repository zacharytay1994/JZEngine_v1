/*	__FILE HEADER__
*	File:	Application.cpp
	Author: JZ
	Date:	19/06/21
	Brief:	Defines an application class that runs the engine editor.
			See Application.h for more information on the class.	
*/

#include "PCH.h"
#include "Application.h"
#include "ECS/testecs.h"

#include <iostream>

#define UNREFERENCED_PARAMETER(P)(P)

namespace JZEngine
{
	Application::Application()
		:
		gl_instance_(800,600),
		tools_gui_(gl_instance_.window_)
	{
		ECS::ECSInstance::Instance().RegisterSystem<TestSystem>();
		ECS::ECSInstance::Instance().RegisterSystem<TestSystem2>();

		ECS::Entity entity;
		entity.AddSystems<TestSystem2>();
		entity.GetComponent<TestComponent>().x = 45;

		ECS::Entity entity2;
		entity2.AddSystems<TestSystem2>();
		entity2.AddSystem<TestSystem>();

		ECS::Entity entity3;
		entity3.AddSystems<TestSystem, TestSystem2>();

		entity.AddComponent<TestComponent2>();

		ECS::ECSInstance::Instance().Print();
	}

	void Application::Run()
	{
		std::cout << "ENGINE UP AND RUNNING!" << std::endl;

		while (gl_instance_.Active())
		{
			gl_instance_.FrameStart();

			tools_gui_.Update();
			ECS::ECSInstance::Instance().Update();

			gl_instance_.FrameEnd();
		}
	}
}
