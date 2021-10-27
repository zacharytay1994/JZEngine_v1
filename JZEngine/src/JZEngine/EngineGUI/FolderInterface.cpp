/*	__FILE HEADER__
*	File:		FolderInterface.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders assets that are loaded into the engine.
*/

#include <PCH.h>

#include "FolderInterface.h"
#include "../Resource/Serialize.h"
#include "../DebugTools/Log.h"
#include "../Resource/ResourceManager.h"
#include "../EngineConfig.h"
#include "../ECS/ECS.h"
#include "SceneTree.h"
#include "../SceneLogic/SceneLogic.h"

namespace JZEngine
{
	FolderInterface::FolderInterface(float x, float y, float sx, float sy, int group)
		:
		ImGuiInterface(x, y, sx, sy, group)
	{}

	void FolderInterface::Render(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		ImGui::Begin("Directory", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Scenes"))
			{ 
				if (ImGui::MenuItem("All"))
				{
					mode = DISPLAY::SCENES;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Prefabs"))
			{
				if (ImGui::MenuItem("All"))
				{
					mode = DISPLAY::PREFAB;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Resources"))
			{
				if (ImGui::MenuItem("Textures"))
				{
					mode = DISPLAY::RESOURCES_TEXTURES;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// render display
		switch (mode)
		{
		case (DISPLAY::SCENES):
			ImGui::Text("Scenes");
			ImGui::Separator();
			RenderScenes();
			break;
		case(DISPLAY::PREFAB):
			ImGui::Text("Prefabs");
			ImGui::Separator();
			RenderPrefabs();
			break;
		case(DISPLAY::RESOURCES_TEXTURES):
			ImGui::Text("Resources");
			ImGui::Separator();
			RenderTextures();
			break;
		}

		ImGui::End();
	}

	void FolderInterface::RenderPrefabs()
	{
		ImGui::Separator();
		ImGui::Text("Prefabs |");
		ImGui::SameLine();
		static ImGuiTextFilter filter;
		filter.Draw(": Filter");
		ImGui::Separator();
		if (ImGui::BeginTable("prefab_table", display_columns_))
		{
			for (auto& e : Serialize::entities_)
			{
				if (filter.PassFilter(e.first.c_str()))
				{
					ImGui::TableNextColumn();
					ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("textfileicon")->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, {0,1}, {1,0});
					if (ImGui::BeginPopupContextItem(e.first.c_str()))
					{
						if (ImGui::Selectable("Add To Scene"))
						{
							Serialize::LoadEntity(ecs_instance_, e.first);
						}
						ImGui::EndPopup();
					}
					ImGui::Text(e.first.c_str());
				}
			}
			ImGui::EndTable();
		}
	}

	void FolderInterface::RenderScenes()
	{
		ImGui::Separator();
		ImGui::Text("Scenes |");
		ImGui::SameLine();
		static ImGuiTextFilter filter;
		filter.Draw(": Filter");
		ImGui::Separator();
		if (ImGui::BeginTable("scene_table", display_columns_))
		{
			for (auto& s : Serialize::scenes_)
			{
				if (filter.PassFilter(s.first.c_str()))
				{
					ImGui::TableNextColumn();
					ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("textfileicon")->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 });
					if (ImGui::BeginPopupContextItem(s.first.c_str()))
					{
						if (ImGui::Selectable("Load Scene"))
						{
							scene_tree_->RemoveAllEntities();
							Serialize::DeserializeScene(ecs_instance_, s.first);
							*scene_tree_->current_scene_name_ = s.first;
							SceneLogic::Instance().SetCurrentSceneName(s.first);
							SceneLogic::Instance().BuildEntityMap();
							SceneLogic::Instance().InitSceneLogic();
						}
						if (ImGui::Selectable("Append To Scene"))
						{
							Serialize::DeserializeScene(ecs_instance_, s.first);
						}
						ImGui::EndPopup();
					}
					ImGui::Text(s.first.c_str());
				}
			}
			ImGui::EndTable();
		}
	}

	void FolderInterface::RenderTextures()
	{
		ImGui::Separator();
		ImGui::Text("Textures |");
		ImGui::SameLine();
		static ImGuiTextFilter filter;
		filter.Draw(": Filter");
		ImGui::SameLine();
		if (ImGui::Button("Refresh"))
		{
			ResourceManager::LoadAllTexturesInFolder();
		}
		ImGui::Separator();
		if (ImGui::BeginTable("textures_table", display_columns_))
		{
			for (auto& texture : ResourceManager::umap_texture2ds_)
			{
				if (filter.PassFilter(texture.first.c_str()))
				{
					ImGui::TableNextColumn();
					ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(texture.second)->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, {1, 1, 1, 1}, {0.5, 0.5, 0.5, 1});
					ImGui::Text(texture.first.c_str());
				}
			}
			ImGui::EndTable();
		}
	}
}