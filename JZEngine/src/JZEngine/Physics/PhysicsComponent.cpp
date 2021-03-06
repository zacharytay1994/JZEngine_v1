/*	__FILE HEADER__
*	File:		PhysicsComponent.cpp
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		ECS physics component.
*/

#include "PCH.h"
#include "PhysicsComponent.h"

namespace JZEngine
{
	PhysicsComponent::PhysicsComponent()
	:
	player{ false },

	size{ 1.f,1.f },
	position{ 0.f, 0.f },
	posnex{ 0.f, 0.f },
	velocity{ 0.f, 0.f },
	acceleration{ 0.0f,0.0f },
	rotation{ 0.f },
	angularVelocity{ 0.f },
	force{ 0.f,0.f },
		totalforce{ 0.f,0.f },
		externalforce{ 0.f,0.f },
	Area{ 0.f },
	Density{ 0.001f },
	Mass{ 1.0f },
	InvMass{ 1.0f },
	Restitution{ 0.5f },
	IsStatic{ true },
	IsAlive{ true },
	StaticFriction{ 0.5f},
	DynamicFriction{0.3f}
	{}

	PhysicsComponent::PhysicsComponent(const PhysicsComponent& s) { std::memcpy(this, &s, sizeof(s)); }
	PhysicsComponent::~PhysicsComponent()
	{
		this->IsAlive = false;
	}


}