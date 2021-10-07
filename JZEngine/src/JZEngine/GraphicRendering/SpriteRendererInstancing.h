/*	__FILE HEADER__
*	File:		SpriteRendererInstancing.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		ECS sprite renderer to render instanced sprites.
*/

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
