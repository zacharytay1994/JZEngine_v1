/*	__FILE HEADER__
*	File:		Application.cpp
	Primary:	Deon Khong, Jee Jia Min, Yu Ching Yin, Zachary Tay
	Date:		19/06/21
	Brief:		Defines an application class that runs the engine editor.
				See Application.h for more information on the class.
*/

/*! PRECOMPILE HEADER */
#include <PCH.h>

/*! GAME ENGINE INCLUDES - START */
#include "Application.h"
#include "EngineConfig.h"
#include "DebugTools/Log.h"
#include "Sound/Sound.h"
#include "SceneLogic/SceneLogic.h"
#include "GraphicRendering/Camera.h"
#include "Input/Input.h"
#include "Resource/Serialize.h"
#include "Resource/ObjectPool.h"
#include "DebugTools/PerformanceData.h"
#include "GraphicRendering/Renderers/GlobalRenderer.h"
/*! GAME ENGINE INCLUDES - END */

namespace JZEngine
{
	Application::Application()
		: 
		global_systems_(new GlobalSystemsManager())
	{
		// Load engine settings from a config file
		Settings::LoadFromConfigFile();

		// Load all scenes and prefabs
		Serialize::Load();

		// Initialize GLFW/OPENGL as a global system
		global_systems_->AddSystem<GLFW_Instance>("GLFW Instance", Settings::window_width, Settings::window_height);

		// initialize global renderer - needs to be after instantiating  GLFW in order to render stuff
		GlobalRenderer::Instance().Initialize();

		// Instantiate Global Systems
		global_systems_->AddSystem<ResourceManager>		("Resource Manager");
		global_systems_->AddSystem<ECS::ECSInstance>	("ECS Instance");
		global_systems_->AddSystem<EngineGUI>			("Engine GUI");
		global_systems_->AddSystem<SoundSystem>			("Sound System");

		// Give global renderer the resource manager to sample textures and shaders
		GlobalRenderer::Instance().SetResourceManager(global_systems_->GetSystem<ResourceManager>());

		// Update viewport dimensions with the loaded dimensions gotten from a the saved config file if any
		global_systems_->GetSystem<GLFW_Instance>()->UpdateViewportDimensions();
		
		// Load all sounds files from the sound resource folder
		global_systems_->GetSystem<SoundSystem>()->LoadAllSoundsInFolder("Assets/Sounds/");

		// give singleton logger handle to the engine console
		Log::Instance().Initialize(global_systems_->GetSystem<EngineGUI>()->GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{}", Settings::engine_name, Settings::version);

		// initialize all global systems
		global_systems_->PostInit();
		PerformanceData::Init();

		// Give scenelogic singleton to be used on the client side various engine systems for use
		SceneLogic::Instance().SetECS(global_systems_->GetSystem<ECS::ECSInstance>());
		SceneLogic::Instance().SetSceneTree(global_systems_->GetSystem<EngineGUI>()->GetSceneTree());
		SceneLogic::Instance().SetSoundSystem(global_systems_->GetSystem<SoundSystem>());
	}

	/*!
	 * @brief ___JZEngine::Application::Free()___
	 * *********************************************************
	 * Freeing the application.
	 * *********************************************************
	*/
	void Application::Free()
	{
		// free logger instance
		Log::Instance().Free();

		// free and delete global systems
		global_systems_->Free();
		delete global_systems_;
	}

	/*!
	 * @brief ___JZEngine::Application::Run()___
	 * *********************************************************
	 * Application main loop.
	 * *********************************************************
	*/
	void Application::Run()
	{
		double	time{ 0.0 };
		double	dt{ Settings::min_tpf };
		bool	limit_frames{ true };

		// Gameloop
		while (global_systems_->GetSystem<GLFW_Instance>()->Active())
		{
			// Get the start time
			auto start_time = std::chrono::high_resolution_clock::now();

			// Record performance data at the start of the frame
			PerformanceData::FrameStart();
			PerformanceData::StartMark("Game Loop", PerformanceData::TimerType::GLOBAL_SYSTEMS);

			// Call frame start function of all global systems
			global_systems_->FrameStart();

			// After this call all mouse world positions will be calculated
			Camera::CalculateMouseWorldPosition(global_systems_->GetSystem<GLFW_Instance>()->window_);

			// Draw global renderer - should be after global systems update but here temporarily because
			// it needs to be drawn before the engine gui
			GlobalRenderer::Instance().Update(static_cast<float>(dt));

			// All global system updates, i.e. ecs, engine gui, sound system
			global_systems_->Update(static_cast<float>(dt));

			// Build entity map of all objects in the scene
			// for the client side to access game objects currently in the scene
			SceneLogic::Instance().BuildEntityMap();
			// Updates the scene logic function specified by the client
			SceneLogic::Instance().UpdateSceneLogic(static_cast<float>(dt));

			// Global renderer end frame clean up
			GlobalRenderer::Instance().FrameEnd();

			// Input handler frame end - process input
			// input handler frameend MUST be here before global system->frameend
			InputHandler::FrameEnd(); 

			// Get the end time of the frame
			auto end_time = std::chrono::high_resolution_clock::now();

			// Call frame end function of global systems
			global_systems_->FrameEnd();

			// Frame end of object pool - WHY ISNT OBJECT POOL A GLOBAL SYSTEM HMM DESIGN FLAW
			ObjectPool::FrameEnd(global_systems_->GetSystem<ECS::ECSInstance>());

			// Record performance data at the end of the frame
			PerformanceData::EndMark("Game Loop", PerformanceData::TimerType::GLOBAL_SYSTEMS);
			PerformanceData::FrameEnd();

			// Calculate sleep time for the frame to maintain maximum fps
			std::chrono::duration<double, std::milli> milli_dt = end_time - start_time;
			dt = milli_dt.count() / 1000.0;
			double min_tpf_milli = Settings::min_tpf * 1000.0;

			// Sleep
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

			// Set performance data variables to be displayed in the engine
			PerformanceData::time_elapsed_ = static_cast<float>(time);
			PerformanceData::app_fps_ = static_cast<unsigned int>(1.0 / dt);
		}

		// Save engine settings to the config file upon exiting the program
		Settings::SaveToConfigFile ();
	}
}
