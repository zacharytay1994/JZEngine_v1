#pragma once
#include <tuple>

#include "../ECSSystems/ExampleSingleHeader.h"
#include "../ECSSystems/ExampleSplitHeaderSource.h"

#include "../ECSSystems/PhysicsSystem.h"
#include "../GraphicRendering/NonInstanceSpriteRenderer.h"
#include "../GraphicRendering/InstanceSpriteRenderer.h"
#include "../GraphicRendering/ExampleFloatAway.h"

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
				NonInstanceShader,
				InstanceShader,
				IsUnicorn,
				IsInputAffected,
				PhysicsComponent

				>;

			// add your structs/classes here that you want to be treated as Systems
			using System =
				std::tuple<
				
				Sprite,
				InstanceSprite,
				FloatAwayAllUnicorn,
				MakeUnicornAffectedByInput,
				PhysicsSystem
				
				>;
		};
	}
}