#include <PCH.h>
#include "DebugInformation.h"
#include "../DebugTools/PerformanceData.h"

namespace JZEngine 
{
	DebugInformation::DebugInformation(float x, float y, float sx, float sy) 
		:
		ImGuiInterface(x, y, sx, sy)
	{

	}

	void DebugInformation::Render() 
	{
		ImGui::Begin("Debug Information");

		ImGui::SetNextItemWidth(50.0f);
		ImGui::SliderInt(": Target FPS |", &target_fps_, 1, 120);

		ImGui::SameLine();
		ImGui::Text("%d Actual FPS |", PerformanceData::actual_fps_);

		ImGui::SameLine();
		ImGui::SetNextItemWidth(50.0f);
		ImGui::SliderFloat("Time Quantum |", &time_quantum_, 0.0f, 5.0f);

		ImGui::Separator();

		if (ImGui::BeginTable("Table", 3))
		{
			//ImGui::TableSetupColumn("Table", 0, 100.0f);
			ImGui::TableNextColumn();
			ImGui::Text("[Process Name]");
			ImGui::TableNextColumn();
			ImGui::Text("[Avg dt/%.1fs]", time_quantum_);
			ImGui::TableNextColumn();
			ImGui::Text("[%% of Target]");
			ImGui::Separator();
			for (auto& t : PerformanceData::timers_)
			{
				ImGui::TableNextColumn();
				ImGui::Text(t.first.c_str());
				ImGui::TableNextColumn();
				ImGui::SliderFloat(":", &t.second.delta_time_, 0.0f, 1.0f/static_cast<float>(target_fps_));
				ImGui::TableNextColumn();
				ImGui::Text("%.3f%%", static_cast<float>(t.second.delta_time_ * target_fps_ * 100.0f));
			}
			ImGui::EndTable();
		}

		ImGui::End();
	}
}