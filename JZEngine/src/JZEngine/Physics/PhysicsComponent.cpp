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
	shapeid{ 0 },
	size{ 1.f,1.f },
	position{ 0.f, 0.f },
	posnex{ 0.f, 0.f },
	velocity{ 0.f, 0.f },
	acceleration{ 0.0f,0.0f },
	rotation{ 0.f },
	rotationalVelocity{ 0.f },
	force{ 0.f,0.f },
	Area{ 0.f },
	Density{ 10.f },
	Mass{ 1.0f },
	InvMass{ 1.0f },
	Restitution{ 0.5f },
	IsStatic{ true },
	IsAlive{ true }
	{}

	PhysicsComponent::PhysicsComponent(const PhysicsComponent& s) { std::memcpy(this, &s, sizeof(s)); }
	PhysicsComponent::~PhysicsComponent()
	{
		this->IsAlive = false;
	}


}