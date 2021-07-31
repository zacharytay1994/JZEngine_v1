/*	__FILE HEADER__ 
*	File:	Application.h
	Author: JZ
	Date:	19/06/21
	Brief:	Declares an application class that runs the engine editor. 
*/

#pragma once

#include "BuildDefinitions.h"

#include "ImGui/JZ_ImGui.h"
#include "JZGL/JZ_GL.h"
#include "ECS/ECS.h"

namespace JZEngine
{	
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
		 * @brief ___JZEngine::Application::Run()___
		 * 
		 * Is called in the main entry point of the engine
		 * defined in EntryPoint.h.
		*/
		void Run();

	private:
		JZEngine::GLFW_Instance		gl_instance_;	/*!< glfw instance, abstracts creation of opengl instance using glfw */
		JZEngine::ToolsGUI			tools_gui_;		/*!< handles rendering and updating of engine tools gui */
		//JZEngine::ECS::ECS_Instance ecs_instance_;	/*!< ecs_instance handling all ecs stuffs */
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