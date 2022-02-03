#pragma once

#include "../ECS/ECS.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	struct LeafParticleComponent
	{
		float lifetime_ { 10.0f };
		float life_ { lifetime_ };
		float mass_ { 1.0f };
		Vec2f gravity_ { 0.0f, -9.81f };
		Vec2f wind_direction_ { 0.0f, 0.0f };

		// private
		float scale_x_ { 1.0f };
	}; 
	
	struct LeafParticle : ECS::System
	{
		LeafParticle ();

		virtual void Update ( const float& dt ) override;
	};

	struct LeafParticleSystemComponent
	{
		float timer_ { 0.0f };
		float emission_rate_ { 0.02f };

		float wind_speed_ { 1.0f };
		float wind_direction_ { 0.0f };
		float wind_spread_ { 0.0f };
	};

	struct LeafParticleSystem : ECS::System
	{
		LeafParticleSystem ();

		virtual void Init () override;

		// updates once per entity component per system per frame
		virtual void Update ( const float& dt ) override;
	};
}