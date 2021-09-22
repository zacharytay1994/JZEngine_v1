/*	__FILE HEADER__ 
*	File:	Application.h
	Author: JZ
	Date:	19/06/21
	Brief:	Declares an application class that runs the engine editor. 
*/

#pragma once

#include "BuildDefinitions.h"
#include "EngineGUI/EngineGUI.h"
#include "ECS/ECS.h"
#include "Resource/ResourceManager.h"

// jzgl should be included last as glad.h should be included after
// any library/file that includes windows.h 
#include "JZGL/JZ_GL.h"

namespace JZEngine
{	
	constexpr int width = 1600;

	/*!
	 * @brief ___JZEngine::Application___
	 * 
	 * Application class to be exported. When inherited from and created in
	 * a client project, it calls the run function from the main entry point
	 * of the engine defined in EntryPoint.h.
	 
	*/
	class JZENGINE_API Application
	{
	public:
		Application();

		/*!
		 * @brief ___JZEngine::Application::Free()___
		 * 
		 * Is called after the game loop
		*/
		void Free();

		/*!
		 * @brief ___JZEngine::Application::Run()___
		 * 
		 * Is called in the main entry point of the engine
		 * defined in EntryPoint.h.
		*/
		void Run();

	private:
		JZEngine::GLFW_Instance				gl_instance_;		/*!< glfw instance, abstracts creation of opengl instance using glfw */
		JZEngine::ResourceManager			resource_manager_;	/*!< resource manager loads all resources from files */
		JZEngine::ECS::ECSInstance*	const	ecs_instance_;		/*!< ecs_instance handling all ecs stuffs */
		JZEngine::EngineGUI					engine_gui_;		/*!< handles rendering and updating of engine tools gui */
		Renderer* const						renderer_;			/*!< renderer handles all opengl rendering */
		RendererInstancing* const			renderer_instancing_;
	};

	/*!
	 * @brief ___JZEngine::CreateApplication()___
	 * 
	 * Just the declaration of the function that exists in the engine.
	 * The definition is left up to the client software to define.
	 * When defined, it should create a child of JZEngine::Application
	 * in the main entry point of the engine defined in EntryPoint.h.
	 * 
	 * @return Application* : pointer to the application created
	*/
	Application* CreateApplication();
}