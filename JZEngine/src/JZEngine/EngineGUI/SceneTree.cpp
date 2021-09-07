/*	__FILE HEADER__
*	File:	SceneTree.cpp
	Author: JZ
	Date:	26/08/21
	Brief:	Renders all entities in the scene tree on the
			GUI using ImGui.
*/

#include "PCH.h"
#include "SceneTree.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"

namespace JZEngine
{
	SceneTree::SceneTree(float x, float y, float sx, float sy, ECS::ECSInstance* ecs)
		:
		ecs_instance_(ecs),
		x_(x), y_(y), sx_(sx), sy_(sy)
	{
		default_entity_name_ = new std::string("Entity");
		//*default_entity_name_ = "Entity";
		names_ = new std::unordered_map<std::string, unsigned int>();
		new_entity_name_[0] = '\0';
	}

	SceneTree::~SceneTree()
	{
		delete default_entity_name_;
		delete names_;
	}

	/*!
	 * @brief ___JZEngine::SceneTree::Render()___
	 * ****************************************************************************************************
	 * Renders the ImGui window.
	 * ****************************************************************************************************
	*/
	void SceneTree::Render()
	{
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, static_cast<float>(Settings::window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height) * sy_ }, ImGuiCond_Once);
		ImGui::Begin("Scene Heirarchy");

		// render text box for input name
		ImGui::InputText(": Name", new_entity_name_, MAX_NAME_SIZE);

		if (ImGui::Button("Add Default Entity"))
		{
			// create a new entity, pushed into EntityManager
			unsigned int id = ecs_instance_->CreateEntity();

			// if successful
			if (id != -1)
			{
				// rename it
				ecs_instance_->GetEntity(id).name_ = GetName();
			}
		}
		ImGui::Text("\nCurrent Scene");
		ImGui::PushStyleColor(ImGuiCol_Separator, { 0.8f,0.8f,0.8f,1.0f });
		ImGui::Separator();
		ImGui::PopStyleColor();

		// render all root entities in EntityManager
		for (auto& id : ecs_instance_->entity_manager_.root_ids_)
		{
			if (id != -1)
			{
				// recursively render all children of a root entity
				RenderAllChildObjects(&ecs_instance_->entity_manager_.GetEntity(id));
			}
		}
		ImGui::End();
	}

	/*!
	 * @brief ___JZEngine::SceneTree::RenderAllChildObjects()___
	 * ****************************************************************************************************
	 * Recursive function that renders the entity in the tree,
	 * and also all of its children under it.
	 * ****************************************************************************************************
	 * @param entity
	 * : The entity to render. Should be a root entity in EntityManager.
	 * ****************************************************************************************************
	*/
	void SceneTree::RenderAllChildObjects(ECS::Entity* entity)
	{
		std::stringstream ss;
		ss << entity->name_;

		// add own tree node
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		bool is_selected = false;
		if (selected_entity_)
		{
			if (entity->entity_id_ == selected_entity_->entity_id_)
			{
				is_selected = true;
				ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f,1.0f,0.0f,1.0f });
			}
		}

		bool open = ImGui::TreeNodeEx(ss.str().c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);

		// if a treenode is clicked, make that entity the selected_entity_
		if (ImGui::IsItemClicked())
		{
			selected_entity_ = entity;
		}
		if (ImGui::BeginPopupContextItem(ss.str().c_str()))
		{
			// adds an entity as a child of this entity on right click
			if (ImGui::Selectable("Add Entity"))
			{
				int id = ecs_instance_->CreateEntity(entity->entity_id_);
				if (id == -1)
				{
					std::stringstream ss;
					ss << "Entity " << entity->name_ << " (ID: " << entity->entity_id_ << ") has maximum number of children!";
					Console::Log(ss.str().c_str());
				}
				else
				{
					ECS::Entity& created_entity = ecs_instance_->GetEntity(id);
					created_entity.name_ = GetName();
				}
			}
			// removes an entity from the tree
			if (ImGui::Selectable("Remove Entity"))
			{
				ecs_instance_->RemoveEntity(entity->entity_id_);
				selected_entity_ = nullptr;
			}
			ImGui::EndPopup();
		}
		if (is_selected)
		{
			ImGui::PopStyleColor();
		}

		// end own tree node
		if (open)
		{
			// add all child tree nodes
			for (auto& c : entity->children_)
			{
				if (c != -1)
				{
					RenderAllChildObjects(&ecs_instance_->entity_manager_.GetEntity(c));
				}
			}
			ImGui::TreePop();
		}
	}

	/*!
	 * @brief ___JZEngine::SceneTree::GetName()___
	 * ****************************************************************************************************
	 * Gets a unique name in the scene. If a name
	 * is repeated, pad it with an index.
	 * ****************************************************************************************************
	 * @return std::string
	 * : The name padded with the index.
	 * ****************************************************************************************************
	*/
	std::string SceneTree::GetName()
	{
		// if a custom name is typed
		if (new_entity_name_[0] == '\0')
		{
			std::stringstream ss;
			ss << *default_entity_name_;
			
			// pad identical names with an index
			if (names_->find(*default_entity_name_) == names_->end())
			{
				(*names_)[*default_entity_name_] = 1;
				return *default_entity_name_;
			}
			else
			{
				ss << "(" << (*names_)[*default_entity_name_]++ << ")";
				return ss.str();
			}
		}
		// else use the default name padded with index
		else
		{
			std::stringstream ss;
			ss << new_entity_name_;
			if (names_->find(new_entity_name_) == names_->end())
			{
				(*names_)[new_entity_name_] = 1;
				return ss.str();
			}
			else
			{
				ss << "(" << (*names_)[new_entity_name_]++ << ")";
				return ss.str();
			}
		}
	}
}