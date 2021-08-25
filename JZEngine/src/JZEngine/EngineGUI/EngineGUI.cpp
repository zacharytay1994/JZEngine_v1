#include "PCH.h"
#include "EngineGUI.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{

	EngineGUI::EngineGUI(GLFWwindow*& glfwwindow)
		:
		inspector_(5.0f/6.0f, 0.0f, 1.0f/6.0f, 1.0f),
		console_(1.0f/6.0f, 5.0f/6.0f, 4.0f/6.0f, 1.0f/6.0f),
		scene_tree_(0.0f, 0.0f, 1.0f / 6.0f, 1.0f)
	{
		InitializeWithGLFW(glfwwindow);
	}

	EngineGUI::~EngineGUI()
	{
		// clean up imgui
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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
	void EngineGUI::Update()
	{
		// start imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render all imgui stuff
		console_.Render();
		scene_tree_.Render();
		inspector_.Render(scene_tree_.selected_entity_);

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
}