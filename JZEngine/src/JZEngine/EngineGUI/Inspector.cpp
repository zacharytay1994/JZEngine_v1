/*	__FILE HEADER__
*	File:		Inspector.cpp
	Primary:	Zachary Tay
	Secondary:	Jee Jia Min
	Date:		26/08/21
	Brief:		Renders all components of a selected entity
				in the engine GUI with ImGui.
*/

#include "PCH.h"
#include "Inspector.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"
#include "MenuBar.h"

namespace JZEngine
{
	void PrintSystemAffected(std::string const& name)
	{
		ImGui::Text(name.c_str() + Inspector::TrimName(name));
	}

	Inspector::Inspector(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{

	}

	/*!
	 * @brief ___JZEngine::ToolsGUI::RenderInspector()___
	 * ****************************************************************************************************
	 * ImGUI window for the inspector, entity details.
	 * ****************************************************************************************************
	 * @param entity
	 * : The entity of which to display the details.
	 * ****************************************************************************************************
	*/
	void Inspector::Render(ECS::Entity* const entity)
	{
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, MenuBar::height_ }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height - MenuBar::height_)}, ImGuiCond_Always);

		// start rendering the inspector
		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button("Components"))
			{
				component_view_ = true;
			}

			if (ImGui::Button("Add Systems"))
			{
				component_view_ = false;
			}

			ImGui::SameLine(ImGui::GetWindowWidth() - 45.0f);
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("saveicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 } , -1 , { 0,0,0,0 } , EngineGUI::icon_col_ ))
			{
				if (entity)
				{
					confirmation_flag_ = Confirmation::SERIALIZE;
				}
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("Save selected object as prefab.");
				ImGui::EndTooltip();
			}

			ImGui::EndMenuBar();
		}

		/*if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("saveicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 }))
		{
			if (entity)
			{
				confirmation_flag_ = Confirmation::SERIALIZE;
			}
		}
		ImGui::Separator();*/

		// renders all registered components and systems 
		if (!component_view_)
		{
			if (entity)
			{
				ImGui::Text("Select a system to add.");
			}
			else
			{
				ImGui::Text("First select an object.");
			}
			ImGui::Separator();
			TreeNodeComponentsAndSystems(entity);
		}
		else
		{
			// if there is selected entity
			if (entity)
			{
				/*std::stringstream ss;
				ss << "Components of [" << entity->name_ << "] [ID: " << entity->entity_id_ << "]";
				ImGui::Text(ss.str().c_str());*/
				ImGui::Text("Edit component properties here.");
				ImGui::Separator();

				// if entity has a chunk, i.e. has component before
				if (entity->owning_chunk_)
				{
					bool flag = entity->GetFlag();
					ImGui::Checkbox(": Active", &flag);
					entity->FlagActive(flag);

					bool has_component_ = false;
					for (int i = 0; i < ECS::MAX_COMPONENTS; ++i)
					{
						if (entity->owning_chunk_->owning_archetype_->mask_[i])
						{
							has_component_ = true;
							ImGui::SetNextItemOpen(true, ImGuiCond_Once);

							// renders all components using their specialization
							LoopTupleRender(ECS::ECSConfig::Component(), i, *entity);
							ImGui::Separator();
						}
					}
					if (!has_component_)
					{
						ImGui::Text("No components found...");
						ImGui::Text("Try adding some systems...");
					}
				}
				else
				{
					ImGui::Text("No components found...");
					ImGui::Text("Try adding some systems...");
				}
			}
			else
			{
				ImGui::Text("Edit component properties here.\n");
				ImGui::Separator();
				ImGui::Text("No object selected...");
			}
		}

		//ImGui::NewLine();
		//ImGui::SameLine(ImGui::GetWindowWidth() / 2 - 50.0f);
		//if (ImGui::Button("Serialize", ImVec2(100.0f, 0.0f)))
		//{
		//	if (entity)
		//	{
		//		/*if (!Serialize::SerializeEntity(*entity))
		//		{
		//			Log::Warning("Resource", "Serializing failed!");
		//		}*/
		//		confirmation_flag_ = Confirmation::SERIALIZE;
		//	}
		//}
		ImGui::End();

		if (confirmation_flag_ == Confirmation::SERIALIZE)
		{
			RenderConfirmation(entity);
		}
	}

	/*!
	 * @brief ___JZEngine::ToolsGUI::TreeNodeComponentAndSystems()___
	 * ****************************************************************************************************
	 * Creates an ImGUI tree node of all registered
	 * components and systems in the engine. Called
	 * in RenderInspector. It is part of the inspector
	 * display.
	 * ****************************************************************************************************
	*/
	void Inspector::TreeNodeComponentsAndSystems(ECS::Entity* const entity)
	{
		if (entity)
		{
			//if (ImGui::BeginListBox("##[Sys]", { 0, ImGui::GetWindowHeight() / 3.0f }))
			//{
			//	// render all registered systems in a listbox
			//	for (auto& s : ecs_instance_->system_manager_.registered_systems_)
			//	{
			//		bool has_system_ = true;

			//		// check if the selected entity has the components of the system already added, if so mark green
			//		for (auto& c : ecs_instance_->system_manager_.system_database_[s.id_]->components_)
			//		{
			//			if (c != -1)
			//			{
			//				has_system_ = has_system_ ? entity->HasComponent(c) : false;
			//			}
			//			else
			//			{
			//				break;
			//			}
			//		}
			//		//if (has_system_)
			//		//{
			//		//	ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f,1.0f,0.0f,1.0f });
			//		//}

			//		//// if system selected
			//		//if (ImGui::Selectable(s.name_.c_str() + TrimName(s.name_), true))
			//		//{
			//		//	// add the system components to the selected entity is any are missing
			//		//	if (!has_system_)
			//		//	{
			//		//		entity->AddSystem(s.id_);
			//		//		//ecs_instance_->Print();
			//		//	}
			//		//}
			//		//if (has_system_)
			//		//{
			//		//	has_system_ = false;
			//		//	ImGui::PopStyleColor(1);
			//		//}

			//		ImGui::Checkbox(s.name_.c_str() + TrimName(s.name_), &has_system_);
			//		if (has_system_)
			//		{
			//			has_system_ = false;
			//		}
			//	}
			//	ImGui::EndListBox();
			//}
			// render all registered systems in a listbox
			for (auto& s : ecs_instance_->system_manager_.registered_systems_)
			{
				bool has_system_ = true;

				// check if the selected entity has the components of the system already added, if so mark green
				for (auto& c : ecs_instance_->system_manager_.system_database_[s.id_]->components_)
				{
					if (c != -1)
					{
						has_system_ = has_system_ ? entity->HasComponent(c) : false;
					}
					else
					{
						break;
					}
				}

				bool temp{ has_system_ };
				ImGui::Checkbox(s.name_.c_str() + TrimName(s.name_), &temp);
				if (temp != has_system_)
				{
					if (temp)
					{
						entity->AddSystem(s.id_);
					}
					else
					{
						entity->RemoveSystem(s.id_);
					}
				}
				if (has_system_)
				{
					has_system_ = false;
				}
			}
		}
		// if no selected entity case, print default messages
		else
		{
			//if (ImGui::BeginListBox("##[Sys]", { 0, ImGui::GetWindowHeight() / 3.0f }))
			//{
			//	for (auto& s : ecs_instance_->system_manager_.registered_systems_)
			//	{
			//		if (ImGui::Selectable(s.name_.c_str() + TrimName(s.name_), true))
			//		{
			//			//Console::Log("Oops please select an entity before adding...");
			//		}

			//		bool temp = false;
			//		ImGui::Checkbox(s.name_.c_str() + TrimName(s.name_), &temp);
			//	}
			//	ImGui::EndListBox();
			//}
			for (auto& s : ecs_instance_->system_manager_.registered_systems_)
			{
				bool temp = false;
				ImGui::Checkbox(s.name_.c_str() + TrimName(s.name_), &temp);
			}
		}
	}

	int Inspector::TrimName(const std::string& name)
	{
		int count{ 0 };
		bool colon{ false };
		for (auto& c : name)
		{
			if (c == ':')
			{
				if (!colon)
				{
					colon = true;
				}
				else
				{
					return ++count;
				}
			}
			++count;
		}
		return 0;
	}

	template <typename... ARGS>
	void TextCenter(std::string text, ARGS...args) {
		float font_size = ImGui::GetFontSize() * text.size() / 2;
		ImGui::SameLine(
			ImGui::GetWindowSize().x / 2 -
			font_size + (font_size / 2)
		);

		ImGui::Text(text.c_str(), args...);
		ImGui::NewLine();
	}

	void Inspector::RenderConfirmation(ECS::Entity* const entity) {
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * (1.0f / 3.0f), static_cast<float>(Settings::window_height) * (1.0f / 3.0f) }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * (1.0f / 3.0f), static_cast<float>(Settings::window_height) * (1.0f / 5.0f) }, ImGuiCond_Once);

		ImGui::Begin("SceneTree Confirmation", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		if (ImGui::BeginTable("Confirmation Table", 1)) {
			ImGui::TableNextColumn();
			bool name_exists_{ false };
			std::stringstream final_name;
			switch (confirmation_flag_) {
			case Confirmation::SERIALIZE:
				TextCenter("[SERIALIZING OBJECT]");
				TextCenter("You are about to save the current object as:");
				if (rename_buffer_[0] == '\0') {
					TextCenter(entity->name_.c_str());
				}
				else {
					TextCenter(rename_buffer_);
				}

				ImGui::SameLine(ImGui::GetWindowSize().x / 2 - 100.0f);
				ImGui::PushItemWidth(200.0f);
				ImGui::InputText("##Rename", rename_buffer_, 64);
				ImGui::PopItemWidth();
				ImGui::SameLine();
				ImGui::Text(": Rename");
				// check if input name already exists and warn the user
				if (rename_buffer_[0] == '\0') {
					final_name << entity->name_;
				}
				else {
					final_name << rename_buffer_;
				}
				for (auto& e : Serialize::entities_) {
					if (e.first == final_name.str()) {
						name_exists_ = true;
					}
				}
				if (name_exists_) {
					ImGui::NewLine();
					TextCenter("A saved object already exists, do you want to overwrite existing?");
				}
				else {
					ImGui::NewLine();
					TextCenter("...");
				}
				ImGui::NewLine();
				ImGui::SameLine(ImGui::GetWindowSize().x / 4 - 50.0f);
				if (ImGui::Button("Confirm", ImVec2(100.0f, 0.0f))) {
					if (rename_buffer_[0] == '\0') {
						Serialize::SerializeEntity(ecs_instance_, *entity);
					}
					else {
						std::string temp = entity->name_;
						entity->name_ = final_name.str();
						if (Serialize::SerializeEntity(ecs_instance_, *entity)) {
							Log::Warning("Resource", "Serializing entity {} failed!", final_name.str());
						}
						entity->name_ = temp;
					}
					confirmation_flag_ = Confirmation::NONE;
				}
				ImGui::SameLine(ImGui::GetWindowSize().x / 4 * 3 - 50.0f);
				if (ImGui::Button("Cancel", ImVec2(100.0f, 0.0f))) {
					confirmation_flag_ = Confirmation::NONE;
				}
				break;
			}
			ImGui::EndTable();
		}
		ImGui::End();
	}
}