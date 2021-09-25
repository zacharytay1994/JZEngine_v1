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
#include "GraphicRendering/RendererInstancing.h"
#include "Input/Input.h"
#include "Input/DeltaTime.h"

#include "STL/Random.h"
#include "STL/Tuple.h"
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
		global_systems_(new GlobalSystemsManager())
	{
		// add and initialize global systems
		global_systems_->AddSystem<GLFW_Instance>(Settings::window_width, Settings::window_height);
		global_systems_->AddSystem<ResourceManager>();
		global_systems_->AddSystem<ECS::ECSInstance>();
		global_systems_->AddSystem<Renderer>();
		global_systems_->AddSystem<RendererInstancing>();
		global_systems_->AddSystem<EngineGUI>();
		global_systems_->AddSystem<SoundSystem>();

		// give subsystems handle to global systems
		global_systems_->GetSystem<ECS::ECSInstance>()->GetSystemInefficient<Sprite>()->sprite_renderer_.renderer_ = global_systems_->GetSystem<Renderer>();
		global_systems_->GetSystem<ECS::ECSInstance>()->GetSystemInefficient<InstanceSprite>()->sprite_renderer_instancing_.renderer_ = global_systems_->GetSystem<RendererInstancing>();

		// give singleton logger handle to the engine console
		Log::Instance().Initialize(global_systems_->GetSystem<EngineGUI>()->GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);

		// test code
		/*global_systems_->GetSystem<SoundSystem>()->createSound("testsound", "../JZEngine/Resources/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");
		global_systems_->GetSystem<SoundSystem>()->playSound("testsound", true, 0.4f);
		global_systems_->GetSystem<SoundSystem>()->setChannelGroupVolume(1.0f, "main");
		InputHandler::IsMousePressed(MOUSEBUTTON::MOUSE_BUTTON_LEFT);*/

		/*ECS::ECSInstance* ecs = global_systems_->GetSystem<ECS::ECSInstance>();
		for (int i = 0; i < 5000; ++i) {
			int id = ecs->CreateEntity();
			ECS::Entity& entity = ecs->entity_manager_.GetEntity(id);
			entity.AddSystem(1);
			entity.AddComponent<IsUnicorn>();
			float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			entity.GetComponent<Transform>().position_ = { x * 800.0f, y * 800.0f };
		}
		for (int i = 0; i < 5000; ++i) {
			int id = ecs->CreateEntity();
			ECS::Entity& entity = ecs->entity_manager_.GetEntity(id);
			entity.AddSystem(1);
			float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			entity.GetComponent<Transform>().position_ = { x * -800.0f, y * -800.0f };
			entity.GetComponent<Texture>().texture_id_ = 1;
		}*/

		ECS::ECSInstance* ecs = global_systems_->GetSystem<ECS::ECSInstance>();
		int id = ecs->CreateEntity();
		ECS::Entity& entity = ecs->entity_manager_.GetEntity(id);
		entity.AddSystem(0);
		entity.AddComponent<PhysicsComponent>();
		entity.GetComponent<Texture>().texture_id_ = 1;
		entity.GetComponent<PhysicsComponent>().shapeid = 1;
		entity.GetComponent<Transform>().size_.x = 800;
		entity.GetComponent<Transform>().position_.y = -200;

		id = ecs->CreateEntity();
		ECS::Entity& entity1 = ecs->entity_manager_.GetEntity(id);
		entity1.AddSystem(0);
		entity1.AddComponent<PhysicsComponent>();
		entity1.GetComponent<Texture>().texture_id_ = 1;
		entity1.GetComponent<PhysicsComponent>().shapeid = 1;
		entity1.GetComponent<Transform>().size_.x = 800;
		entity1.GetComponent<Transform>().position_.y = 400;

		id = ecs->CreateEntity();
		ECS::Entity& entity3 = ecs->entity_manager_.GetEntity(id);
		entity3.AddSystem(0);
		entity3.AddComponent<PhysicsComponent>();
		entity3.GetComponent<Texture>().texture_id_ = 1;
		entity3.GetComponent<PhysicsComponent>().shapeid = 1;
		entity3.GetComponent<Transform>().size_.y = 800;
		entity3.GetComponent<Transform>().position_.x = 400;

		id = ecs->CreateEntity();
		ECS::Entity& entity4 = ecs->entity_manager_.GetEntity(id);
		entity4.AddSystem(0);
		entity4.AddComponent<PhysicsComponent>();
		entity4.GetComponent<Texture>().texture_id_ = 1;
		entity4.GetComponent<PhysicsComponent>().shapeid = 1;
		entity4.GetComponent<Transform>().size_.y = 800;
		entity4.GetComponent<Transform>().position_.x = -400;

		id = ecs->CreateEntity();
		ECS::Entity& entity5 = ecs->entity_manager_.GetEntity(id);
		entity5.AddSystem(0);
		entity5.AddComponent<PhysicsComponent>();
		entity5.GetComponent<Texture>().texture_id_ = 1;
		entity5.GetComponent<PhysicsComponent>().shapeid = 1;
		entity5.GetComponent<Transform>().size_.x = 400;
		entity5.GetComponent<Transform>().size_.y = 10;
		


		for (int i = 0; i < 200; ++i) 
		{
			 int id3 = ecs->CreateEntity();
			 ECS::Entity& entity2 = ecs->entity_manager_.GetEntity(id3);
			 entity2.AddSystem(0);
			 entity2.AddComponent<PhysicsComponent>();
			 entity2.GetComponent<Transform>().position_ = { random<float>(-300.0f, 300.0f),random<float>(-150.0f, 300.0f) };
			 entity2.GetComponent<Texture>().texture_id_ = 2;
			 entity2.GetComponent<PhysicsComponent>().shapeid = 0;
			 float speed =  random<float>(0.3f, 3.0f) ;
			 entity2.GetComponent<Transform>().size_.x = 30;
			 entity2.GetComponent<Transform>().size_.y = 30;
			 entity2.GetComponent<PhysicsComponent>().speed = speed;
			 entity2.GetComponent<PhysicsComponent>().velocity = { speed*cosf( random<float>(0.0f, 6.28f) ) , speed * sinf( random<float>(0.0f, 6.28f) ) };//dir
		}



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

			DeltaTime::update_deltatime(1.0);
			//Test code
			//std::cout<<DeltaTime::get_FPS()<<std::endl;

			global_systems_->FrameEnd();
		}
	}
}
