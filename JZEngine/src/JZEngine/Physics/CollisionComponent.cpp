/*	__FILE HEADER__
*	File:		CollisionComponent.cpp
	Primary:	Deon Khong
	Date:		11/11/21
	Brief:		Collision Component for physics system
*/
#include "PCH.h"
#include "CollisionComponent.h"


namespace JZEngine {
	CollisionComponent::CollisionComponent() : shapeid{ 0 }, offset{ 0.0f, 0.0f }, size{ 50.0f, 50.0f }
	{}

	CollisionComponent::CollisionComponent(const CollisionComponent& s)
	{
		std::memcpy(this, &s, sizeof(s));
	}

	CollisionComponent::~CollisionComponent()
	{
	}
}