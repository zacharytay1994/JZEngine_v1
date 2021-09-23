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
#include "STL/Tuple.h"

#include <iostream>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>

#define UNREFERENCED_PARAMETER(P)(P)

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
	}

	void Application::Free()
	{
		Log::Instance().Free();
		global_systems_->Free();
		delete global_systems_;
	}

	void Application::Run()
	{
		double time = 0.0;
		double actual_dt{ Settings::min_tpf };
		double clamped_dt{ Settings::min_tpf };
		bool limit_frames = false;

		while (global_systems_->GetSystem<GLFW_Instance>()->Active())
		{
			if (InputHandler::IsKeyPressed(KEY::KEY_L)) { limit_frames = !limit_frames; }

			auto start_time = std::chrono::high_resolution_clock::now();

			double dt = limit_frames ? clamped_dt : actual_dt;

			global_systems_->FrameStart();
			global_systems_->Update(actual_dt);
			DeltaTime::update_time(1.0);

			auto end_time = std::chrono::high_resolution_clock::now();
			global_systems_->FrameEnd();

			std::chrono::duration<double, std::milli> milli_dt = end_time - start_time;
			actual_dt = milli_dt.count() / 1000.0;
			double min_tpf_milli = Settings::min_tpf * 1000.0;

			// sleep
			if (limit_frames) 
			{
				while (milli_dt.count() < min_tpf_milli)
				{
					end_time = std::chrono::high_resolution_clock::now();
					milli_dt = end_time - start_time;
				}
				clamped_dt = milli_dt.count() / 1000.0;
				time += clamped_dt;
			}
			else 
			{
				clamped_dt = std::max(Settings::min_tpf, actual_dt);
				time += actual_dt;
			}

			/*Log::Info("Main", "Time Elapsed: {}", time);
			Log::Info("Main", "Actual dt: {}", actual_dt);
			Log::Info("Main", "Clamped dt: {}", clamped_dt);
			Log::Info("Main", "Actual FPS: {}", 1.0 / actual_dt);
			Log::Info("Main", "Clamped FPS: {}", 1.0 / clamped_dt);*/
		}
	}
}
