#pragma once

#include "BuildDefinitions.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

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