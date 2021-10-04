#pragma once
#if 1
#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"


namespace JZEngine
{
	class RigidBody
	{
	
	public:
		static void Step(PhysicsComponent& pcomponent, const float& dt);

		static void AddForce(PhysicsComponent& pcomponent, const Vec2f& force);

		static void Move(PhysicsComponent& pcomponent, const Vec2f& moveby);

	private:
		Vec2f gravity{ 0.f,-0.981f };// m / s*s

	};


}

#endif
