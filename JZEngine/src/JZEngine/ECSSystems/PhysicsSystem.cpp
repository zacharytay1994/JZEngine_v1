#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"
#include "PhysicsSystem.h"
#include "../Input/Input.h"
#include "../Physics/RigidBody.h"


namespace JZEngine
{
	std::vector<Transform*> transform_cont;

	
	PhysicsComponent::PhysicsComponent() {}
	PhysicsComponent::PhysicsComponent(const PhysicsComponent& s) { std::memcpy(this, &s, sizeof(s)); }
	PhysicsComponent::~PhysicsComponent() {}

	PhysicsSystem::PhysicsSystem()
	{
		RegisterComponents<PhysicsComponent,Transform>();
	}

	void PhysicsSystem::FrameBegin(const float& dt)
	{
		
	}

	//_____Updates Physic Components and calculates posnex for Collision & Response____//
	void PhysicsSystem::Update(const float& dt)
	{
		PhysicsComponent& current_pcomponent = GetComponent<PhysicsComponent>();
		Transform& current_transform = GetComponent<Transform>();
		current_pcomponent.position = current_transform.position_;
		current_pcomponent.size = current_transform.size_;
		current_pcomponent.rotation = current_transform.rotation_;
		//current_pcomponent.Restitution = 0.5f;
		//current_pcomponent.Mass = 20.0f;

		//current_pcomponent.posnex = current_transform.position_ + current_pcomponent.velocity * dt;

		if (current_pcomponent.player)
		{
			float dx = 0.f;
			float dy = 0.f;
			float forcemagnitude = 8000.f;
			if (InputHandler::IsKeyPressed(KEY::KEY_W))
				dy++;
			if (InputHandler::IsKeyPressed(KEY::KEY_A))
				dx--;
			if (InputHandler::IsKeyPressed(KEY::KEY_S))
				dy--;
			if (InputHandler::IsKeyPressed(KEY::KEY_D))
				dx++;

			if (dx != 0.f || dy != 0.f)
			{
				Vec2f forcedirection{ dx,dy };
				forcedirection.Normalize();
				Vec2f force = forcedirection * forcemagnitude;
				RigidBody::AddForce(current_pcomponent, force);

			}
			
		}

		RigidBody::Step(current_pcomponent, dt);

		//update vertices
		if (current_pcomponent.shapeid == shapetype::circle)
		{
			current_pcomponent.m_circle.m_center = current_pcomponent.position;
			current_pcomponent.m_circle.m_radius = 0.5f * current_pcomponent.size.x;
			RendererDebug::DrawCircle(current_pcomponent.m_circle.m_center, current_pcomponent.m_circle.m_radius);
		}
		if (current_pcomponent.shapeid == shapetype::square)
		{
			current_pcomponent.m_square = { current_pcomponent.position,current_pcomponent.size };

#if 1

			for (int i = 0; i < 4; i++)
			{
				current_pcomponent.m_square.vertices[i] = Math::GetRotatedVector((current_pcomponent.m_square.vertices[i] - current_transform.position_), Math::DegToRad(current_transform.rotation_)) + current_transform.position_;

			}
			for (int i = 0; i < 4; i++)
			{

				if (i == 3)
					RendererDebug::DrawLine(current_pcomponent.m_square.vertices[i], current_pcomponent.m_square.vertices[0]);
				else
					RendererDebug::DrawLine(current_pcomponent.m_square.vertices[i], current_pcomponent.m_square.vertices[(i + 1)]);
			}
#endif
		}


		bool am_inside{ false };
		for (int i = 0; i < physics_cont.size(); ++i)
		{
			if (physics_cont[i] == &current_pcomponent)
			{
				am_inside = true;
				break;
			}
		}
		if (!am_inside)
		{
			physics_cont.push_back(&current_pcomponent);
			transform_cont.push_back(&current_transform);
		}
	}//__________________UPDATE_________________________//


	void PhysicsSystem::FrameEnd(const float& dt)
	{
		//optimised double for loop
		for (int i = 0; i < physics_cont.size() - 1; ++i)
		{
			PhysicsComponent& componentA = *physics_cont[i];
			for (int j = i+1; j < physics_cont.size(); ++j)
			{
				PhysicsComponent& componentB = *physics_cont[j];

				Vec2f normal{ 0.f,0.f };
				float depth;
				if (true == Collision::CheckPhysicsComponentCollision(componentA, componentB, normal, depth))
				{
					RigidBody::Move(componentA, -normal * depth /2.f);
					RigidBody::Move(componentB, normal * depth / 2.f);



					Collision::ResolvePhysicsComponentCollision(componentA, componentB, normal, depth);

				}

			}
		}
		for (int i = 0; i < transform_cont.size(); ++i)
		{
			//transform_cont[i]->position_ = physics_cont[i]->posnex;
			transform_cont[i]->position_ = physics_cont[i]->position;
			transform_cont[i]->rotation_ = physics_cont[i]->rotation;
		}

	}

}//JZEngine