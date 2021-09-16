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
#include "GraphicRendering/SpriteRenderer.h"

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

	SpriteRenderer sprite;

	Application::Application()
		:
		gl_instance_(Settings::window_width, Settings::window_height),
		ecs_instance_(new ECS::ECSInstance),
		engine_gui_(gl_instance_.window_, ecs_instance_)
	{
		Log::Instance().Initialize(engine_gui_.GetConsole());
		JZEngine::Log::Info("Main", "[{}] Up and Running! v{} [MEM LEAKS BEGONE]", Settings::engine_name, Settings::version);
	
		testsystem.initialize();
		/*testsystem.createSound("testsound", "../JZEngine/Resources/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");
		testsystem.playSound("testsound", true, 0.4f);
		testsystem.setChannelGroupVolume(1.0f,"main");*/

		//Math::AllMatrixTestCases();
		sprite.Init( "Assets/Textures/Square.jpg");
	}

	void Application::Free()
	{
		Log::Instance().Free();
		delete ecs_instance_;
	}

	void Application::Run()
	{
		while ( gl_instance_.Active() )
		{

			gl_instance_.FrameStart();

			gl_instance_.Draw();

			engine_gui_.Update();

			testsystem.updateSoundSystem();

			ecs_instance_->Update();

			sprite.DrawSprite({ 200.0f, 200.0f }, { 300.0f,300.0f }, 45.0f, {1.0f, 1.0f, 0.40f} );

			gl_instance_.FrameEnd();
		}
	
	}
}
