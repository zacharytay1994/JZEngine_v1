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
#include "../JZGL/JZ_GL.h"

#include "../GraphicRendering/Renderers/RendererDebug.h"
#include "../DebugTools/PerformanceData.h"
#include "FolderInterface.h"
#include "DebugInformation.h"
#include "EngineSettings.h"
#include "../GraphicRendering/Camera.h"

#define UNREFERENCED_PARAMETER(P)(P);

namespace JZEngine {
	float MenuBar::height_{ 0.0f };
	bool MenuBar::light_theme_{ true };
	MenuBar::MenuBar(float x, float y, float sx, float sy, int group) 
		:
		ImGuiInterface(x, y, sx, sy, group)
	{
	}

	void MenuBar::Render(float dt) {
		UNREFERENCED_PARAMETER(dt);
		// shortcuts
		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_SHIFT) && InputHandler::IsKeyTriggered(KEY::KEY_TAB)) {
			GetInterface<FolderInterface>()->ToggleOnOff();
		}
		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_SHIFT) && InputHandler::IsKeyTriggered(KEY::KEY_P)) {
			GetInterface<DebugInformation>()->ToggleOnOff();
		}
		if (InputHandler::IsKeyTriggered(KEY::KEY_ESCAPE))
		{
			GetInterface<EngineSettings>()->ToggleOnOff();
		}
		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_SHIFT) && InputHandler::IsKeyTriggered(KEY::KEY_T))
		{
			transform_mode_ = "Transform Mode: Translate";
			engine_gui_->operation_ = ImGuizmo::OPERATION::TRANSLATE;
		}
		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_SHIFT) && InputHandler::IsKeyTriggered(KEY::KEY_R))
		{
			transform_mode_ = "Transform Mode: Rotate";
			engine_gui_->operation_ = ImGuizmo::OPERATION::ROTATE_Z;
		}
		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_SHIFT) && InputHandler::IsKeyTriggered(KEY::KEY_S))
		{
			transform_mode_ = "Transform Mode: Scale";
			engine_gui_->operation_ = ImGuizmo::OPERATION::SCALE;
		}

		float menubar_height = 0.0f;
		// render main menu bar
		if (ImGui::BeginMainMenuBar())
		{
			menubar_height = ImGui::GetWindowHeight();
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Resources", "[SHIFT+TAB]"))
				{
					GetInterface<FolderInterface>()->ToggleOnOff();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Settings", "[ESC]"))
				{
					GetInterface<EngineSettings>()->temp_width_ = Settings::window_width;
					GetInterface<EngineSettings>()->temp_height_ = Settings::window_height;
					GetInterface<EngineSettings>()->ToggleOnOff();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::MenuItem("Performance Visualizer", "[SHIFT+P]"))
				{
					GetInterface<DebugInformation>()->ToggleOnOff();
				}
				ImGui::Checkbox(": Sprite Outline", &RendererDebug::sprite_outline_);
				ImGui::Checkbox(": Debug Shapes", &RendererDebug::draw_debug_);
				ImGui::SetNextItemWidth(50.0f);
				ImGui::SliderFloat(": Point Size", &RendererDebug::point_size_, 1.0f, 20.0f);
				ImGui::EndMenu();
			}

			if (more_info_)
			{
				ImGui::SameLine(Settings::window_width - 200.0f);
				ImGui::Text("FPS: %4d | True FPS: %4d", PerformanceData::average_app_fps_, PerformanceData::average_fps_);
			}

			ImGui::SameLine(Settings::window_width - menubar_height * 1.6f);
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("extraicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
			{
				more_info_ = !more_info_;
			}

			/*ImGui::SameLine();
			if (ImGui::BeginMenu(transform_mode_.c_str()))
			{
				if (ImGui::MenuItem("Translate", "[SHIFT+T]"))
				{
					transform_mode_ = "Transform Mode: Translate";
					engine_gui_->operation_ = ImGuizmo::OPERATION::TRANSLATE;
				}
				if (ImGui::MenuItem("Rotate", "[SHIFT+R]"))
				{
					transform_mode_ = "Transform Mode: Rotate";
					engine_gui_->operation_ = ImGuizmo::OPERATION::ROTATE_Z;
				}
				if (ImGui::MenuItem("Scale", "[SHIFT+S]"))
				{
					transform_mode_ = "Transform Mode: Scale";
					engine_gui_->operation_ = ImGuizmo::OPERATION::SCALE;
				}
				ImGui::EndMenu();
			}*/

			ImGui::EndMainMenuBar();
		}

		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::SetNextWindowPos({ 0.0f, menubar_height }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width), menubar_height * 2.0f }, ImGuiCond_Always);
		ImGui::Begin("playbar", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("textfileicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			GetInterface<FolderInterface>()->ToggleOnOff();
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Resource Manager");
			ImGui::EndTooltip();
		}

		ImGui::SameLine();
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("barcharticon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			GetInterface<DebugInformation>()->ToggleOnOff();
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Performance Visualizer");
			ImGui::EndTooltip();
		}
		
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("settingicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			GetInterface<EngineSettings>()->temp_width_ = Settings::window_width;
			GetInterface<EngineSettings>()->temp_height_ = Settings::window_height;
			GetInterface<EngineSettings>()->ToggleOnOff();
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Settings");
			ImGui::EndTooltip();
		}

		ImGui::SameLine();
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("fullscreenicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			Camera::fullscreen = !Camera::fullscreen;
			GLFW_Instance::UpdateViewportDimensions();
			Log::Info("Main", "Toggle fullscreen: {}", Camera::fullscreen);
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Fullscreen");
			ImGui::EndTooltip();
		}

		ImGui::SameLine();
		ImGui::Text("|");

		ImGui::SameLine();
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("translateicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			engine_gui_->operation_ = ImGuizmo::OPERATION::TRANSLATE;
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Translate, [SHIFT+T]");
			ImGui::EndTooltip();
		}

		ImGui::SameLine();
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("scaleicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			engine_gui_->operation_ = ImGuizmo::OPERATION::SCALE;
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Scale, [SHIFT+S]");
			ImGui::EndTooltip();
		}

		ImGui::SameLine();
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("rotateicon")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			engine_gui_->operation_ = ImGuizmo::OPERATION::ROTATE_Z;
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Rotate, [SHIFT+R]");
			ImGui::EndTooltip();
		}

		ImGui::SameLine(Settings::window_width / 2.0f - (menubar_height * 1.5f));
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconstart")->GetRendererID()), {menubar_height * 0.8f, menubar_height * 0.8f}, { 0,1 }, { 1,0 }))
		{
			// start code
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Play");
			ImGui::EndTooltip();
		}
		ImGui::SameLine(Settings::window_width / 2.0f);
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconstop")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			// stop code
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Stop");
			ImGui::EndTooltip();
		}
		ImGui::SameLine(Settings::window_width / 2.0f + (menubar_height * 1.5f));
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconpause")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }, { 0,1 }, { 1,0 }))
		{
			// pause code
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Pause");
			ImGui::EndTooltip();
		}

		ToggleButton("testtogglebutton", &light_theme_);

		ImGui::End();

		height_ = menubar_height * 3.0f;
	} 

	void MenuBar::ToggleButton(const char* str_id, bool* v)
	{
		ImGui::SameLine(Settings::window_width - 40.0f);
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
			*v = !*v;
		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = *v ? IM_COL32(218 - 20, 218 - 20, 218 - 20, 255) : IM_COL32(145 + 20, 68, 211 + 20, 255);
		else
			col_bg = *v ? IM_COL32(218, 218, 218, 255) : IM_COL32(145, 68, 211, 255);

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
	}
}