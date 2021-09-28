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
#include "Input/Input.h"
#include "Input/DeltaTime.h"


#include "STL/Tuple.h"
#include <iostream>
#include <tuple>


#define UNREFERENCED_PARAMETER(P)(P)

#include <memory>
#include <unordered_map>
#include <string>

#include "Math/JZMath.h"

#include "Message/Event.h"





namespace JZEngine
{
	//instance
	SoundSystem testsystem;

	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		ecs_instance_(new ECS::ECSInstance),
		engine_gui_(gl_instance_.window_, ecs_instance_)
	{
		Log::Instance().Initialize(engine_gui_.GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{} [MEM LEAKS BEGONE]", Settings::engine_name, Settings::version);
	
		
		testsystem.initialize();
		testsystem.createSound("LOST CIVILIZATION - NewAge MSCNEW2_41.wav", "../JZEngine/Resources/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");
		//testsystem.playSound("testsound", true, 0.4f);
		testsystem.setChannelGroupVolume(0.1f,"main");
		//InputHandler::

		msgbus.subscribe(&testsystem, &SoundSystem::playSound);

	}

	void Application::Free()
	{
		Log::Instance().Free();
		delete ecs_instance_;
	}
	
	void Application::Run()
	{
		while (gl_instance_.Active())
		{
			 
			gl_instance_.FrameStart();

			gl_instance_.Draw ();

			engine_gui_.Update();

			testsystem.updateSoundSystem();
			
			ecs_instance_->Update();

			gl_instance_.FrameEnd();

			DeltaTime::update_time(1.0);

			bool pressed = JZEngine::InputHandler::IsMousePressed(JZEngine::InputHandler::MOUSEBUTTON::MOUSE_BUTTON_LEFT);
			
			if (pressed == true)
			{
				SoundEvent event{};
				event.name = "LOST CIVILIZATION - NewAge MSCNEW2_41.wav";
				msgbus.publish(&event);
			}


		}


	
	}
}
