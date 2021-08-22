#pragma once

#include "../BuildDefinitions.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"

#include "Inspector.h"
#include "Console.h"

namespace JZEngine
{
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
		void Update(ECS::Entity& entity);

	private:
		Inspector	inspector_;
		Console		console_;

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

		void SetWindowPositionScale(float x, float y, float sx, float sy);

		void RenderSceneTree();
	};
}