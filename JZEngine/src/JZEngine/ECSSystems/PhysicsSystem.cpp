/*	__FILE HEADER__
*	File:		PhysicsSystem.cpp
	Primary:	Deon Khong
	Secondary:
	Date:		07/10/2021
	Brief:
	Physics system handles collision and resolution of physics objects.
*/

#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"
#include "../Physics/PhyicsDebug.h"
#include "PhysicsSystem.h"
#include "../Input/Input.h"
#include "../Physics/RigidBody.h"

#define PHYSICSDEBUG 

namespace JZEngine
{
	std::vector<Transform*> transform_cont;

	PhysicsSystem::PhysicsSystem()
	{
		RegisterComponents<PhysicsComponent, Transform>();
	}

	void PhysicsSystem::FrameBegin(const float& dt) 
	{
		UNREFERENCED_PARAMETER(dt);
		for (int i = 0; i < physics_cont.size(); ++i)
		{
			if (physics_cont[i]->IsAlive == false)
			{
				physics_cont.erase(physics_cont.begin() + i);
				transform_cont.erase(transform_cont.begin() + i);
			}
		}
	}

	//_____Updates Physic Components____//
	void PhysicsSystem::Update(const float& dt)
	{
		PhysicsComponent& current_pcomponent = GetComponent<PhysicsComponent>();
		Transform& current_transform = GetComponent<Transform>();
		current_pcomponent.position = current_transform.position_;
		current_pcomponent.size = current_transform.size_;
		current_pcomponent.rotation = current_transform.rotation_;
		
		//calculate area
		// Square = size.x * size.y;
		// Circle = PI * radius * radius
		
		if (!current_pcomponent.IsStatic)
		{
			if(current_pcomponent.shapeid ==square)
				current_pcomponent.Area = (current_transform.size_.x * current_transform.size_.y); // w * h 
			if (current_pcomponent.shapeid == circle)
				current_pcomponent.Area = Math::PI * current_transform.size_.x/2.f * current_transform.size_.x/2.f ; // PI * r * r

			current_pcomponent.Mass = current_pcomponent.Density * current_pcomponent.Area;// Mass = Density * area (not using volume for 2D)
			current_pcomponent.InvMass = 1.f / current_pcomponent.Mass;
		}
		else
			current_pcomponent.InvMass = 0.f;
		
		if (current_pcomponent.player)
		{
			float dx = 0.f;
			float dy = 0.f;
			float forcemagnitude = 1500.f;
			if (InputHandler::IsKeyPressed(KEY::KEY_W))
				++dy;
			if (InputHandler::IsKeyPressed(KEY::KEY_A))
				--dx;
			if (InputHandler::IsKeyPressed(KEY::KEY_S))
				--dy;
			if (InputHandler::IsKeyPressed(KEY::KEY_D))
				++dx;

			if (dx != 0.f || dy != 0.f)
			{
				Vec2f forcedirection{ dx,dy };
				forcedirection.Normalize();
				Vec2f force = forcedirection * forcemagnitude;
				RigidBody::AddForce(current_pcomponent, force);

			}
			
		}

		if (!pause)
		{
			RigidBody::ApplyForces(current_pcomponent, dt);
		}

#ifdef PHYSICSDEBUG
		PhysicsDebug::DebugDrawLine(current_pcomponent.position,current_pcomponent.position + 0.33f * (current_pcomponent.velocity));	
#endif


		//update shapes & vertices
		if (current_pcomponent.shapeid == shapetype::circle)
		{
			current_pcomponent.m_circle.m_center = current_pcomponent.position;
			current_pcomponent.m_circle.m_radius = 0.5f * current_pcomponent.size.x;
		}
		if (current_pcomponent.shapeid == shapetype::square)
		{
			current_pcomponent.m_square = { current_pcomponent.position,current_pcomponent.size };

			for (int i = 0; i < 4; i++)
			{
				current_pcomponent.m_square.vertices[i] = 
					Math::GetRotatedVector((current_pcomponent.m_square.vertices[i] - current_transform.position_)
					, Math::DegToRad(current_transform.rotation_)) + current_transform.position_;
			}

		}
#ifdef PHYSICSDEBUG
		PhysicsDebug::DebugDrawShape(current_pcomponent);
#endif
		//to update physics system container of components
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
#ifdef PHYSICSDEBUG
		if (InputHandler::IsKeyTriggered(KEY::KEY_I))
		{
			pause = !pause;
		}
		if (pause)
		{
			if (InputHandler::IsKeyTriggered(KEY::KEY_O))
			{
				for (int i = 0; i < physics_cont.size(); ++i)
				{
					PhysicsComponent& current_pcomponent = *physics_cont[i];
					RigidBody::ApplyForces(current_pcomponent, dt);
				}
				
			}
		}
#endif
		//optimised double for loop for collision & response
		for (int i = 0; i < (int)physics_cont.size() - 1; ++i)
		{
			PhysicsComponent& componentA = *physics_cont[i];
			for (int j = i+1; j < physics_cont.size(); ++j)
			{
				PhysicsComponent& componentB = *physics_cont[j];

				if (componentA.IsStatic && componentB.IsStatic)
					continue;

				Vec2f normal{ 0.f,0.f };
				float depth;
				if (true == Collision::CheckPhysicsComponentCollision(componentA, componentB, normal, depth))
				{
					if (componentA.IsStatic)
					{
						RigidBody::Move(componentB, normal * depth );
					}
					else if (componentB.IsStatic)
					{
						RigidBody::Move(componentA, -normal * depth );
					}
					else
					{
						
						RigidBody::Move(componentA, -normal * depth * componentA.InvMass);
						RigidBody::Move(componentB, normal * depth * componentB.InvMass);
					}
					Collision::ResolvePhysicsComponentCollision(componentA, componentB, normal, depth);

				}

			}
		}

		for (int i = 0; i < transform_cont.size(); ++i)
		{
			//Set transform component for graphics to render updated values
			transform_cont[i]->position_ = physics_cont[i]->position;
			transform_cont[i]->rotation_ = physics_cont[i]->rotation;
		}

	}

}//JZEngine