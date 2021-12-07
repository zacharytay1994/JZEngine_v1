/*	__FILE HEADER__
*	File:		ExampleParticleSystem.h
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Particle system example.
*/

#pragma once

#include "../ECS/ECS.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	struct ExampleParticleSystemComponent
	{
		float timer_{ 0.0f };
	};

	struct ExampleParticleSystem : ECS::System
	{
		//float timer_ = 0.0f;

		ExampleParticleSystem();

		virtual void Init() override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;
	};

	struct ExampleParticleComponent
	{
		float lifetime_{ 3.0f };
		float speed_{ 1.0f };
		Vec2f direction_{ 0.0,1.0f };
	};

	struct ExampleParticle : ECS::System
	{
		ExampleParticle();

		virtual void Update(const float& dt) override;
	};

	struct PopiahPSFlag
	{
		char flag;
	};

	struct PopiahParticleSystem : public ECS::System
	{
		float timer_ = 1.0f;

		PopiahParticleSystem();

		virtual void Init() override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;
	};
}