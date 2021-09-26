#include <PCH.h>
#include "MenuBar.h"
#include "EngineGUI.h"

#include "../DebugTools/PerformanceData.h"
#include "DebugInformation.h"

namespace JZEngine {
	MenuBar::MenuBar(float x, float y, float sx, float sy) 
		:
		ImGuiInterface(x, y, sx, sy)
	{

	}

	void MenuBar::Render(float dt) {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Performance Visualizer", "[TAB]"))
				{
					GetInterface<DebugInformation>()->active_ = !GetInterface<DebugInformation>()->active_;
				}
				ImGui::EndMenu();
			}

			ImGui::SameLine();
			ImGui::Text(" | App FPS: %4d", PerformanceData::average_app_fps_);
			ImGui::SameLine();
			ImGui::Text(" | Process FPS: %4d |", PerformanceData::average_fps_);

			ImGui::EndMainMenuBar();
		}
	} 
}