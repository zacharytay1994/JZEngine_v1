#pragma once
#include "../Math/JZMath.h"
#include "../DebugTools/Log.h"


namespace JZEngine
{
	/* ________________________________ COLLISION DETECTION COMPONENTS ___________________________*/
	struct PhysicComponent
	{
		Vec2f velocity;
		Vec2f acceleration;
		float mass;
	};

	struct PhysicsSystem : public JZEngine::ECS::System
	{
		

		float gravity{ -0.0981f };

		PhysicsSystem();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;
	};
}