/*	__FILE HEADER__
*	File:		SceneTree.h
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders all entities in the scene tree on the 
				GUI using ImGui.
*/

#pragma once

#include <unordered_map>

#include "../BuildDefinitions.h"
#include "../ImGui/imgui.h"

namespace JZEngine
{
	namespace ECS
	{
		struct Entity;
		struct ECSInstance;
	}

	/*!
	 * @brief ___JZEngine::SceneTree___
	 * ****************************************************************************************************
	 * Renders all entities in the scene tree GUI.
	 * Able to add and remove entities from the scene.
	 * ****************************************************************************************************
	*/
	struct SceneTree
	{
		ECS::ECSInstance* ecs_instance_{nullptr};
		float x_, y_, sx_, sy_;		/*!< position and scale of ImGui window */

		static constexpr unsigned int					MAX_NAME_SIZE = 50;					/*!< maximum length a custom name can be */

		//ECS::Entity*									selected_entity_{ nullptr };		/*!< the currently selected entity */
		int												selected_entity_id_{ -1 };
		std::string*									default_entity_name_{ nullptr };	/*!< the default entity name if no name is specified */
		std::string*									current_scene_name_{ nullptr };
		char											reset_name_[MAX_NAME_SIZE]{ '\0' };
		char											new_entity_name_[MAX_NAME_SIZE];	/*!< buffer for custom name when creating new entities */
		std::unordered_map<std::string, unsigned int>*	names_;								/*!< for repeated names to add an index behind */
		bool											hide_{ false };

		enum class VIEW
		{
			SCENE,
			LAYER,
			LOGIC
		};

		VIEW view_ = VIEW::SCENE;
		bool											scene_{ true };

		struct LayerData
		{
			std::string		name_;
			int*			layer_;
			int*			texture_id_;
			int				uid_;
			LayerData(const std::string& name, int uid, int* layer, int* textureId) : name_(name), uid_(uid), layer_(layer), texture_id_(textureId) {}
		};

		SceneTree(float x, float y, float sx, float sy);
		~SceneTree();

		/*!
		 * @brief ___JZEngine::SceneTree::Render()___
		 * ****************************************************************************************************
		 * Renders the ImGui window.
		 * ****************************************************************************************************
		*/
		void Render();

		void RenderScene();

		void RecursivelyAddChildObjectsToLayerData(ECS::Entity* entity);
		void BuildLayerData();
		void RenderLayers();

		void RenderLogic ();

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
		void RenderAllChildObjects(ECS::Entity* entity, int& id);

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
		std::string GetName();

		void RemoveAllEntities();

		enum class Confirmation {
			NONE,
			SAVE,
			REMOVE
		};

		Confirmation confirmation_flag_{ Confirmation::NONE };
		void RenderConfirmation();

		void SetSelectedEntity(int id);

		ECS::Entity* GetSelectedEntity();

	private:
		std::vector<LayerData> layers_;
	};
}