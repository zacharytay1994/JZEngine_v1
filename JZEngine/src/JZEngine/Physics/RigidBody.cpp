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
	Vec2f RigidBody::gravity{ 0.f, -398.1f };

	void RigidBody::ApplyForces(PhysicsComponent& pcomponent,const float& dt)
	{
		if (pcomponent.IsStatic)
			return;
		//pcomponent.angularVelocity += pcomponent.torque * (1.0f / momentofinertia) * dt;

		pcomponent.rotation += pcomponent.angularVelocity * dt;

		pcomponent.force += pcomponent.Mass * gravity;//force caused by gravity

		pcomponent.acceleration = pcomponent.force / pcomponent.Mass;

		//pcomponent.acceleration += gravity;//constant accel due to gravity

		pcomponent.velocity += pcomponent.acceleration * dt;
	
		pcomponent.position += pcomponent.velocity * dt;

		pcomponent.force = { 0.0f,0.0f };
	}

	void RigidBody::AddForce(PhysicsComponent& pcomponent, const Vec2f& force)
	{

		pcomponent.force += force;
	}

	void RigidBody::Move(PhysicsComponent& pcomponent,const  Vec2f& moveby)
	{
		pcomponent.position += moveby; 

	}

}
#endif