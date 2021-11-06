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

#include "../GraphicRendering/RendererDebug.h"
#include "../DebugTools/PerformanceData.h"
#include "FolderInterface.h"
#include "DebugInformation.h"
#include "EngineSettings.h"
#include "../GraphicRendering/Camera.h"

#define UNREFERENCED_PARAMETER(P)(P);

namespace JZEngine {
	float MenuBar::height_{ 0.0f };
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
					/*GetInterface<EngineSettings>()->temp_cam_x = Settings::camera_width;
					GetInterface<EngineSettings>()->temp_cam_y = Settings::camera_height;*/
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

			ImGui::SameLine();
			ImGui::Text(" | App FPS: %4d", PerformanceData::average_app_fps_);
			ImGui::SameLine();
			ImGui::Text(" | Process FPS: %4d |", PerformanceData::average_fps_);

			ImGui::SetNextItemWidth(100.0f);
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
			}

			if (ImGui::Button("Fullscreen"))
			{
				Camera::fullscreen = !Camera::fullscreen;
				GLFW_Instance::UpdateViewportDimensions();
				Log::Info("Main", "Toggle fullscreen: {}", Camera::fullscreen);
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::SetNextWindowPos({ 0.0f, menubar_height }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width), menubar_height * 2.0f }, ImGuiCond_Always);
		ImGui::Begin("playbar", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImGui::SameLine(Settings::window_width / 2.0f - (menubar_height * 1.5f));
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconstart")->GetRendererID()), {menubar_height * 0.8f, menubar_height * 0.8f}))
		{
			// start code
		}
		ImGui::SameLine(Settings::window_width / 2.0f);
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconstop")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }))
		{
			// stop code
		}
		ImGui::SameLine(Settings::window_width / 2.0f + (menubar_height * 1.5f));
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconpause")->GetRendererID()), { menubar_height * 0.8f, menubar_height * 0.8f }))
		{
			// pause code
		}

		ImGui::End();

		height_ = menubar_height * 3.0f;
	} 
}