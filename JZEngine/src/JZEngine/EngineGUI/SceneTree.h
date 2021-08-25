#pragma once

#include <unordered_map>

#include "../ImGui/imgui.h"

namespace JZEngine
{
	namespace ECS
	{
		struct Entity;
	}

	struct SceneTree
	{
		ECS::Entity* selected_entity_{ nullptr };
		std::string default_entity_name_{ "Entity" };
		static constexpr unsigned int MAX_NAME_SIZE = 50;
		float x_, y_, sx_, sy_;
		std::unordered_map<std::string, unsigned int> names_;
		char new_entity_name_[MAX_NAME_SIZE];

		SceneTree(float x, float y, float sx, float sy);

		void Render();

		void RenderAllChildObjects(ECS::Entity* entity);

		std::string GetName();
	};
}