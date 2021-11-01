#pragma once

#include "../Math/JZMath.h"
#include "../Physics/PhysicsShapes.h"
namespace JZEngine
{
	enum shapetype;

	struct CollisionComponent
	{
		int shapeid;
		Vec2f size;
		Vec2f offset;
		union {
			Circle m_circle;
			Square m_square;
			AABB m_aabb;
		};

		CollisionComponent();
		CollisionComponent(const CollisionComponent& s);
		~CollisionComponent();
	};
}