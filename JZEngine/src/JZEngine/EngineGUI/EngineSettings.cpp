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
		temp_height_(Settings::window_height)
	{

	}

	void EngineSettings::Render(float dt)
	{
		ImGui::Begin("EngineSettings", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		std::stringstream ss;
		ss << Settings::engine_name << " v" << Settings::version << " Settings";
		ImGui::Text(ss.str().c_str());
		ImGui::Separator();
		if (ImGui::BeginTable("settings", 2))
		{
			ImGui::TableNextColumn();
			ImGui::Text("Window Width:");
			ImGui::TableNextColumn();
			ImGui::InputInt("##windowwidth", &temp_width_);
			ImGui::TableNextColumn();
			ImGui::Text("Window Height:");
			ImGui::TableNextColumn();
			ImGui::InputInt("##windowheight", &temp_height_);

			// confirmation button
			ImGui::TableNextColumn();
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(100.0f);
			if (ImGui::Button("Apply"))
			{
				Settings::window_width = static_cast<unsigned int>(temp_width_);
				Settings::window_height = static_cast<unsigned int>(temp_height_);
				GLFW_Instance::ResizeWindow(Settings::window_width, Settings::window_height);
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
	}
}