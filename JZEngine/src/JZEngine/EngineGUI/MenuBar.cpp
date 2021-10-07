/*	__FILE HEADER__
*	File:		MenuBar.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders the menubar at the top of the engine.
*/

#include <PCH.h>
#include "MenuBar.h"
#include "EngineGUI.h"
#include "../Input/Input.h"

#include "../GraphicRendering/RendererDebug.h"
#include "../DebugTools/PerformanceData.h"
#include "FolderInterface.h"
#include "DebugInformation.h"
#include "EngineSettings.h"

namespace JZEngine {
	float MenuBar::height_{ 0.0f };
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
			height_ = ImGui::GetWindowHeight();
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Resources", "[SHIFT+TAB]"))
				{
					GetInterface<FolderInterface>()->ToggleOnOff();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Settings", "[SHIFT+S]"))
				{
					GetInterface<EngineSettings>()->ToggleOnOff();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::MenuItem("Performance Visualizer", "[TAB]"))
				{
					GetInterface<DebugInformation>()->ToggleOnOff();
				}
				ImGui::Checkbox(": Sprite Outline", &RendererDebug::sprite_outline_);
				ImGui::Checkbox(": Debug Shapes", &RendererDebug::draw_debug_);
				ImGui::SetNextItemWidth(50.0f);
				ImGui::SliderFloat(": Point Size", &RendererDebug::point_size_, 1.0f, 20.0f);
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