/*	__FILE HEADER__
*	File:	EngineGUI.h
	Author: JZ
	Date:	26/08/21
	Brief:	Handles the rendering of the Engine GUI,
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

#include "Inspector.h"
//#include "Console.h"
#include "SceneTree.h"

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
		void AddInterface(float x, float y, float sx, float sy) {
			imgui_interfaces_[typeid(INTERFACE).name()] = std::make_shared<INTERFACE>(x, y, sx, sy);
			imgui_interfaces_[typeid(INTERFACE).name()]->SetEngineGUI(this);
		}

		template <typename INTERFACE>
		std::shared_ptr<INTERFACE> GetInterface() {
			if (imgui_interfaces_.find(typeid(INTERFACE).name()) != imgui_interfaces_.end()) {
				return std::dynamic_pointer_cast<INTERFACE>(imgui_interfaces_[typeid(INTERFACE).name()]);
			}
			return nullptr;
		}

		Console* GetConsole();
	private:
		Inspector	inspector_;		/*!< engine inspector */
		Console		console_;		/*!< engine console */
		SceneTree	scene_tree_;	/*!< engine console */
		std::unordered_map<std::string, std::shared_ptr<ImGuiInterface>> imgui_interfaces_;

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