/*	__FILE HEADER__
*	File:		ImGuiInterface.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Virtual class to be inherited by any
				imgui interface and added to the enginegui.
*/

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
			ImGui::SetNextWindowBgAlpha(gui_alpha_);
			ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, MenuBar::height_ + static_cast<float>(Settings::window_height - MenuBar::height_) * y_ }, ImGuiCond_Always);
			ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height - MenuBar::height_) * sy_ }, ImGuiCond_Always);

			Render(dt);
		}
	}

	void ImGuiInterface::SetNextWindowDimensions(float start_x, float start_y, float width, float height)
	{
		ImGui::SetNextWindowBgAlpha(gui_alpha_);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_ + (start_x * static_cast<float>(Settings::window_width) * sx_),
			MenuBar::height_ + static_cast<float>(Settings::window_height - MenuBar::height_) * y_ + (start_y * static_cast<float>(Settings::window_height - MenuBar::height_) * sy_) }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_ * width, static_cast<float>(Settings::window_height - MenuBar::height_) * sy_ * height }, ImGuiCond_Always);
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

	void ImGuiInterface::CloseButtonMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			float button_size = Settings::window_width * sx_ * 0.01f;
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconx")->GetRendererID()), { button_size, button_size }))
			{
				ToggleOnOff();
			}
			ImGui::EndMenuBar();
		}
	}
}