#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{


	PhysicsSystem::PhysicsSystem()
	{
		RegisterComponents<PhysicComponent,Transform>();
	}

	void PhysicsSystem::FrameBegin(const float& dt)
	{

	}

	// updates once per entity component per system per frame
	void PhysicsSystem::Update(const float& dt)
	{
		PhysicComponent& pcomponent = GetComponent<PhysicComponent>();
		pcomponent.acceleration.y = gravity;

		pcomponent.velocity += pcomponent.acceleration * dt;

		Transform& ptransform = GetComponent<Transform>();
		ptransform.position_ += pcomponent.velocity * dt;




	}


}//JZEngine