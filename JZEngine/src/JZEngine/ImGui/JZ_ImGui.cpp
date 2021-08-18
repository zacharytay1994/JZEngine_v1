#include "PCH.h"
#include "JZ_ImGui.h"

#include "../ECS/ECSConfig.h"
#include "../STL/Tuple.h"

namespace JZEngine
{
	ToolsGUI::ToolsGUI(GLFWwindow*& glfwwindow)
	{
		InitializeWithGLFW(glfwwindow);
	}

	ToolsGUI::~ToolsGUI()
	{
		// clean up imgui
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ToolsGUI::Update(ECS::Entity& entity)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		RenderInspector(entity);

		ImGui::Begin("Demo window 2");
		ImGui::Button("Hello!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ToolsGUI::InitializeWithGLFW(GLFWwindow*& glfwwindow)
	{
		// initialize imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

	void ToolsGUI::RenderInspector(ECS::Entity& entity)
	{
		ImGui::Begin("Inspector");
		for (int i = 0; i < ECS::MAX_COMPONENTS; ++i)
		{
			if (entity.owning_chunk_->owning_archetype_->mask_[i])
			{
				LoopTuple(ECS::ECSConfig::Component(), i, entity);
			}
		}
		//RenderComponent<TestComponent>(entity.GetComponent<TestComponent>());
		ImGui::End();
	}
}