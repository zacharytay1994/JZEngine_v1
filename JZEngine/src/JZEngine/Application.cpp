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
		ECS::Entity entity;
		entity.AddComponent<ECS::TestData2>();
		//entity.AddComponent<ECS::TestData2>();
		//entity.GetComponent<ECS::TestData>().x = 1;
		//TestSystem ts;
		/*TestSystem ts2;
		TestSystem2 ts3;*/
		ECS::Entity entity2;
		entity2.AddComponent<TestComponent, ECS::TestData2>();
		//entity2.GetComponent<ECS::TestData>().x = 2;
		entity.GetComponent<ECS::TestData2>().c = 'p';
		//std::cout << entity.GetComponent<ECS::TestData>().x << std::endl;
		std::cout << entity.GetComponent<ECS::TestData2>().c << std::endl;
		std::cout << entity2.GetComponent<TestComponent>().x << std::endl;
		std::cout << entity2.GetComponent<ECS::TestData2>().c << std::endl;

		ECS::ECSInstance::Instance().RegisterSystem<TestSystem>();
		ECS::ECSInstance::Instance().RegisterSystem<TestSystem>();
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
