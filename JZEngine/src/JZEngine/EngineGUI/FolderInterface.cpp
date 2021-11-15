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
	{
	}

	void FolderInterface::RecursivelyRenderFolders(ResourceManager::FolderData const& folder)
	{
		//ImGui::SetNextItemOpen(true);
		ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconfolder")->GetRendererID()), { 11.0f, 11.0f }, { 0,1 }, { 1,0 });
		ImGui::SameLine();
		bool open = ImGui::TreeNodeEx(folder.name_.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick);
		if (ImGui::IsItemClicked())
		{
			selected_texture_path = folder.path_;
			selected_texture_directory = folder.name_;
		}
		if (open)
		{
			for (auto const& child_folder : folder.folders_)
			{
				RecursivelyRenderFolders(child_folder);
			}
			ImGui::TreePop();
		}
	}

	void FolderInterface::Render(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		SetNextWindowDimensions(0.0f, 0.0f, 0.2f, 1.0f);
		ImGui::Begin("Folders", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		if (ImGui::BeginMenuBar())
		{
			float button_size = Settings::window_width * sx_ * 0.01f;
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconx")->GetRendererID()), { button_size, button_size }))
			{
				ToggleOnOff();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Separator();
		ImGui::Text("Directories");
		ImGui::Separator();
		switch (mode)
		{
		case (DISPLAY::SCENES):
			break;
		case(DISPLAY::PREFAB):
			break;
		case(DISPLAY::RESOURCES_TEXTURES):
			RecursivelyRenderFolders(ResourceManager::texture_folder_data_);
			break;
		}
		ImGui::End();

		SetNextWindowDimensions(0.2f, 0.0f, 0.8f, 1.0f);
		ImGui::Begin("Directory", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button("Textures"))
			{
				mode = DISPLAY::RESOURCES_TEXTURES;
			}
			if (ImGui::Button("Scenes"))
			{
				mode = DISPLAY::SCENES;
			}
			if (ImGui::Button("Prefabs"))
			{
				mode = DISPLAY::PREFAB;
			}
			ImGui::EndMenuBar();
		}
		ImGui::Separator();
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
			std::stringstream ss;
			ss << "Folder: " << selected_texture_path;
			ImGui::Text(ss.str().c_str());
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
		if (selected_texture_directory != "Nothing Selected")
		{
			// get all files in the folder
			if (ImGui::BeginTable("textures_table", display_columns_))
			{
				if (selected_texture_directory == "Textures")
				{
					for (auto& texture : ResourceManager::umap_texture2ds_)
					{
						if (filter.PassFilter(texture.first.c_str()))
						{
							ImGui::TableNextColumn();
							ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(texture.second)->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, { 1, 1, 1, 1 }, { 0.5, 0.5, 0.5, 1 });
							ImGui::Text(texture.first.c_str());
						}
					}
				}
				else
				{
					for (auto const& texture : ResourceManager::texture_folders_[selected_texture_directory])
					{
						if (filter.PassFilter(texture.c_str()))
						{
							ImGui::TableNextColumn();
							ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(ResourceManager::umap_texture2ds_[texture])->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, { 1, 1, 1, 1 }, { 0.5, 0.5, 0.5, 1 });
							ImGui::Text(texture.c_str());
						}
					}
				}
				ImGui::EndTable();
			}
		}
		/*if (ImGui::BeginTable("textures_table", display_columns_))
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
		}*/
	}

	void FolderInterface::GetAllDirectories(const std::string& path)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			std::cout << entry.path() << std::endl;
			if (std::filesystem::is_directory(entry.path()))
			{
				GetAllDirectories(entry.path().u8string());
			}
			else
			{
				std::cout << entry.path().filename() << std::endl;
			}
		}
	}
}