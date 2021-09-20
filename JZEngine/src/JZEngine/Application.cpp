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
		gl_instance_( Settings::window_width, Settings::window_height ),
		ecs_instance_( new ECS::ECSInstance() ),
		engine_gui_( gl_instance_.window_, ecs_instance_, &resource_manager_ ),
		renderer_( new Renderer(&resource_manager_) )
	{
		Log::Instance().Initialize( engine_gui_.GetConsole() );
		JZEngine::Log::Info( "Main", "[{}] Up and Running! v{} [MEM LEAKS BEGONE]", Settings::engine_name, Settings::version );

		testsystem.initialize();

		renderer_->Init();

		ecs_instance_->GetSystemInefficient<Sprite>()->sprite_renderer_.renderer_ = renderer_;
		/*testsystem.createSound("testsound", "../JZEngine/Resources/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");
		testsystem.playSound("testsound", true, 0.4f);
		testsystem.setChannelGroupVolume(1.0f,"main");*/
		InputHandler::IsMousePressed(MOUSEBUTTON::MOUSE_BUTTON_LEFT);

	}

	void Application::Free()
	{
		Log::Instance().Free();
		delete ecs_instance_;
		delete renderer_;
	}

	void Application::Run()
	{
		while ( gl_instance_.Active() )
		{
			gl_instance_.FrameStart();

			gl_instance_.Draw();

			/*sprite.DrawSprite({ 400.0f, 400.0f },
				{ 50.0f , 50.0f },
				{ 1.0f, 1.0f },
				45.0f,
				{ 0.5f, 0.5f, 0.50f });

			sprite2.DrawSprite({ -300.0f, 200.0f },
				{ 50.0f , 50.0f },
				{ 1.0f, 1.0f },
					45.0f,
					{ 0.5f, 0.5f, 0.50f });*/

			engine_gui_.Update();

			testsystem.updateSoundSystem();

			ecs_instance_->Update();

			gl_instance_.FrameEnd();

			DeltaTime::update_time(1.0);


		}
	}
}
