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
#include "GraphicRendering/TextRenderer.h"
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
	TextRenderer text;

	Application::Application ()
		:
		global_systems_ ( new GlobalSystemsManager () )
	{
		// add and initialize global systems
		global_systems_->AddSystem<GLFW_Instance> ( Settings::window_width , Settings::window_height );
		global_systems_->AddSystem<ResourceManager> ();
		global_systems_->AddSystem<ECS::ECSInstance> ();
		global_systems_->AddSystem<Renderer> ();
		global_systems_->AddSystem<RendererInstancing> ();
		global_systems_->AddSystem<EngineGUI> ();
		global_systems_->AddSystem<SoundSystem> ();

		// give subsystems handle to global systems
		global_systems_->GetSystem<ECS::ECSInstance> ()->GetSystemInefficient<Sprite> ()->sprite_renderer_.renderer_ = global_systems_->GetSystem<Renderer> ();
		global_systems_->GetSystem<ECS::ECSInstance> ()->GetSystemInefficient<InstanceSprite> ()->sprite_renderer_instancing_.renderer_ = global_systems_->GetSystem<RendererInstancing> ();

		// give singleton logger handle to the engine console
		Log::Instance ().Initialize ( global_systems_->GetSystem<EngineGUI> ()->GetConsole () );
		JZEngine::Log::Info ( "Main" , "[{}] Up and Running! v{}" , Settings::engine_name , Settings::version );

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

		text.Load ( "Assets/Fonts/Weather Sunday.otf" , 100 , Settings::window_width/2.0f , Settings::window_height / 2.0f );

	}

	void Application::Free ()
	{
		Log::Instance ().Free ();
		global_systems_->Free ();
		delete global_systems_;
	}

	void Application::Run ()
	{
		while( global_systems_->GetSystem<GLFW_Instance> ()->Active () )
		{
			global_systems_->FrameStart ();
			global_systems_->Update ( 1.0 );

			text.RenderText ( "JZ Engine" , 100 , 100 , 1 , { 0.0f , 0.0f , 0.0f } );
			DeltaTime::update_time ( 1.0 );
			global_systems_->FrameEnd ();
		}
	}
}
