#include <PCH.h>
#include "ImGuiInterface.h"
#include "../EngineConfig.h"
#include "EngineGUI.h"
#include "MenuBar.h"

namespace JZEngine 
{
	ImGuiInterface::ImGuiInterface(float x, float y, float sx, float sy, int group)
		:
		x_(x), y_(y), sx_(sx), sy_(sy), group_(group)
	{

	}

	void ImGuiInterface::RenderInterface(float dt)
	{
		if (active_)
		{
			ImGui::SetNextWindowBgAlpha(0.8f);
			ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, MenuBar::height_ + static_cast<float>(Settings::window_height - MenuBar::height_) * y_ }, ImGuiCond_Always);
			ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height - MenuBar::height_) * sy_ }, ImGuiCond_Always);

			Render(dt);
		}
	}

	void ImGuiInterface::SetEngineGUI(EngineGUI* enginegui) {
		engine_gui_ = enginegui;
	}

	void ImGuiInterface::ToggleOnOff() {
		if (engine_gui_) {
			bool temp = active_;
			engine_gui_->CloseAllGroupedInterface(group_);
			active_ = !temp;
		}
	}
}