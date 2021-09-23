#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	PhysicsComponent::PhysicsComponent() {}
	PhysicsComponent::PhysicsComponent(const PhysicsComponent& s) { std::memcpy(this, &s, sizeof(s)); }
	PhysicsComponent::~PhysicsComponent() {}

	PhysicsSystem::PhysicsSystem()
	{
		RegisterComponents<PhysicsComponent,Transform>();
	}

	void PhysicsSystem::FrameBegin(const float& dt)
	{
		j = 0;
	}

	// updates once per entity component per system per frame
	void PhysicsSystem::Update(const float& dt)
	{
		PhysicsComponent& pcomponent = GetComponent<PhysicsComponent>();
		pcomponent.acceleration.y = gravity;

		pcomponent.velocity += pcomponent.acceleration * dt;

		Transform& ptransform = GetComponent<Transform>();
		ptransform.position_ += pcomponent.velocity * dt;

		if (pcomponent.shapeid == 0)
		{
			pcomponent.m_circle.m_center = ptransform.position_;
			pcomponent.m_circle.m_radius = 0.5f*ptransform.size_.x ;

		}

		bool am_inside{ false };
		for (int i = j; i < physics_cont.size(); ++i)
		{
			// to not check with itself
			if (physics_cont[i] != &pcomponent)
			{
				switch (pcomponent.shapeid)
				{
				case 0:
					switch (physics_cont[i]->shapeid)
					{
					case 0:
						// do circle circle code
						Log::Info("Collision", "is circle circle colliding");
						break;
					case 1:
						Log::Info("Collision", "is circle line colliding");
						// do circle line
						break;
					}
					break;
				case 1:
					switch (physics_cont[i]->shapeid)
					{
					case 0:
						// do line circle
						Log::Info("Collision", "is line circle colliding");
						break;
					case 1:
						// do line line
						Log::Info("Collision", "is line line colliding");
						break;
					}
					break;
				}
			}
			else
			{
				am_inside = true;
			}
		}
		if (!am_inside)
		{
			physics_cont.push_back(&pcomponent);
		}
		++j;

	}


}//JZEngine