
/*	__FILE HEADER__
*	File:		Application.cpp
	Primary:	Deon Khong, Jee Jia Min, Yu Ching Yin, Zachary Tay
	Date:		19/06/21
	Brief:		Defines an application class that runs the engine editor.
				See Application.h for more information on the class.
*/

#include <PCH.h>
#include "Application.h"
#include "ECS/ECSconfig.h"
#include "EngineConfig.h"
#include "DebugTools/Log.h"
#include "Sound/Sound.h"
#include "SceneLogic/SceneLogic.h"
#include "GraphicRendering/Camera.h"

#include "GraphicRendering/Renderer.h"
#include "GraphicRendering/RendererInstancing.h"
#include "GraphicRendering/RendererDebug.h"
#include "GraphicRendering/SpriteRenderer.h"
#include "GraphicRendering/TextRenderer.h"
#include "GraphicRendering/RenderQueue.h"

#include "Input/Input.h"
#include "Input/DeltaTime.h"
#include "Resource/Serialize.h"
#include "Resource/ObjectPool.h"

#include "STL/Random.h"
#include "STL/Tuple.h"
#include "DebugTools/PerformanceData.h"

#include <iostream>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>

#include "ImGui/ImGuizmo.h"

#define UNREFERENCED_PARAMETER(P) (P)

#include "Message/Event.h"
#include "FSM/CustomerState.h"

namespace JZEngine
{
	Application::Application()
		: //msgbus( new MessageBus() ),
		  global_systems_(new GlobalSystemsManager())
	{
		Settings::LoadFromConfigFile();
		Serialize::Load();

		// add and initialize global systems
		global_systems_->AddSystem<GLFW_Instance>("GLFW Instance", Settings::window_width, Settings::window_height);
		global_systems_->AddSystem<ResourceManager>("Resource Manager");
		global_systems_->AddSystem<ECS::ECSInstance>("ECS Instance");
		global_systems_->AddSystem<Renderer>("Default Renderer");
		global_systems_->AddSystem<RendererInstancing>("Instance Renderer");
		global_systems_->AddSystem<RenderQueue>("Render Queue");
		global_systems_->AddSystem<RendererDebug>("Debug Renderer");
		global_systems_->AddSystem<EngineGUI>("Engine GUI");
		global_systems_->AddSystem<SoundSystem>("Sound System");
		global_systems_->AddSystem<TextRenderer>("Text Renderer");

		SceneLogic::Instance().SetECS(global_systems_->GetSystem<ECS::ECSInstance>());

		global_systems_->GetSystem<GLFW_Instance>()->UpdateViewportDimensions();
		global_systems_->GetSystem<RenderQueue>()->SetRenderer(global_systems_->GetSystem<Renderer>());

		// give subsystems handle to global systems
		/*global_systems_->GetSystem<ECS::ECSInstance> ()->GetSystemInefficient<Sprite> ()->sprite_renderer_.renderer_ = global_systems_->GetSystem<Renderer> ();*/
		global_systems_->GetSystem<ECS::ECSInstance>()->GetSystemInefficient<InstanceSprite>()->sprite_renderer_instancing_.renderer_ = global_systems_->GetSystem<RendererInstancing>();
		//global_systems_->GetSystem<ECS::ECSInstance> ()->GetSystemInefficient<ParallaxBackground> ()->sprite_renderer_.renderer_ = global_systems_->GetSystem<Renderer> ();
		global_systems_->GetSystem<ECS::ECSInstance>()->GetSystemInefficient<Text>()->text_renderer_ = global_systems_->GetSystem<TextRenderer>();

		//Create sound
		//global_systems_->GetSystem<SoundSystem>()->createSound("LOST CIVILIZATION - NewAge MSCNEW2_41.wav", "../JZEngine/Resources/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");
		//global_systems_->GetSystem<SoundSystem>()->createSound("mellau__button-click-1.wav", "../JZEngine/Resources/mellau__button-click-1.wav");
		
		global_systems_->GetSystem<SoundSystem>()->LoadAllSoundsInFolder("Assets/Sounds/");
		//global_systems_->GetSystem<SoundSystem>()->playSound("lost_civ");
		// give singleton logger handle to the engine console
		Log::Instance().Initialize(global_systems_->GetSystem<EngineGUI>()->GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);

		// initialize all global systems
		global_systems_->PostInit();
		PerformanceData::Init();
		SceneLogic::Instance().SetSceneTree(global_systems_->GetSystem<EngineGUI>()->GetSceneTree());
		SceneLogic::Instance().SetSoundSystem(global_systems_->GetSystem<SoundSystem>());

		//msgbus->subscribe ( global_systems_->GetSystem<SoundSystem> () , &SoundSystem::playSound );
	}

	void Application::Free()
	{
		Log::Instance().Free();
		global_systems_->Free();
		//delete msgbus;
		delete global_systems_;
	}

	void Application::Run()
	{
		double time = 0.0;
		double dt{Settings::min_tpf};
		//double actual_dt{ Settings::min_tpf };
		//double clamped_dt{ Settings::min_tpf };
		bool limit_frames = true;

		//Cannot pass the dt into the sandbox that's why test it here first
		std::cout << "-----------------------------"
				  << "\n";
		std::cout << "Demo for Finite State Machine"
				  << "\n";
		std::cout << "-----------------------------"
				  << "\n";
		/**/
		/*JZEngine::FiniteStateMachine<JZEngine::CustomerStateType>* fsm = new JZEngine::FiniteStateMachine<JZEngine::CustomerStateType>();

		fsm->add(new JZEngine::CustomerOrderingState(*fsm));
		fsm->add(new JZEngine::CustomerWaitingState(*fsm));
		fsm->add(new JZEngine::CustomerAngryLeaveState(*fsm));
		fsm->add(new JZEngine::CustomerHappyLeaveState(*fsm));

		fsm->setCurrentState(JZEngine::CustomerStateType::ORDERING);*/

		//fsm->update(1.0f/ JZEngine::PerformanceData::app_fps_);

		while (global_systems_->GetSystem<GLFW_Instance>()->Active())
		{
			//fsm->update(static_cast<float>(dt));

			/*if( InputHandler::IsKeyTriggered ( KEY::KEY_L ) )
			{
				limit_frames = !limit_frames;
			}*/

			auto start_time = std::chrono::high_resolution_clock::now();

			//double dt = limit_frames ? clamped_dt : actual_dt;

			PerformanceData::FrameStart();
			PerformanceData::StartMark("Game Loop", PerformanceData::TimerType::GLOBAL_SYSTEMS);

			global_systems_->FrameStart();

			// after this call all mouse world positions will be calculated
			//InputHandler::CalculateMouseWorldPosition(global_systems_->GetSystem<GLFW_Instance>()->window_, MenuBar::height_);
			Camera::CalculateMouseWorldPosition(global_systems_->GetSystem<GLFW_Instance>()->window_);

			global_systems_->Update(static_cast<float>(dt));
			SceneLogic::Instance().BuildEntityMap();
			SceneLogic::Instance().UpdateSceneLogic(static_cast<float>(dt));

			//DeltaTime::update_time(1.0);
			//DeltaTime::update_deltatime(1.0);

			//Test code
			//std::cout<<DeltaTime::get_FPS()<<std::endl;

			//click sound test code
			bool pressed = JZEngine::InputHandler::IsMouseTriggered(JZEngine::MOUSE::MOUSE_BUTTON_LEFT);
			if (pressed == true)
			{
				SoundEvent event{};
				event.name = "mellau__button-click-1.wav";
				//msgbus->publish ( &event );
			}

			InputHandler::FrameEnd(); //input handler frameend MUST be here before global system->frameend

			auto end_time = std::chrono::high_resolution_clock::now();
			global_systems_->FrameEnd();
			ObjectPool::FrameEnd(global_systems_->GetSystem<ECS::ECSInstance>());

			PerformanceData::EndMark("Game Loop", PerformanceData::TimerType::GLOBAL_SYSTEMS);
			PerformanceData::FrameEnd();

			std::chrono::duration<double, std::milli> milli_dt = end_time - start_time;
			dt = milli_dt.count() / 1000.0;
			double min_tpf_milli = Settings::min_tpf * 1000.0;

			// sleep
			if (limit_frames)
			{
				while (milli_dt.count() < min_tpf_milli)
				{
					end_time = std::chrono::high_resolution_clock::now();
					milli_dt = end_time - start_time;
				}
				dt = milli_dt.count() / 1000.0;
				time += dt;
			}
			else
			{
				time += dt;
			}
			//Log::Info("Main", "Sleep Time: {}", sleep_time);
			PerformanceData::time_elapsed_ = static_cast<float>(time);

			PerformanceData::app_fps_ = static_cast<unsigned int>(1.0 / dt);
			/*Log::Info("Main", "Time Elapsed: {}", time);
			Log::Info("Main", "Actual dt: {}", actual_dt);
			Log::Info("Main", "Clamped dt: {}", clamped_dt);
			Log::Info("Main", "Actual FPS: {}", 1.0 / actual_dt);
			Log::Info("Main", "Clamped FPS: {}", 1.0 / clamped_dt);*/
		}

		//Serialize::Save();
		Settings::SaveToConfigFile ();
		//delete fsm;
	}
}
