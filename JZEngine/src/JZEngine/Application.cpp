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
#include "Sound/Sound.h"
#include "GraphicRendering/Renderer.h"
#include "GraphicRendering/SpriteRenderer.h"
#include "Input/Input.h"
#include "Input/DeltaTime.h"

#include "STL/Tuple.h"
#include <iostream>
#include <tuple>


#define UNREFERENCED_PARAMETER(P)(P)

#include <memory>
#include <unordered_map>
#include <string>

namespace JZEngine
{
	SoundSystem testsystem;

	//SpriteRenderer sprite;//
	//SpriteRenderer sprite2;

	Application::Application()
		:
		global_systems_(new GlobalSystemsManager())
	{
		global_systems_->AddSystem<GLFW_Instance>(Settings::window_width, Settings::window_height);
		global_systems_->AddSystem<ResourceManager>();
		global_systems_->AddSystem<ECS::ECSInstance>();
		global_systems_->AddSystem<Renderer>();
		global_systems_->AddSystem<EngineGUI>(global_systems_->GetSystem<GLFW_Instance>()->window_,
			global_systems_->GetSystem<ECS::ECSInstance>(),
			global_systems_->GetSystem<ResourceManager>());
		global_systems_->AddSystem<SoundSystem>();

		Log::Instance().Initialize(global_systems_->GetSystem<EngineGUI>()->GetConsole() );
		JZEngine::Log::Info( "Main", "[{}] Up and Running! v{} [MEM LEAKS BEGONE]", Settings::engine_name, Settings::version );

		//testsystem.initialize();
		global_systems_->Init();
		//renderer_->Init();

		global_systems_->GetSystem<ECS::ECSInstance>()->GetSystemInefficient<Sprite>()->sprite_renderer_.renderer_ = global_systems_->GetSystem<Renderer>();
		global_systems_->GetSystem<SoundSystem>()->createSound("testsound", "../JZEngine/Resources/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");
		global_systems_->GetSystem<SoundSystem>()->playSound("testsound", true, 0.4f);
		global_systems_->GetSystem<SoundSystem>()->setChannelGroupVolume(1.0f,"main");
		InputHandler::IsMousePressed(MOUSEBUTTON::MOUSE_BUTTON_LEFT);

		ECS::ECSInstance* ecs = global_systems_->GetSystem<ECS::ECSInstance>();
		/*for (int i = 0; i < 1000; ++i)
		{
			if (i == 255)
			{
				int j = 0;
			}
			int e = ecs->CreateEntity();
			ECS::Entity& entity = ecs->entity_manager_.GetEntity(e);
			entity.AddComponent<TestComponent2>();
		}
		for (int i = 0; i < 5000; ++i)
		{
			int e = ecs->CreateEntity();
			ECS::Entity& entity = ecs->entity_manager_.GetEntity(e);
			entity.AddComponent<TestComponent3>();
		}*/
	}

	void Application::Free()
	{
		Log::Instance().Free();
		global_systems_->Free();
		delete global_systems_;
	}

	void Application::Run()
	{
		while ( global_systems_->GetSystem<GLFW_Instance>()->Active() )
		{
			global_systems_->FrameStart();
			global_systems_->Update(1.0);

			//testsystem.updateSoundSystem();
			DeltaTime::update_time(1.0);

			global_systems_->FrameEnd();
		}
	}
}
