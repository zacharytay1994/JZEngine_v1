#include <PCH.h>

#include "FolderInterface.h"
#include "../Resource/Serialize.h"
#include "../DebugTools/Log.h"
#include "../Resource/ResourceManager.h"
#include "../EngineConfig.h"
#include "../ECS/ECS.h"
#include "SceneTree.h"

namespace JZEngine
{
	FolderInterface::FolderInterface(float x, float y, float sx, float sy, int group)
		:
		ImGuiInterface(x, y, sx, sy, group)
	{

	}

	void FolderInterface::Render(float dt)
	{
		ImGui::Begin("Directory", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Scenes"))
			{ 
				ImGui::Text("Scenes");
				ImGui::Separator();
				if (ImGui::MenuItem("All"))
				{
					mode = DISPLAY::SCENES;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Prefabs"))
			{
				ImGui::Text("Prefabs");
				ImGui::Separator();
				if (ImGui::MenuItem("All"))
				{
					mode = DISPLAY::PREFAB;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// render display
		switch (mode)
		{
		case (DISPLAY::SCENES):
			RenderScenes();
			break;
		case(DISPLAY::PREFAB):
			RenderPrefabs();
			break;
		}

		ImGui::End();
	}

	void FolderInterface::RenderPrefabs()
	{
		if (ImGui::BeginTable("prefab_table", display_columns_))
		{
			for (auto& e : Serialize::entities_)
			{
				ImGui::TableNextColumn();
				ImGui::Image((void*)ResourceManager::texture2ds_[0].texture2d_.GetRendererID(), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f });
				if (ImGui::BeginPopupContextItem(e.first.c_str()))
				{
					if (ImGui::Selectable("Add To Scene"))
					{
						int id = ecs_instance_->CreateEntity();
						ECS::Entity& entity = ecs_instance_->entity_manager_.GetEntity(id);
						Serialize::LoadEntity(entity, e.first);
						std::stringstream ss;
						ss << e.first << "(copy)";
						entity.name_ = ss.str();
					}
					ImGui::EndPopup();
				}
				ImGui::Text(e.first.c_str());
			}
			ImGui::EndTable();
		}
	}

	void FolderInterface::RenderScenes()
	{
		if (ImGui::BeginTable("scene_table", display_columns_))
		{
			for (auto& s : Serialize::scenes_)
			{
				ImGui::TableNextColumn();
				ImGui::Image((void*)ResourceManager::texture2ds_[0].texture2d_.GetRendererID(), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f });
				if (ImGui::BeginPopupContextItem(s.first.c_str()))
				{
					if (ImGui::Selectable("Add To Scene"))
					{
						scene_tree_->RemoveAllEntities();
						Serialize::DeserializeScene(ecs_instance_, s.first);
					}
					ImGui::EndPopup();
				}
				ImGui::Text(s.first.c_str());
			}
			ImGui::EndTable();
		}
	}
}