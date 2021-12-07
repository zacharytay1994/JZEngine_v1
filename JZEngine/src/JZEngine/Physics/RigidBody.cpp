/*	__FILE HEADER__
*	File:		RegidBody.cpp
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Physics rigidbodies.
*/

#include "PCH.h"
#include "RigidBody.h"
#if 1

namespace JZEngine
{
	

	void RigidBody::Update(PhysicsComponent& pcomponent,const float& dt)
	{
		if (pcomponent.IsStatic)
			return;
		//pcomponent.angularVelocity += pcomponent.torque * (1.0f / momentofinertia) * dt;

		pcomponent.rotation += pcomponent.angularVelocity * dt;

	

		pcomponent.acceleration += pcomponent.totalforce / pcomponent.Mass;

		pcomponent.velocity += pcomponent.acceleration * dt;
	
		pcomponent.position += pcomponent.velocity * dt;

		pcomponent.totalforce = { 0.0f,0.0f };
	}


	void RigidBody::Move(PhysicsComponent& pcomponent,const  Vec2f& moveby)
	{
		pcomponent.position += moveby; 

	}

}
#endif