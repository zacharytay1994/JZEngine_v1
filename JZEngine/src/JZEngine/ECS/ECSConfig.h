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

#include "../ECSSystems/PhysicsSystem.h"
#include "../GraphicRendering/NonInstanceSpriteRenderer.h"
#include "../GraphicRendering/InstanceSpriteRenderer.h"
#include "../GraphicRendering/Background.h"
#include "../GraphicRendering/Text.h"
#include "../ECSSystems/FloatRandom.h"
#include "../ECSSystems/ExampleParticleSystem.h"

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
				PopiahPSFlag
		

				>;

			// add your structs/classes here that you want to be treated as Systems
			using System =
				std::tuple<

				ParallaxBackground ,
				Sprite ,
				InstanceSprite ,
				PhysicsSystem ,
				Text ,
				FloatRandom ,
				ExampleParticleSystem ,
				ExampleParticle ,
				PopiahParticleSystem

				>;
		};
	}
}