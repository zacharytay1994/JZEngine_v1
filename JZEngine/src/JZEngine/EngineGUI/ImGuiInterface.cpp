#include <PCH.h>
#include "ImGuiInterface.h"
#include "../EngineConfig.h"
#include "EngineGUI.h"

namespace JZEngine 
{
	ImGuiInterface::ImGuiInterface(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{

	}

	void ImGuiInterface::RenderInterface() 
	{
		if (active_)
		{
			ImGui::SetNextWindowBgAlpha(0.8f);
			ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, static_cast<float>(Settings::window_height) * y_ }, ImGuiCond_Always);
			ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height) * sy_ }, ImGuiCond_Always);

			Render();
		}
	}

	void ImGuiInterface::SetEngineGUI(EngineGUI* enginegui) {
		engine_gui_ = enginegui;
	}
}