/*	__FILE HEADER__
*	File:		EngineSettings.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders the interface that allows the user to
				modify the engine settings.
*/

#include <PCH.h>
#include "EngineSettings.h"
#include "../EngineConfig.h"
#include "../JZGL/JZ_GL.h"

namespace JZEngine
{
	EngineSettings::EngineSettings(float x, float y, float sx, float sy, int group)
		:
		ImGuiInterface(x, y, sx, sy, group),
		temp_width_(Settings::window_width),
		temp_height_(Settings::window_height),
		temp_cam_x(Settings::camera_width),
		temp_cam_y(Settings::camera_height)
	{

	}

	void EngineSettings::Render(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, { 0, 0, 0, 1 });
		ImGui::Begin("EngineSettings", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		if (ImGui::BeginMenuBar())
		{
			float button_size = Settings::window_width * sx_ * 0.01f;
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconx")->GetRendererID()), { button_size, button_size }))
			{
				ToggleOnOff();
			}
			ImGui::EndMenuBar();
		}
		std::stringstream ss;
		ss << Settings::engine_name << " v" << Settings::version << " Settings";
		ImGui::Text(ss.str().c_str());
		ImGui::Separator();
		if (ImGui::BeginTable("settings", 2))
		{
			// window width and height
			ImGui::TableNextColumn();
			ImGui::Text("Window Width:");
			ImGui::TableNextColumn();
			ImGui::InputInt("##windowwidth", &temp_width_);
			ImGui::TableNextColumn();
			ImGui::Text("Window Height:");
			ImGui::TableNextColumn();
			ImGui::InputInt("##windowheight", &temp_height_);

			// resolution
			ImGui::TableNextColumn();
			ImGui::Text("Camera:");
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(100.0f);
			ImGui::InputInt("##resox", &temp_cam_x);
			ImGui::SameLine();
			ImGui::Text(" x ");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(100.0f);
			ImGui::InputInt("##resoy", &temp_cam_y);

			// confirmation button
			ImGui::TableNextColumn();
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(100.0f);
			if (ImGui::Button("Apply"))
			{
				Settings::window_width = static_cast<unsigned int>(temp_width_);
				Settings::window_height = static_cast<unsigned int>(temp_height_);
				GLFW_Instance::ResizeWindow(Settings::window_width, Settings::window_height);
				Settings::camera_width = temp_cam_x;
				Settings::camera_height = temp_cam_y;
				ToggleOnOff();
			}
			ImGui::SameLine();
			ImGui::SetNextItemWidth(100.0f);
			if (ImGui::Button("Cancel"))
			{
				ToggleOnOff();
				temp_width_ = Settings::window_width;
				temp_height_ = Settings::window_height;
			}

			ImGui::EndTable();
		}


		ImGui::End();
		ImGui::PopStyleColor();
	}
}