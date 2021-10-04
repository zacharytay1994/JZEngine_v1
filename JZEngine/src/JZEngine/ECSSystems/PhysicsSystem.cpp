#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"
#include "PhysicsSystem.h"
#include "../Input/Input.h"



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

		//acceleration
		if (current_pcomponent.shapeid == shapetype::circle)
			current_pcomponent.velocity += current_pcomponent.acceleration * dt;

		current_pcomponent.posnex = current_transform.position_ + current_pcomponent.velocity * dt;

		
		if (current_pcomponent.shapeid == shapetype::circle)
		{
			current_pcomponent.m_circle.m_center = current_transform.position_;
			current_pcomponent.m_circle.m_radius = 0.5f * current_transform.size_.x;
		}
		if (current_pcomponent.shapeid == shapetype::square)
		{
			current_pcomponent.m_square = { current_transform.position_,current_transform.size_ };

#if 1

			for (int i = 0; i <4; i++)
			{

				RendererDebug::DrawPoint(current_pcomponent.m_square.midpoint);
				current_pcomponent.m_square.vertices[i] = Math::GetRotatedVector( (current_pcomponent.m_square.vertices[i] - current_transform.position_), Math::PI / 4.0f) + current_transform.position_;

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

		if (current_pcomponent.player)
		{
			if (InputHandler::IsKeyPressed(KEY::KEY_W))
				current_pcomponent.position.y += 1.0f;
			if (InputHandler::IsKeyPressed(KEY::KEY_A))
				current_pcomponent.position.x -= 1.0f;
			if (InputHandler::IsKeyPressed(KEY::KEY_S))
				current_pcomponent.position.y -= 1.0f;
			if (InputHandler::IsKeyPressed(KEY::KEY_D))
				current_pcomponent.position.x += 1.0f;
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

				if (&componentB == &componentA)
					continue;

				Collision::CheckPhysicsComponentCollision(componentA, componentB);

			}
		}
		for (int i = 0; i < transform_cont.size(); ++i)
		{
			//transform_cont[i]->position_ = physics_cont[i]->posnex;
			transform_cont[i]->position_ = physics_cont[i]->position;
		}

	}

}//JZEngine