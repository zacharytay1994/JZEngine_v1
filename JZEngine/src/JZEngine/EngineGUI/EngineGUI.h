/*	__FILE HEADER__
*	File:		EngineGUI.h
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Handles the rendering of the Engine GUI,
				e.g. Inspector, Console, etc.
*/
#pragma once

#include <memory>
#include <unordered_map>

#include "../BuildDefinitions.h"
#include "../GlobalSystems.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"

#include "../ImGui/imgui_impl_opengl3.h"
#include "../ImGui/ImGuizmo.h"

#include "Inspector.h"
//#include "Console.h"
#include "SceneTree.h"

#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::EngineGUI___
	 * ****************************************************************************************************
	 * In charge of rendering the Engine graphical user interface with ImGui.
	 * ****************************************************************************************************
	*/
	struct ImGuiInterface;
	struct ResourceManager;
	namespace ECS { struct ECSInstance; }
	struct EngineGUI : public GlobalSystem
	{
		EngineGUI();
		~EngineGUI();

		virtual void Init() override;

		/*!
		 * @brief ___JZEngine::ToolsGUI::Update()___
		 * ****************************************************************************************************
		 * Updates all imgui gui.
		 * ****************************************************************************************************
		 * @param entity 
		 * : Entity for Inspector gui to use.
		 * ****************************************************************************************************
		*/
		virtual void Update(float dt) override;

		template <typename INTERFACE>
		void AddInterface(float x, float y, float sx, float sy, int group = -1) {
			imgui_interfaces_[typeid(INTERFACE).name()] = { group, std::make_shared<INTERFACE>(x, y, sx, sy, group) };
			imgui_interfaces_[typeid(INTERFACE).name()].interface_->SetEngineGUI(this);
			imgui_interfaces_[typeid(INTERFACE).name()].interface_->active_ = false;
		}

		template <typename INTERFACE>
		std::shared_ptr<INTERFACE> GetInterface() {
			if (imgui_interfaces_.find(typeid(INTERFACE).name()) != imgui_interfaces_.end()) {
				return std::dynamic_pointer_cast<INTERFACE>(imgui_interfaces_[typeid(INTERFACE).name()].interface_);
			}
			return nullptr;
		}

		void CloseAllGroupedInterface(int group);

		Console* GetConsole();
		ImGuizmo::OPERATION operation_{ ImGuizmo::OPERATION::TRANSLATE };

		static Mat3f GetCameraTransform();
		//float camera_zoom_{ 1.0f };

	private:
		Inspector	inspector_;		/*!< engine inspector */
		Console		console_;		/*!< engine console */
		SceneTree	scene_tree_;	/*!< engine console */

		ECS::ECSInstance* ecs_instance_{ nullptr };
		// scene camera
		//Vec2f camera_position_{ 0.0f, 0.0f };
		//static Mat3f camera_transform_;
		bool camera_locked{ false };
		Vec2f camera_record_world_;
		Vec2f camera_record_screen_;
		//Vec2f mouse_world_position_;
		void ProcessCameraInput();
		
		struct InterfaceGroup {
			int group_{ -1 };
			std::shared_ptr<ImGuiInterface> interface_{ nullptr };
		};
		std::unordered_map<std::string, InterfaceGroup> imgui_interfaces_;

		/*!
		 * @brief ___JZEngine::ToolsGUI::IntiializeWithGLFW()___
		 * ****************************************************************************************************
		 * Initializes ImGUI with GLFWOpenGL3.
		 * ****************************************************************************************************
		 * @param glfwwindow 
		 * : Handle to glfw window created.
		 * ****************************************************************************************************
		*/
		void InitializeWithGLFW(GLFWwindow*& glfwwindow);
	};
}