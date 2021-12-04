/*	__FILE HEADER__
*	File:		ECSConfig.h
	Primary:	Zachary Tay
	Secondary:
	Date:		07/10/2021
	Brief:
	Registers all ECS components and systems here.
*/

#pragma once
#include <tuple>

#include "../ECSSystems/ExampleSingleHeader.h"
#include "../ECSSystems/ExampleSplitHeaderSource.h"

#include "../ECSSystems/CollisionShapeSystem.h"
#include "../ECSSystems/PhysicsSystem.h"
#include "../GraphicRendering/Systems/NonInstanceSpriteRenderer.h"
#include "../GraphicRendering/Systems/InstanceSpriteRenderer.h"
#include "../GraphicRendering/Systems/Background.h"
#include "../GraphicRendering/Systems/Text.h"
#include "../ECSSystems/FloatRandom.h"
#include "../ECSSystems/ExampleParticleSystem.h"
#include "../ECSSystems/MouseEvent.h"
#include "../ECSSystems/FollowMouseCursor.h"
#include "../SceneLogic/LogicContainer.h"
#include "../SceneLogic/DataContainer.h"

namespace JZEngine
{ 
	namespace ECS
	{
		struct ECSConfig
		{
			// add your structs/classes here that you want to be treated as Components
			using Component =
				std::tuple<

				Transform ,	// transform must always be the first component, for hardcode reasons sorry pls dont change it
				SpriteLayer,
				Texture ,
				NonInstanceShader ,
				InstanceShader ,
				CollisionComponent,
				PhysicsComponent ,
				Parallax ,
				NotBackground ,
				TextData ,
				Animation2D ,
				RandomMovement ,
				ExampleParticleSystemComponent ,
				ExampleParticleComponent ,
				PopiahPSFlag,
				MouseEvent,
				FollowMouseCursor,
				CustomLogicContainer,
				CustomDataContainer
		

				>;

			// add your structs/classes here that you want to be treated as Systems
			using System =
				std::tuple<
				ParallaxBackground ,
				CollisionShapeSystem,
				PhysicsSystem,
				Sprite,
				InstanceSprite,
				Text ,
				FloatRandom ,
				ExampleParticleSystem ,
				ExampleParticle ,
				PopiahParticleSystem,
				MouseEventSystem,
				FollowMouseCursorSystem,
				LogicContainerSystem

				>;
		};
	}
}