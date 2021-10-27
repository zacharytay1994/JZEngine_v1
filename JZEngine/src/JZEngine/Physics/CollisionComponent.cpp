#include "PCH.h"
#include "CollisionComponent.h"


namespace JZEngine {
	CollisionComponent::CollisionComponent() = default;

	CollisionComponent::CollisionComponent(const CollisionComponent& s)
	{
		std::memcpy(this, &s, sizeof(s));
	}

	CollisionComponent::~CollisionComponent()
	{
	}
}