/*	__FILE HEADER__
*	File:	Inspector.cpp
	Author: JZ
	Date:	26/08/21
	Brief:	Renders all components of a selected entity
			in the engine GUI with ImGui.
*/

#include "PCH.h"
#include "Inspector.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"

namespace JZEngine
{
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
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, static_cast<float>(Settings::window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height) * sy_ }, ImGuiCond_Once);

		// start rendering the inspector
		ImGui::Begin("Inspector");

		// renders all registered components and systems 
		TreeNodeComponentsAndSystems(entity);
		ImGui::PushStyleColor(ImGuiCol_Separator, { 0.8f,0.8f,0.8f,1.0f });
		ImGui::Separator();
		ImGui::PopStyleColor();

		// if there is selected entity
		if (entity)
		{
			std::stringstream ss;
			ss << "Components of [" << entity->name_ << "] [ID: " << entity->entity_id_ << "]";
			ImGui::Text(ss.str().c_str());
			
			// if entity has a chunk, i.e. has component before
			if (entity->owning_chunk_)
			{
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
					ImGui::Separator();
					ImGui::Text("Oops entity has no components...");
					ImGui::Text("Try adding some at the top...");
				}
			}
			else
			{
				ImGui::Separator();
				ImGui::Text("Oops entity is new...");
				ImGui::Text("Try adding some at the top...");
			}
		}
		else
		{
			ImGui::Text("Components of [] [ID: ]\n");
			ImGui::Separator();
			ImGui::Text("Oops no entity selected...");
		}
		ImGui::End();
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
		//ImGui::PushStyleColor(ImGuiCol_Separator, { 1.0f,1.0f,1.0f,1.0f });
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNodeEx("Engine Components and Systems", ImGuiTreeNodeFlags_Framed))
		{
			if (entity)
			{
				ImGui::Text("Components:");
				ImGui::BeginListBox("[Com]", { 0.0f, 100.0f });

				// renders all registered components in a listbox
				for (auto& c : ECS::ECSInstance::Instance().component_manager_.registered_components_)
				{
					bool has_component_ = false;
					
					// if the selected entity has the component, color it green
					if (entity->HasComponent(c.bit_))
					{
						has_component_ = true;
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f,1.0f,0.0f,1.0f });
					}

					// if component is selected
					if (ImGui::Selectable(c.name_.c_str(), true))
					{

						// if selected entity does not have component, add it in
						if (!has_component_)
						{
							entity->AddComponent(c.bit_);
							std::stringstream ss;
							ss << "Added component [" << c.name_ << "] to entity" << " [" << entity->name_ << "].";
							Console::Log(ss.str().c_str());
							ECS::ECSInstance::Instance().Print();
						}
						// else remove it
						else
						{
							entity->RemoveComponent(c.bit_);
							std::stringstream ss;
							ss << "Removed component [" << c.name_ << "] from entity" << " [" << entity->name_ << "].";
							Console::Log(ss.str().c_str());
							ECS::ECSInstance::Instance().Print();
						}
					}
					if (has_component_)
					{
						has_component_ = false;
						ImGui::PopStyleColor(1);
					}
				}
				ImGui::EndListBox();

				ImGui::Separator();
				ImGui::Text("Systems:");
				ImGui::BeginListBox("[Sys]", { 0.0f, 100.0f });

				// render all registered systems in a listbox
				for (auto& s : ECS::ECSInstance::Instance().system_manager_.registered_systems_)
				{
					bool has_system_ = true;
					
					// check if the selected entity has the components of the system already added, if so mark green
					for (auto& c : ECS::ECSInstance::Instance().system_manager_.system_database_[s.id_]->components_)
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
					if (has_system_)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f,1.0f,0.0f,1.0f });
					}
					
					// if system selected
					if (ImGui::Selectable(s.name_.c_str(), true))
					{
						// add the system components to the selected entity is any are missing
						if (!has_system_)
						{
							entity->AddSystem(s.id_);
							std::stringstream ss;
							ss << "Added system [" << s.name_ << "]'s components to entity" << " [" << entity->name_ << "].";
							Console::Log(ss.str().c_str());
							ECS::ECSInstance::Instance().Print();
						}
					}
					if (has_system_)
					{
						has_system_ = false;
						ImGui::PopStyleColor(1);
					}
				}
				ImGui::EndListBox();
			}
			// if no selected entity case, print default messages
			else
			{
				ImGui::Separator();
				ImGui::Text("Components:");
				ImGui::BeginListBox("[Com]", { 0.0f, 100.0f });
				for (auto& c : ECS::ECSInstance::Instance().component_manager_.registered_components_)
				{
					if (ImGui::Selectable(c.name_.c_str(), true))
					{
						Console::Log("Oops please select an entity before adding...");
					}
				}
				ImGui::EndListBox();

				ImGui::Separator();
				ImGui::Text("Systems:");
				ImGui::BeginListBox("[Sys]", { 0.0f, 100.0f });
				for (auto& s : ECS::ECSInstance::Instance().system_manager_.registered_systems_)
				{
					if (ImGui::Selectable(s.name_.c_str(), true))
					{
						Console::Log("Oops please select an entity before adding...");
					}
				}
				ImGui::EndListBox();
			}
			ImGui::TreePop();
		}
		//ImGui::PopStyleColor();
	}
}