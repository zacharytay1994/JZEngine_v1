#pragma once

#include "../Math/JZMath.h"
#include "../Physics/PhysicsShapes.h"
#include "../Physics/Rect.h"
namespace JZEngine
{
	enum shapetype;

	struct CollisionComponent
	{
		int shapeid;
		int index;
		Vec2f pos;
		Vec2f size;
		Vec2f offset;
		Rect boundingrect;
		union {
			Circle m_circle;
			Square m_square;
		};

		CollisionComponent();
		CollisionComponent(const CollisionComponent& s);
		~CollisionComponent();
	};
}