#include <PCH.h>
#include "MenuBar.h"
#include "EngineGUI.h"
#include "../Input/Input.h"

#include "../DebugTools/PerformanceData.h"
#include "FolderInterface.h"
#include "DebugInformation.h"

namespace JZEngine {
	MenuBar::MenuBar(float x, float y, float sx, float sy, int group) 
		:
		ImGuiInterface(x, y, sx, sy, group)
	{

	}

	void MenuBar::Render(float dt) {
		// shortcuts
		if (InputHandler::IsKeyTriggered(KEY::KEY_TAB)) {
			GetInterface<FolderInterface>()->ToggleOnOff();
		}
		if (InputHandler::IsKeyTriggered(KEY::KEY_P)) {
			GetInterface<DebugInformation>()->ToggleOnOff();
		}

		// render main menu bar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Resources", "[SHIFT+TAB]"))
				{
					GetInterface<FolderInterface>()->ToggleOnOff();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Performance Visualizer", "[TAB]"))
				{
					GetInterface<DebugInformation>()->ToggleOnOff();
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