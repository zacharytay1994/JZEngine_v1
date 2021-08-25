/*	__FILE HEADER__
*	File:	SceneTree.h
	Author: JZ
	Date:	26/08/21
	Brief:	Renders all entities in the scene tree on the 
			GUI using ImGui.
*/

#pragma once

#include <unordered_map>

#include "../ImGui/imgui.h"

namespace JZEngine
{
	namespace ECS
	{
		struct Entity;
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
		float x_, y_, sx_, sy_;		/*!< position and scale of ImGui window */

		static constexpr unsigned int					MAX_NAME_SIZE = 50;					/*!< maximum length a custom name can be */

		ECS::Entity*									selected_entity_{ nullptr };		/*!< the currently selected entity */
		std::string										default_entity_name_{ "Entity" };	/*!< the default entity name if no name is specified */
		char											new_entity_name_[MAX_NAME_SIZE];	/*!< buffer for custom name when creating new entities */
		std::unordered_map<std::string, unsigned int>	names_;								/*!< for repeated names to add an index behind */

		SceneTree(float x, float y, float sx, float sy);

		/*!
		 * @brief ___JZEngine::SceneTree::Render()___
		 * ****************************************************************************************************
		 * Renders the ImGui window.
		 * ****************************************************************************************************
		*/
		void Render();

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
		void RenderAllChildObjects(ECS::Entity* entity);

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
	};
}