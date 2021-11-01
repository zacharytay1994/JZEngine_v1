#pragma once
#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"


namespace JZEngine
{
	namespace Resolve
	{
		void ResolvePhysicsCollision(PhysicsComponent& componentA, PhysicsComponent& componentB, const Vec2f& normal, const float& depth);
	}
}
