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

		Vec2f size; // cm
		Vec2f position;
		Vec2f posnex;
		Vec2f velocity{ 0.f, 0.f }; // cm/s
		Vec2f acceleration{ 0.0f,0.0f }; // cm/s^2


		float rotation{ 0.f };
		float rotationalVelocity{ 0.f };
		Vec2f force{ 0.f,0.f };

		float Area{ 0.f }; // size * size (m^2)
		float Density{ 10.f };// mass / volume(area for 2D) // kg/cm^2
		float Mass{ 1.0f }; // kg
		float InvMass{ 1.0f }; // 1/kg
		float Restitution{ 0.5f };
		//The coefficient of Restitution [ 0.0f to 1.0f ]
		

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
