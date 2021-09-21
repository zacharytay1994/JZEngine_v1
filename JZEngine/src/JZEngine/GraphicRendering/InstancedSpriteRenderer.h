#pragma once

#include <vector>
#include "../Math/JZMath.h"

namespace JZEngine
{
	class RendererInstancing;
	class InstancedSpriteRenderer
	{
	public:
		InstancedSpriteRenderer();
		~InstancedSpriteRenderer();

		void DrawInstances();

		RendererInstancing* renderer_{ nullptr };
	};
}
