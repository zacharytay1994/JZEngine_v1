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