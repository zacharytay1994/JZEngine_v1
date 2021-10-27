#pragma once

#include "../Math/JZMath.h"
#include "../Physics/PhysicsShapes.h"
namespace JZEngine
{
	enum shapetype;

	struct CollisionComponent
	{
		int shapeid{};
		union {
			Circle m_circle;
			Square m_square;
		};

		CollisionComponent();
		CollisionComponent(const CollisionComponent& s);
		~CollisionComponent();
	};
}