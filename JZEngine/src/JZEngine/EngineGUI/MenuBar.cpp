#include <PCH.h>
#include "MenuBar.h"
#include "EngineGUI.h"

#include "../DebugTools/PerformanceData.h"
#include "FolderInterface.h"
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
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Resources", "[SHIFT+R]"))
				{
					GetInterface<FolderInterface>()->active_ = !GetInterface<FolderInterface>()->active_;
				}
				ImGui::EndMenu();
			}
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

			ImGui::SetNextItemWidth(100.0f);
			if (ImGui::BeginMenu(transform_mode_.c_str()))
			{
				if (ImGui::MenuItem("Translate", "[t]"))
				{
					transform_mode_ = "Transform Mode: Translate";
					engine_gui_->operation_ = ImGuizmo::OPERATION::TRANSLATE;
				}
				if (ImGui::MenuItem("Rotate", "[r]"))
				{
					transform_mode_ = "Transform Mode: Rotate";
					engine_gui_->operation_ = ImGuizmo::OPERATION::ROTATE_Z;
				}
				if (ImGui::MenuItem("Scale", "[s]"))
				{
					transform_mode_ = "Transform Mode: Scale";
					engine_gui_->operation_ = ImGuizmo::OPERATION::SCALE;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	} 
}