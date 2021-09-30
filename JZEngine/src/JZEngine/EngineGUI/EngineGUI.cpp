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
#include "Console.h"
#include "FolderInterface.h"
#include "../Input/Input.h"
#include "../Math/JZMath.h"


namespace JZEngine
{
	//Mat4f view;
	//Mat4f projection;
	//Mat4f transform; //{ {100, 0, 0, 0}, { 0,100,0,0 }, { 0,0,1,0 }, { 0,0,0,1 }};
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

		// add imgui interfaces
		AddInterface<MenuBar>(1.0f / 6.0f, 0.0f, 4.0f / 6.0f, 1.0f / 18.0f, 0);
		AddInterface<DebugInformation>(1.0f / 6.0f, 1.0f / 46.0f, 4.0f / 6.0f, 34.0f / 46.0f, 1);
		GetInterface<DebugInformation>()->active_ = false;
		AddInterface<FolderInterface>(1.0f / 6.0f, 1.0f / 46.0f, 4.0f / 6.0f, 34.0f / 46.0f, 1);
		GetInterface<FolderInterface>()->active_ = false;
		GetInterface<FolderInterface>()->ecs_instance_ = GetSystem<ECS::ECSInstance>();
		GetInterface<FolderInterface>()->scene_tree_ =	&scene_tree_;
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
		ImGuizmo::BeginFrame();

		// engine gui shortcuts
		/*if (InputHandler::IsKeyPressed(KEY::KEY_TAB))
		{
			GetInterface<DebugInformation>()->active_ = !GetInterface<DebugInformation>()->active_;
		}*/

		// render all engine gui parts
		console_.Render();
		scene_tree_.Render();
		inspector_.Render(scene_tree_.selected_entity_);

		for (auto& interface : imgui_interfaces_) {
			interface.second.interface_->RenderInterface(dt);
		}

		if (scene_tree_.selected_entity_)
		{
			// for now hardcoded as if has transform
			if (scene_tree_.selected_entity_->HasComponent(0))
			{
				ImGuizmo::SetOrthographic(true);
				ImGuiIO& io = ImGui::GetIO();
				ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
				Mat4f projection = static_cast<Mat4f>(Math::GetProjectionTransformNonTransposed()).Transpose();
				Mat4f view;

				Transform& transform = scene_tree_.selected_entity_->GetComponent<Transform>();
				Mat4f m4_translation = Mat4f::Translate(transform.position_.x, transform.position_.y, 0.0f);
				Mat4f m4_rotation = Mat4f::RotateZ(Math::DegToRad(transform.rotation_));
				Mat4f m4_scale = Mat4f::Scale(transform.scale_.x, transform.scale_.y, 1.0f);
				Mat4f m4_transform = m4_translation * (m4_rotation * m4_scale);
				m4_transform.Transpose();

				ImGuizmo::Manipulate(view.data_[0], projection.data_[0], operation_, ImGuizmo::MODE::LOCAL, m4_transform.data_[0]);

				float translation[3] = { transform.position_.x, transform.position_.y, 1.0f };
				float rotation[3] = { 0.0f, 0.0f, transform.rotation_ };
				float scale[3] = { transform.scale_.x, transform.scale_.y, 1.0f };
				ImGuizmo::DecomposeMatrixToComponents(m4_transform.data_[0], translation, rotation, scale);

				transform.position_ = { translation[0], translation[1] };
				transform.rotation_ = rotation[2];
				transform.scale_ = { scale[0], scale[1] };
			}
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void EngineGUI::CloseAllGroupedInterface(int group) {
		for (auto& i : imgui_interfaces_) {
			if (i.second.group_ == group) {
				i.second.interface_->active_ = false;
			}
		}
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
		ImGuizmo::SetImGuiContext(ImGui::CreateContext());
		//ImGui::CreateContext();
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