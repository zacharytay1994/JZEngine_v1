#pragma once

#include <vector>
#include "../Math/JZMath.h"

namespace JZEngine
{
	class RendererInstancing;
	class SpriteRendererInstancing
	{
	public:
		SpriteRendererInstancing();
		~SpriteRendererInstancing();

		void DrawInstances();

		RendererInstancing* renderer_{ nullptr };
	};
}
