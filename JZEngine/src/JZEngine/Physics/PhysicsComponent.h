#pragma once


#include "../Math/JZMath.h"
#include "../Physics/PhysicsShapes.h"

namespace JZEngine
{

	struct PhysicsComponent
	{
		bool player{ false };
		int shapeid{};

		float speed{};

		Vec2f size;
		Vec2f position;
		Vec2f posnex;
		Vec2f velocity{};
		Vec2f acceleration{ 0.0f,0.0f };


		float rotation{};
		float rotationalVelocity{ 0.f };
		Vec2f force{ 0.f,0.f };

		float Density{ 0.f };// g / m*m*m
		float Mass{ 1.0f };
		float InvMass{ 0.f };
		float Restitution{ 0.5f };//The bounciness of the object
		float Area{ 0.f };

		bool IsStatic{ false };

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
