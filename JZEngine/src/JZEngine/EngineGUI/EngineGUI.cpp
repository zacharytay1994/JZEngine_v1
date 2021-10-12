/*	__FILE HEADER__
*	File:		EngineGUI.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Handles the rendering of the Engine GUI,
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
#include "EngineSettings.h"
#include "../Input/Input.h"
#include "../Math/JZMath.h"


namespace JZEngine
{
	//Mat4f view;
	//Mat4f projection;
	//Mat4f transform; //{ {100, 0, 0, 0}, { 0,100,0,0 }, { 0,0,1,0 }, { 0,0,0,1 }};
	Mat3f EngineGUI::camera_transform_;
	EngineGUI::EngineGUI()
		:
		inspector_(5.0f / 6.0f, 1.0f / 46.0f, 1.0f / 6.0f, 45.0f / 46.0f),
		console_(1.0f / 6.0f, 3.0f / 4.0f, 4.0f / 6.0f, 1.0f / 4.0f),
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
		ecs_instance_ = GetSystem<ECS::ECSInstance>();

		// add imgui interfaces
		AddInterface<MenuBar>(1.0f / 6.0f, 0.0f, 4.0f / 6.0f, 1.0f / 18.0f, 0);
		GetInterface<MenuBar>()->active_ = true;
		AddInterface<DebugInformation>(1.0f / 6.0f, 0.0f, 4.0f / 6.0f, 3.0f / 4.0f, 1);
		AddInterface<FolderInterface>(1.0f / 6.0f, 0.0f, 4.0f / 6.0f, 3.0f / 4.0f, 1);
		GetInterface<FolderInterface>()->ecs_instance_ = GetSystem<ECS::ECSInstance>();
		GetInterface<FolderInterface>()->scene_tree_ =	&scene_tree_;
		AddInterface<EngineSettings>(1.0f / 6.0f, 0.0f, 4.0f / 6.0f, 3.0f / 4.0f, 1);
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
				//ImGuiIO& io = ImGui::GetIO();
				ImGuizmo::SetRect(static_cast<float>(1.0 / 6.0 * Settings::window_width), MenuBar::height_, static_cast<float>(4.0 / 6.0 * Settings::window_width), static_cast<float>(3.0 / 4.0 * (Settings::window_height - MenuBar::height_)));
				Mat4f projection = static_cast<Mat4f>(Math::GetProjectionTransformNonTransposed()).Transpose();
				Mat4f view = Mat4f::Translate(-camera_position_.x, -camera_position_.y, 0.0f).Transpose();

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

		if (!GLFW_Instance::dimensions_updated)
		{
			GLFW_Instance::UpdateViewportDimensions();
			GLFW_Instance::dimensions_updated = true;
		}

		ProcessCameraInput();

		camera_transform_ = Math::GetModelTransformNonTransposed(-camera_position_, 0.0f, { camera_zoom_, camera_zoom_ }, { 1.0f, 1.0f });
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
		//ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

	Console* EngineGUI::GetConsole()
	{
		return &console_;
	}

	Mat3f EngineGUI::GetCameraTransform()
	{
		return camera_transform_;
	}

	void EngineGUI::ProcessCameraInput()
	{
		GLFWwindow* window = GetSystem<GLFW_Instance>()->window_;
		if (!window)
		{
			return;
		}
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Vec2f screen_position_ = { static_cast<float>(x), static_cast<float>(y) };
		if (InputHandler::IsMouseTriggered(MOUSE::MOUSE_BUTTON_2))
		{
			camera_record_world_ = camera_position_;
			camera_record_screen_ = screen_position_;
			camera_locked = true;
		}
		if (InputHandler::IsMousePressed(MOUSE::MOUSE_BUTTON_2))
		{
			Vec2f offset = screen_position_ - camera_record_screen_;
			offset.x = (offset.x / Settings::window_width) * Settings::camera_width * 1.5f;
			//offset.y = (offset.y / Settings::window_height) * Settings::camera_height * 1.5f;
			offset.y = -(((offset.y / Settings::window_height)) / (0.375f * (1.0f - (MenuBar::height_ / Settings::window_height)))) * 0.5f * Settings::camera_height;
			camera_position_ = camera_record_world_ - offset;
		}
		if (InputHandler::IsMouseReleased(MOUSE::MOUSE_BUTTON_2))
		{
			camera_locked = false;
		}

		// convert mouse into world coordinates
		mouse_world_position_.x = ((screen_position_.x / Settings::window_width) - 0.5f) * Settings::camera_width * 1.5f;
		float percent = (MenuBar::height_ / Settings::window_height) + (0.375f * (1.0f - (MenuBar::height_ / Settings::window_height)));
		mouse_world_position_.y = (-(((screen_position_.y / Settings::window_height) - percent) / (0.375f * (1.0f - (MenuBar::height_ / Settings::window_height)))) * 0.5f) * Settings::camera_height;
		//Log::Info("MousePress", "y: {}", mouse_world_position_.y);
		//mouse_world_position_.y = (screen_position_.y / Settings::window_height)
		mouse_world_position_.x += camera_position_.x;
		mouse_world_position_.y += camera_position_.y;
		//Log::Info("MousePress", "x: {}, y: {}", mouse_world_position_.x, mouse_world_position_.y);

		// check all entities with transforms
		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_SHIFT) && InputHandler::IsMouseTriggered(MOUSE::MOUSE_BUTTON_1))
		{
			for (auto& e : ecs_instance_->entity_manager_.entities_)
			{
				if (e.HasComponent(0))
				{
					Transform& transform = e.GetComponent<Transform>();
					// do bounding box check
					float half_width = ((transform.scale_.x * transform.size_.x) / 2.0f);
					float half_height = ((transform.scale_.y * transform.size_.y) / 2.0f);
					float left = transform.position_.x - half_width;
					float right = transform.position_.x + half_width;
					float top = transform.position_.y + half_height;
					float bottom = transform.position_.y - half_height;
					// check if mouse point within it
					if (!(mouse_world_position_.x < left || mouse_world_position_.x > right || mouse_world_position_.y > top || mouse_world_position_.y < bottom))
					{
						scene_tree_.selected_entity_ = &e;
					}
				}
			}
		}

		if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_CONTROL) && InputHandler::mouse_scrolled_ == -1)
		{
			Settings::camera_width += 100;
			Settings::camera_height += static_cast<int>(100 * Settings::aspect_ratio);
		}
		else if (InputHandler::IsKeyPressed(KEY::KEY_LEFT_CONTROL) && InputHandler::mouse_scrolled_ == 1)
		{
			Settings::camera_width -= 100;
			Settings::camera_height -= static_cast<int>(100 * Settings::aspect_ratio);
		}
	}
}