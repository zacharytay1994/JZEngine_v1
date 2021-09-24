/*	__FILE HEADER__
*	File:	EngineGUI.cpp
	Author: JZ
	Date:	26/08/21
	Brief:	Handles the rendering of the Engine GUI,
			e.g. Inspector, Console, etc.
*/

#include "PCH.h"
#include "EngineGUI.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "../Resource/ResourceManager.h"
#include "../JZGL/JZ_GL.h"

#include "MenuBar.h"
#include "DebugInformation.h"
#include "../Input/Input.h"


namespace JZEngine
{
	EngineGUI::EngineGUI()
		:
		inspector_(5.0f / 6.0f, 1.0f / 46.0f, 1.0f / 6.0f, 45.0f / 46.0f),
		console_(1.0f / 6.0f, 35.0f / 46.0f, 4.0f / 6.0f, 11.0f / 46.0f),
		scene_tree_(0.0f, 1.0f / 46.0f, 1.0f / 6.0f, 45.0f / 46.0f)
	{
		//InitializeWithGLFW();
	}

	EngineGUI::~EngineGUI()
	{
		// clean up imgui
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EngineGUI::Init() 
	{
		InitializeWithGLFW(GetSystem<GLFW_Instance>()->window_);
		inspector_.resource_manager_ = GetSystem<ResourceManager>();
		inspector_.ecs_instance_ = GetSystem<ECS::ECSInstance>();
		scene_tree_.ecs_instance_ = GetSystem<ECS::ECSInstance>();

		AddInterface<DebugInformation>(1.0f / 6.0f, 1.0f / 46.0f, 4.0f / 6.0f, 34.0f / 46.0f);
		AddInterface<MenuBar>(1.0f / 6.0f, 0.0f, 4.0f / 6.0f, 1.0f / 18.0f);
	}

	/*!
	 * @brief ___JZEngine::ToolsGUI::Update()___
	 * ****************************************************************************************************
	 * Updates all imgui gui.
	 * ****************************************************************************************************
	 * @param entity
	 * : Entity for Inspector gui to use.
	 * ****************************************************************************************************
	*/
	void EngineGUI::Update(float dt)
	{
		// start imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// engine gui shortcuts
		if (InputHandler::IsKeyPressed(KEY::KEY_TAB))
		{
			GetInterface<DebugInformation>()->active_ = !GetInterface<DebugInformation>()->active_;
		}

		// render all engine gui parts
		console_.Render();
		scene_tree_.Render();
		inspector_.Render(scene_tree_.selected_entity_);

		for (auto& interface : imgui_interfaces_) {
			interface.second->RenderInterface();
		}

		ImGui::EndFrame();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	/*!
	 * @brief ___JZEngine::ToolsGUI::IntiializeWithGLFW()___
	 * ****************************************************************************************************
	 * Initializes ImGUI with GLFWOpenGL3.
	 * ****************************************************************************************************
	 * @param glfwwindow
	 * : Handle to glfw window created.
	 * ****************************************************************************************************
	*/
	void EngineGUI::InitializeWithGLFW(GLFWwindow*& glfwwindow)
	{
		// initialize imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

	Console* EngineGUI::GetConsole()
	{
		return &console_;
	}
}