/*	__FILE HEADER__
*	File:		PhysicsComponent.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		ECS physics component.
*/

#pragma once

#include "../Math/JZMath.h"


namespace JZEngine
{

	struct PhysicsComponent
	{
		bool player{ false };


		Vec2f size; // cm
		Vec2f position;
		Vec2f posnex;
		Vec2f velocity; // cm/s
		Vec2f acceleration; // cm/s^2

		float rotation;
		float angularVelocity;
		Vec2f force;

		float Area; // size * size (m^3)
		float Density;// mass / volume(area for 2D) // kg/cm^2
		float Mass; // kg
		float InvMass; // 1/kg
		float Restitution;
		//The coefficient of Restitution [ 0.0f to 1.0f ]

		float StaticFriction;  
		float DynamicFriction;

		//float MomentofInertia;


		bool IsStatic{ true };
		bool IsAlive{ true };
		bool IsResting{ false };

		//Mat3f ModeltoWorld;


		PhysicsComponent();
		PhysicsComponent(const PhysicsComponent& s);
		~PhysicsComponent();
	};
}
