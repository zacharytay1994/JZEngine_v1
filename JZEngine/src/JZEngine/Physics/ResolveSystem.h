/*	__FILE HEADER__
*	File:		ResolveSystem.h
	Primary:	Deon Khong
	Date:		11/11/21
	Brief:		Header file For applying impulse after collision of physics objects
*/
#pragma once
#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/CollisionSystem.h"
#include "../Physics/RigidBody.h"
namespace JZEngine
{
	namespace Resolve
	{
		void ApplyImpulse(PhysicsComponent& componentA, PhysicsComponent& componentB, const Manifold& CollData);

		void ResolveCollision(PhysicsComponent& componentA, PhysicsComponent& componentB, const Manifold& CollData);
	}
}
