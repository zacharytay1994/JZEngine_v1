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
#include "../Sound/Sound.h"

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
			if (texture_preview_)
			{
				texture_preview_ = false;
			}
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

	void FolderInterface::RecursivelyRenderAudioFolders(SoundSystem::FolderData const& folder)
	{
		//ImGui::SetNextItemOpen(true);
		ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconfolder")->GetRendererID()), { 11.0f, 11.0f }, { 0,1 }, { 1,0 });
		ImGui::SameLine();
		bool open = ImGui::TreeNodeEx(folder.name_.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick);
		if (ImGui::IsItemClicked())
		{
			selected_audio_path = folder.path_;
			selected_audio_directory = folder.name_;
			if (audio_preview_ && sound_system_)
			{
				audio_preview_ = false;
				sound_system_->stopSound(audio_clip_preview_id_);
			}
		}
		if (open)
		{
			for (auto const& child_folder : folder.folders_)
			{
				RecursivelyRenderAudioFolders(child_folder);
			}
			ImGui::TreePop();
		}
	}

	void FolderInterface::Render(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		SetNextWindowDimensions(0.0f, 0.0f, 0.2f, 1.0f);
		ImGui::Begin("Folders", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		CloseButtonMenuBar();

		ImGui::Text("Directories");
		ImGui::Separator();
		switch (mode)
		{
		case (DISPLAY::SCENES):
			ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconfolder")->GetRendererID()), { 11.0f, 11.0f }, { 0,1 }, { 1,0 });
			ImGui::SameLine();
			if (ImGui::TreeNodeEx("Scenes", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick))
			{
				ImGui::TreePop();
			}
			break;
		case(DISPLAY::PREFAB):
			ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconfolder")->GetRendererID()), { 11.0f, 11.0f }, { 0,1 }, { 1,0 });
			ImGui::SameLine();
			if (ImGui::TreeNodeEx("Prefabs", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick))
			{
				ImGui::TreePop();
			}
			break;
		case(DISPLAY::RESOURCES_TEXTURES):
			RecursivelyRenderFolders(ResourceManager::texture_folder_data_);
			break;
		case(DISPLAY::RESOURCES_AUDIO):
			if (sound_system_)
			{
				RecursivelyRenderAudioFolders(sound_system_->sound_folder_data_);
			}
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
				ResetAllPreviews();
			}
			if (ImGui::Button("Audio"))
			{
				mode = DISPLAY::RESOURCES_AUDIO;
				ResetAllPreviews();
			}
			if (ImGui::Button("Scenes"))
			{
				mode = DISPLAY::SCENES;
				ResetAllPreviews();
			}
			if (ImGui::Button("Prefabs"))
			{
				mode = DISPLAY::PREFAB;
				ResetAllPreviews();
			}
			ImGui::EndMenuBar();
		}
		// render display
		std::stringstream ss;
		switch (mode)
		{
		case (DISPLAY::SCENES):
			ImGui::Text("Folder: Saves/Scenes");
			ImGui::Separator();
			RenderScenes();
			break;
		case(DISPLAY::PREFAB):
			ImGui::Text("Folder: Saves/Prefabs");
			ImGui::Separator();
			RenderPrefabs();
			break;
		case(DISPLAY::RESOURCES_TEXTURES):
			ss << "Folder: " << selected_texture_path;
			ImGui::Text(ss.str().c_str());
			ImGui::Separator();
			if (texture_preview_)
			{
				DisplayTexturePreview();
			}
			else
			{
				RenderTextures();
			}
			break;
		case(DISPLAY::RESOURCES_AUDIO):
			ss << "Folder: " << selected_audio_path;
			ImGui::Text(ss.str().c_str());
			ImGui::Separator();
			if (audio_preview_)
			{
				DisplayAudioPreview();
			}
			else
			{
				RenderAudio();
			}
			break;
		}

		ImGui::End();
	}

	void FolderInterface::CloseAction()
	{
		ResetAllPreviews();
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
					if (ImGui::BeginPopupContextItem(e.first.c_str(), ImGuiPopupFlags_MouseButtonLeft))
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
					if (ImGui::BeginPopupContextItem(s.first.c_str(), ImGuiPopupFlags_MouseButtonLeft))
					{
						if (ImGui::Selectable("Load Scene"))
						{
							scene_tree_->RemoveAllEntities();
							Serialize::DeserializeScene(ecs_instance_, s.first);
							*scene_tree_->current_scene_name_ = s.first;
							SceneLogic::Instance().SetCurrentSceneName(s.first);
							SceneLogic::Instance().BuildEntityMap();
							SceneLogic::Instance().InitSceneLogic();
							ToggleOnOff();
						}
						if (ImGui::Selectable("Append To Scene"))
						{
							Serialize::DeserializeScene(ecs_instance_, s.first);
							ToggleOnOff();
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
			//ResourceManager::LoadAllTexturesInFolder();
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
							if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(texture.second)->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, -1, { 1, 0, 1, 0.5 }, { 1, 1, 1, 1 }))
							{
							}
							if (ImGui::BeginPopupContextItem(texture.first.c_str(), ImGuiPopupFlags_MouseButtonLeft))
							{
								if (ImGui::Selectable("Preview"))
								{
									texture_preview_ = true;
									selected_preview_texture = texture.first.c_str();
								}
								if (ImGui::Selectable("Select"))
								{
								}
								ImGui::EndPopup();
							}
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
							if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(texture)->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, -1, { 1, 0, 1, 0.5 }, { 1, 1, 1, 1 }))
							{
							}
							if (ImGui::BeginPopupContextItem(texture .c_str(), ImGuiPopupFlags_MouseButtonLeft))
							{
								if (ImGui::Selectable("Preview"))
								{
									texture_preview_ = true;
									selected_preview_texture = texture.c_str();
								}
								if (ImGui::Selectable("Select"))
								{
								}
								ImGui::EndPopup();
							}
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

	void FolderInterface::RenderAudio()
	{
		ImGui::Separator();
		ImGui::Text("Audio |");
		ImGui::SameLine();
		static ImGuiTextFilter filter;
		filter.Draw(": Filter");
		ImGui::SameLine();
		if (ImGui::Button("Refresh"))
		{
			//ResourceManager::LoadAllTexturesInFolder();
		}
		ImGui::Separator();
		if (!sound_system_)
		{
			return;
		}
		if (selected_audio_directory != "Nothing Selected")
		{
			// get all files in the folder
			if (ImGui::BeginTable("audio_table", display_columns_))
			{
				if (selected_audio_directory == "Sounds")
				{
					for (auto& sound : sound_system_->sound_cont)
					{
						if (filter.PassFilter(sound.first.c_str()))
						{
							ImGui::TableNextColumn();
							if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconaudio")->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, -1, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }))
							{
							}
							if (ImGui::BeginPopupContextItem(sound.first.c_str(), ImGuiPopupFlags_MouseButtonLeft))
							{
								if (ImGui::Selectable("Preview"))
								{
									audio_preview_ = true;
									selected_preview_audio = sound.first.c_str();
									selected_audio = sound.first;
									audio_clip_preview_id_ = sound_system_->playSound(sound.first);
								}
								if (ImGui::Selectable("Select"))
								{
								}
								ImGui::EndPopup();
							}
							ImGui::Text(sound.first.c_str());
						}
					}
				}
				else
				{
					for (auto const& sound : sound_system_->sound_folders_[selected_audio_directory])
					{
						if (filter.PassFilter(sound.c_str()))
						{
							ImGui::TableNextColumn();
							if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconaudio")->GetRendererID()), { static_cast<float>(Settings::window_width) / 20.0f,static_cast<float>(Settings::window_width) / 20.0f }, { 0,1 }, { 1,0 }, -1, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }))
							{
							}
							if (ImGui::BeginPopupContextItem(sound.c_str(), ImGuiPopupFlags_MouseButtonLeft))
							{
								if (ImGui::Selectable("Preview"))
								{
									audio_preview_ = true;
									selected_preview_audio = sound.c_str();
									selected_audio = sound;
									audio_clip_preview_id_ = sound_system_->playSound(sound);
								}
								if (ImGui::Selectable("Select"))
								{
								}
								ImGui::EndPopup();
							}
							ImGui::Text(sound.c_str());
						}
					}
				}
				ImGui::EndTable();
			}
		}
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

	void FolderInterface::ResetAllPreviews()
	{
		if (texture_preview_)
		{
			texture_preview_ = false;
		}

		if (audio_preview_ && sound_system_)
		{
			audio_preview_ = false;
			sound_system_->stopSound(audio_clip_preview_id_);
		}
	}

	void FolderInterface::DisplayTexturePreview()
	{
		float button_size = Settings::window_width * sx_ * 0.01f;
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconback")->GetRendererID()), { button_size, button_size }))
		{
			texture_preview_ = false;
		}
		ImGui::Separator();
		JZEngine::Texture2D* tex2d = ResourceManager::GetTexture(selected_preview_texture);
		std::stringstream ss;
		ss << "Name: " << selected_preview_texture << " [" << tex2d->GetWidth() << "x" << tex2d->GetHeight() << "]";
		ImGui::Text(ss.str().c_str());
		unsigned long long id = static_cast<unsigned long long>(tex2d->GetRendererID());
		float width = static_cast<float>(Settings::window_width) * sx_ * 0.7f;
		float height = width * tex2d->GetHeight() / tex2d->GetWidth();
		ImGui::Image((void*)id, { width , height }, { 0,1 }, { 1,0 }, { 1, 1, 1, 1 }, { 0.5, 0.5, 0.5, 1 });
	}

	void FolderInterface::DisplayAudioPreview()
	{
		float button_size = Settings::window_width * sx_ * 0.01f;
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconback")->GetRendererID()), { button_size, button_size }))
		{
			audio_preview_ = false;
			sound_system_->stopSound(audio_clip_preview_id_);
		}
		ImGui::Separator();
		std::stringstream ss;
		ss << "Name: " << selected_preview_audio;
		ImGui::Text(ss.str().c_str());
		if (ImGui::BeginTable("audio_preview_table", 1))
		{
			ImGui::TableNextColumn();
			JZEngine::Texture2D* tex2d = ResourceManager::GetTexture("iconaudio");
			unsigned long long id = static_cast<unsigned long long>(tex2d->GetRendererID());
			float width = static_cast<float>(Settings::window_width) * sx_ * 0.1f;
			ImGui::SetCursorPosX(static_cast<float>(Settings::window_width) * sx_ * 0.4f - width/2.0f);
			ImGui::Image((void*)id, { width , width }, { 0,1 }, { 1,0 }, { 1, 1, 1, 1 });

			ImGui::SetCursorPosX(static_cast<float>(Settings::window_width) * sx_ * 0.4f - button_size);
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("iconstart")->GetRendererID()), { button_size * 2.0f , button_size * 2.0f }, { 0,1 }, { 1,0 }, -1, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }))
			{
				if (sound_system_)
				{
					sound_system_->stopSound(audio_clip_preview_id_);
					audio_clip_preview_id_ = sound_system_->playSound(selected_audio);
				}
			}
			ImGui::EndTable();
		}
	}
}