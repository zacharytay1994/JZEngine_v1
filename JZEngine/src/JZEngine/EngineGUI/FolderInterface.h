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
	struct FolderInterface : public ImGuiInterface
	{
		enum class DISPLAY
		{
			SCENES,
			PREFAB,
			RESOURCES_TEXTURES
		};

		ECS::ECSInstance* ecs_instance_{ nullptr };
		SceneTree* scene_tree_{ nullptr };
		static constexpr unsigned int display_columns_{ 4 };

		FolderInterface(float x, float y, float sx, float sy, int group);
		virtual void Render(float dt) override;

		void RenderPrefabs();
		void RenderScenes();
		void RenderTextures();

		void RecursivelyRenderFolders(ResourceManager::FolderData const& folder);
		void GetAllDirectories(std::string const& path);

	private:
		DISPLAY mode{ DISPLAY::RESOURCES_TEXTURES };

		/*!
		 * TEXTURE VARIABLES
		*/
		std::string selected_texture_path{ "Assets/Textures" };
		std::string selected_texture_directory{ "Textures" };
		bool texture_preview_{ false };
		std::string selected_preview_texture{ "" };

		void DisplayTexturePreview();
	};
}