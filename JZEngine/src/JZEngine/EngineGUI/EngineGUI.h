#pragma once

#include "../BuildDefinitions.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
/*	__FILE HEADER__
*	File:	EngineGUI.h
	Author: JZ
	Date:	26/08/21
	Brief:	Handles the rendering of the Engine GUI,
			e.g. Inspector, Console, etc.
*/

#pragma once

#include "../ImGui/imgui_impl_opengl3.h"

#include "Inspector.h"
#include "Console.h"
#include "SceneTree.h"

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::EngineGUI___
	 * ****************************************************************************************************
	 * In charge of rendering the Engine graphical user interface with ImGui.
	 * ****************************************************************************************************
	*/
	struct JZENGINE_API EngineGUI
	{
		EngineGUI(GLFWwindow*& glfwwindow);
		~EngineGUI();

		/*!
		 * @brief ___JZEngine::ToolsGUI::Update()___
		 * ****************************************************************************************************
		 * Updates all imgui gui.
		 * ****************************************************************************************************
		 * @param entity 
		 * : Entity for Inspector gui to use.
		 * ****************************************************************************************************
		*/
		void Update();

	private:
		Inspector	inspector_;		/*!< engine inspector */
		Console		console_;		/*!< engine console */
		SceneTree	scene_tree_;	/*!< engine console */

		/*!
		 * @brief ___JZEngine::ToolsGUI::IntiializeWithGLFW()___
		 * ****************************************************************************************************
		 * Initializes ImGUI with GLFWOpenGL3.
		 * ****************************************************************************************************
		 * @param glfwwindow 
		 * : Handle to glfw window created.
		 * ****************************************************************************************************
		*/
		void InitializeWithGLFW(GLFWwindow*& glfwwindow);
	};
}