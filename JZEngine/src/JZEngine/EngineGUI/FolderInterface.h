/*	__FILE HEADER__
*	File:		FolderInterface.h
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders assets that are loaded into the engine.
*/

#pragma once
#include "ImGuiInterface.h"

namespace JZEngine
{
	namespace ECS
	{
		struct ECSInstance;
	}
	struct SceneTree;
	struct SoundSystem;
	struct FolderInterface : public ImGuiInterface
	{
		enum class DISPLAY
		{
			SCENES,
			PREFAB,
			RESOURCES_TEXTURES,
			RESOURCES_AUDIO
		};

		ECS::ECSInstance* ecs_instance_{ nullptr };
		SceneTree* scene_tree_{ nullptr };
		SoundSystem* sound_system_{ nullptr };
		static constexpr unsigned int display_columns_{ 4 };
		bool select_enabled_{ false };
		std::string selected_texture_{ "" };

		FolderInterface(float x, float y, float sx, float sy, int group);
		virtual void Render(float dt) override;
		virtual void CloseAction() override;

		void RenderPrefabs();
		void RenderScenes();
		void RenderTextures();
		void RenderAudio();

		void RecursivelyRenderFolders(ResourceManager::FolderData const& folder);
		void RecursivelyRenderAudioFolders(SoundSystem::FolderData const& folder);
		void GetAllDirectories(std::string const& path);

		DISPLAY mode{ DISPLAY::RESOURCES_TEXTURES };
		void ResetAllPreviews();

		void ReloadScene ();
		void ReloadScene2 ();
	private:

		/*!
		 * TEXTURE VARIABLES
		*/
		std::string selected_texture_path{ "Assets/Textures" };
		std::string selected_texture_directory{ "Textures" };
		bool texture_preview_{ false };
		std::string selected_preview_texture{ "" };

		void DisplayTexturePreview();
		
		/*!
		 * SOUND VARIABLES
		*/
		std::string selected_audio_path{ "Assets/Sounds" };
		std::string selected_audio_directory{ "Sounds" };
		std::string selected_audio{ "" };
		bool audio_preview_{ false };
		std::string selected_preview_audio{ "" };
		int audio_clip_preview_id_{ -1 };

		void DisplayAudioPreview();
	};
}