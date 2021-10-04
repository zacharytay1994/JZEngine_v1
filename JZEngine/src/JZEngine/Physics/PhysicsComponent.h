#pragma once


#include "../Math/JZMath.h"
#include "../Physics/PhysicsShapes.h"

namespace JZEngine
{

	struct PhysicsComponent
	{
		bool player{ false };
		int shapeid{};

		float mass{};
		float speed{};

		Vec2f size;
		Vec2f position;
		Vec2f posnex;
		Vec2f velocity{};
		Vec2f acceleration{ 0.0f,0.0f };

		Vec2f linearVelocity;

		float rotation{};
		float rotationalVelocity;
		Vec2f force;

		float Density;
		float Mass;
		float InvMass;
		float Restitution;
		float Area;

		bool IsStatic;

		union {
			Circle m_circle;
			//AABB m_AABB;
			Square m_square;
		};
		PhysicsComponent();
		PhysicsComponent(const PhysicsComponent& s);
		~PhysicsComponent();
	};
}
