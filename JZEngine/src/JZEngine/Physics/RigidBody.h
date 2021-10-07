/*	__FILE HEADER__
*	File:		RegidBody.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Physics rigidbodies.
*/

#pragma once
#if 1
#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"


namespace JZEngine
{
	class RigidBody
	{
	
	public:
		static void ApplyForces(PhysicsComponent& pcomponent, const float& dt);

		static void AddForce(PhysicsComponent& pcomponent, const Vec2f& force);

		static void Move(PhysicsComponent& pcomponent, const Vec2f& moveby);

	private:
		static Vec2f gravity;// m / s*s

	};


}

#endif
