#include "PCH.h"
#include "RigidBody.h"
#if 1


namespace JZEngine
{

	void RigidBody::Step(PhysicsComponent& pcomponent,const float& dt)
	{
		pcomponent.acceleration = pcomponent.force / pcomponent.Mass;
		pcomponent.velocity += pcomponent.acceleration * dt;

		pcomponent.position += pcomponent.velocity * dt;

		pcomponent.rotation += pcomponent.rotationalVelocity * dt;

		pcomponent.force = { 0.0f,0.0f };
	}
	void RigidBody::AddForce(PhysicsComponent& pcomponent, const Vec2f& force)
	{

		pcomponent.force = force;
	}

	void RigidBody::Move(PhysicsComponent& pcomponent,const  Vec2f& moveby)
	{
		pcomponent.position += moveby; 

	}

}
#endif