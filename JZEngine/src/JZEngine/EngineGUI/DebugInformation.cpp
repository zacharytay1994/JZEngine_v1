/*	__FILE HEADER__
*	File:		DebugInformation.cpp
	Primary:	Zachary Tay
	Secondary:
	Date:		07/10/2021
	Brief:
	Handles the rendering of all debug information.
	Data that the performance visualizer calculates.
*/

#include <PCH.h>

#include "DebugInformation.h"
#include "../DebugTools/PerformanceData.h"
#include "../EngineConfig.h"

namespace JZEngine 
{
	DebugInformation::DebugInformation(float x, float y, float sx, float sy, int group)
		:
		ImGuiInterface(x, y, sx, sy, group)
	{
		target_fps_ = Settings::max_fps;
		float test = sx_;
	}

	void DebugInformation::Render(float dt) 
	{
		ImGui::Begin("Performance Visualizer", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		if (ImGui::BeginMenuBar())
		{
			float button_size = Settings::window_width * sx_ * 0.01f;
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconx")->GetRendererID()), { button_size, button_size }))
			{
				ToggleOnOff();
			}
			ImGui::EndMenuBar();
		}
		ImGui::SetNextItemWidth(100.0f);
		ImGui::InputInt("Target FPS |", &target_fps_);
		if (target_fps_ < 30)
		{
			target_fps_ = 30;
		}

		Settings::max_fps = target_fps_;
		Settings::min_tpf = 1.0 / static_cast<double>(Settings::max_fps);

		ImGui::SameLine();
		ImGui::Text("%5d Process FPS |", PerformanceData::average_fps_);

		ImGui::SameLine();
		ImGui::Text("%5d Application FPS |", PerformanceData::average_app_fps_);

		ImGui::SameLine();
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputFloat("Time Quantum |", &PerformanceData::time_quantum_);
		if (PerformanceData::time_quantum_ < 0.1f)
		{
			PerformanceData::time_quantum_ = 0.1f;
		}

		ImGui::Separator();

		if (ImGui::BeginTable("Headers", 4))
		{
			//ImGui::TableSetupColumn("Table", 0, 100.0f);
			ImGui::TableNextColumn();
			ImGui::Text("Process Name");
			ImGui::TableNextColumn();
			ImGui::Text("Time Taken (ms)");
			ImGui::TableNextColumn();
			ImGui::Text("[Avg DT/Target]");
			ImGui::TableNextColumn();
			ImGui::Text("[%% of Target]");

			ImGui::EndTable();
		}

		// render global systems timers
		ImGui::Separator();
		ImGui::Text("Global Systems");
		ImGui::Separator();
		if (ImGui::BeginTable("Global Systems", 4))
		{
			for (auto& t : PerformanceData::global_system_timers_)
			{
				ImGui::TableNextColumn();
				ImGui::Text(t.first.c_str());
				ImGui::TableNextColumn();
				ImGui::Text("%8.3f", t.second.average_delta_time_ * 1000.0f);
				ImGui::TableNextColumn();
				ImGui::SetNextItemWidth(200.0f);
				t.second.display_delta_time_ += (t.second.average_delta_time_ - t.second.display_delta_time_) * 0.5f * dt;
				ImGui::SliderFloat("##label", &t.second.display_delta_time_, 0.0f, 1.0f / static_cast<float>(target_fps_));
				ImGui::TableNextColumn();
				ImGui::Text("%.3f%%", static_cast<float>(t.second.average_delta_time_ * target_fps_ * 100.0f));
			}
			ImGui::EndTable();
		}

		// render ecs system timers
		ImGui::Separator();
		ImGui::Text("ECS Systems");
		ImGui::Separator();
		if (ImGui::BeginTable("ECS Systems", 4))
		{
			for (auto& t : PerformanceData::ecs_system_timers_)
			{
				ImGui::TableNextColumn();
				ImGui::Text(t.first.c_str());
				ImGui::TableNextColumn();
				ImGui::Text("%8.3f", t.second.average_delta_time_ * 1000.0f);
				ImGui::TableNextColumn();
				ImGui::SetNextItemWidth(200.0f);
				t.second.display_delta_time_ += (t.second.average_delta_time_ - t.second.display_delta_time_) * 0.5f * dt;
				ImGui::SliderFloat("##label", &t.second.display_delta_time_, 0.0f, 1.0f / static_cast<float>(target_fps_));
				ImGui::TableNextColumn();
				ImGui::Text("%.3f%%", static_cast<float>(t.second.average_delta_time_ * target_fps_ * 100.0f));
			}
			ImGui::EndTable();
		}

		// render default timers
		ImGui::Separator();
		ImGui::Text("Default Systems");
		ImGui::Separator();
		if (ImGui::BeginTable("Default Systems", 4))
		{
			for (auto& t : PerformanceData::default_timers_)
			{
				ImGui::TableNextColumn();
				ImGui::Text(t.first.c_str());
				ImGui::TableNextColumn();
				ImGui::Text("%8.3f", t.second.average_delta_time_ * 1000.0f);
				ImGui::TableNextColumn();
				ImGui::SetNextItemWidth(200.0f);
				t.second.display_delta_time_ += (t.second.average_delta_time_ - t.second.display_delta_time_) * 0.5f * dt;
				ImGui::SliderFloat("##label", &t.second.display_delta_time_, 0.0f, 1.0f / static_cast<float>(target_fps_));
				ImGui::TableNextColumn();
				ImGui::Text("%.3f%%", static_cast<float>(t.second.average_delta_time_ * target_fps_ * 100.0f));
			}
			ImGui::EndTable();
		}

		ImGui::End();
	}
}