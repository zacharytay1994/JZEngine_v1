#include "PCH.h"
#include "SceneTree.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"

namespace JZEngine
{
	SceneTree::SceneTree(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{
		new_entity_name_[0] = '\0';
	}

	void SceneTree::Render()
	{
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, static_cast<float>(Settings::window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height) * sy_ }, ImGuiCond_Once);
		ImGui::Begin("Scene Heirarchy");

		// render text box for input name
		ImGui::InputText("Name", new_entity_name_, MAX_NAME_SIZE);

		if (ImGui::Button("Add Default Entity"))
		{
			unsigned int id = ECS::ECSInstance::Instance().CreateEntity();
			if (id != -1)
			{
				ECS::Entity& created_entity = ECS::ECSInstance::Instance().GetEntity(id);
				created_entity.name_ = GetName();
			}
		}
		ImGui::Text("\nCurrent Scene");
		ImGui::Text("______________________________");
		for (auto& id : ECS::ECSInstance::Instance().entity_manager_.root_ids_)
		{
			if (id != -1)
			{
				RenderAllChildObjects(&ECS::ECSInstance::Instance().entity_manager_.GetEntity(id));
			}
		}
		ImGui::End();
	}

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
		if (ImGui::IsItemClicked())
		{
			selected_entity_ = entity;
		}
		if (ImGui::BeginPopupContextItem(ss.str().c_str()))
		{
			if (ImGui::Selectable("Add Entity"))
			{
				int id = ECS::ECSInstance::Instance().CreateEntity(entity->entity_id_);
				if (id == -1)
				{
					std::stringstream ss;
					ss << "Entity " << entity->name_ << " (ID: " << entity->entity_id_ << ") has maximum number of children!";
					Console::Log(ss.str().c_str());
				}
				else
				{
					ECS::Entity& created_entity = ECS::ECSInstance::Instance().GetEntity(id);
					created_entity.name_ = GetName();
				}
			}
			if (ImGui::Selectable("Remove Entity"))
			{
				ECS::ECSInstance::Instance().RemoveEntity(entity->entity_id_);
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
					RenderAllChildObjects(&ECS::ECSInstance::Instance().entity_manager_.GetEntity(c));
				}
			}
			ImGui::TreePop();
		}
	}

	std::string SceneTree::GetName()
	{
		if (new_entity_name_[0] == '\0')
		{
			std::stringstream ss;
			ss << default_entity_name_;
			if (names_.find(default_entity_name_) == names_.end())
			{
				names_[default_entity_name_] = 1;
				return default_entity_name_;
			}
			else
			{
				ss << "(" << names_[default_entity_name_]++ << ")";
				return ss.str();
			}
		}
		else
		{
			std::stringstream ss;
			ss << new_entity_name_;
			if (names_.find(new_entity_name_) == names_.end())
			{
				names_[new_entity_name_] = 1;
				return ss.str();
			}
			else
			{
				ss << "(" << names_[new_entity_name_]++ << ")";
				return ss.str();
			}
		}
	}
}