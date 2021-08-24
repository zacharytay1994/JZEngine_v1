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

	}

	void SceneTree::Render()
	{
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * x_, static_cast<float>(Settings::window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * sx_, static_cast<float>(Settings::window_height) * sy_ }, ImGuiCond_Once);
		ImGui::Begin("Scene Heirarchy");
		if (ImGui::Button("Add Default Object"))
		{
			ECS::ECSInstance::Instance().CreateEntity();
		}
		ImGui::Text("\nCurrent Scene");
		ImGui::Text("______________________________");
		for (auto& entity : ECS::ECSInstance::Instance().entity_manager_.roots_)
		{
			if (entity)
			{
				RenderAllChildObjects(entity);
			}
		}
		ImGui::End();
	}

	void SceneTree::RenderAllChildObjects(ECS::Entity* entity)
	{
		std::stringstream ss;
		ss << "Object " << entity->entity_id_;

		// add own tree node
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		bool open = ImGui::TreeNode(ss.str().c_str());
		if (ImGui::BeginPopupContextItem(ss.str().c_str()))
		{
			if (ImGui::Selectable("Add Object"))
			{
				ECS::ECSInstance::Instance().CreateEntity(entity->entity_id_);
			}
			if (ImGui::Selectable("Remove Object"))
			{
				ECS::ECSInstance::Instance().RemoveEntity(entity->entity_id_);
			}
			ImGui::EndPopup();
		}

		// end own tree node
		if (open)
		{
			// add all child tree nodes
			for (auto& c : entity->children_)
			{
				if (c)
				{
					RenderAllChildObjects(c);
				}
			}
			ImGui::TreePop();
		}
	}
}