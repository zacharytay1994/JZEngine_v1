#pragma once

#include "../ImGui/imgui.h"

namespace JZEngine
{
	namespace ECS
	{
		struct Entity;
	}

	struct SceneTree
	{
		float x_, y_, sx_, sy_;

		SceneTree(float x, float y, float sx, float sy);

		void Render();

		void RenderAllChildObjects(ECS::Entity* entity);
	};
}