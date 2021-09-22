#pragma once
#include <tuple>

#include "../ECSSystems/ExampleSingleHeader.h"
#include "../ECSSystems/ExampleSplitHeaderSource.h"

#include "../GraphicRendering/NonInstanceSpriteRenderer.h"

namespace JZEngine
{
	namespace ECS
	{
		struct ECSConfig
		{
			// add your structs/classes here that you want to be treated as Components
			using Component =
				std::tuple<
				
				Transform,
				Texture,
				TestComponent2,
				TestComponent3

				>;

			// add your structs/classes here that you want to be treated as Systems
			using System =
				std::tuple<
				
				Sprite,
				TestSystem,
				TestSystem2
				
				>;
		};
	}
}