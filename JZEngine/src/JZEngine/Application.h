/*	__FILE HEADER__ 
*	File:	Application.h
	Author: JZ
	Date:	19/06/21
	Brief:	Declares an application class that runs the engine editor. 
*/

#pragma once

#include "BuildDefinitions.h"

namespace JZEngine
{	
	/*!
	 * @brief JZEngine::Application ~
	 * Application class to be exported. When inherited from and created in
	 * a project, it calls the run function from the main entry point
	 * of the engine defined in EntryPoint.h.
	*/
	class JZENGINE_API Application
	{
	public:
		Application();

		/*!
		 * @brief JZEngine::Application::Run() ~
		 * Is called in the main entry point of the engine
		 * defined in EntryPoint.h.
		*/
		void Run();

	};

	/*!
	 * @brief JZEngine::CreateApplication()
	 * Just the declaration of the function exists in the engine.
	 * The definition is left up to the client software to define.
	 * When defined, it should create a child of JZEngine::Application
	 * in the main entry point of the engine defined in EntryPoint.h.
	 * 
	 * @return 
	 * Pointer to the application created.
	*/
	Application* CreateApplication();
}