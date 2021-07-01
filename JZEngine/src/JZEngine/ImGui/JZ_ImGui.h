#pragma once

#include "../BuildDefinitions.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace JZEngine
{
	struct JZENGINE_API ToolsGUI
	{
		ToolsGUI(GLFWwindow*& glfwwindow);
		~ToolsGUI();

		void Update();
	private:
		void InitializeGLFW(GLFWwindow*& glfwwindow);
	};
}