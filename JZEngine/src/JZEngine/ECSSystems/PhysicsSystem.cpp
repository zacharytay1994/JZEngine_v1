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
		PhysicsComponent& pcomponent = GetComponent<PhysicsComponent>();
		Transform& tcomponent = GetComponent<Transform>();
		pcomponent.position = tcomponent.position_;
		pcomponent.size = tcomponent.size_;
		pcomponent.rotation = tcomponent.rotation_;
		
		//calculate area
		// Square = size.x * size.y;
		// Circle = PI * radius * radius
		if (!pcomponent.IsStatic)
		{
			if (pcomponent.shapeid == square)
			{
				pcomponent.Area = (pcomponent.size.x * pcomponent.size.y); // w * h 
				pcomponent.Mass = pcomponent.Density * pcomponent.Area;// Mass = Density * area (not using volume for 2D)
				pcomponent.InvMass = 1.f / pcomponent.Mass;
				pcomponent.MomentofInertia = pcomponent.Mass * (pcomponent.size.x * pcomponent.size.x + pcomponent.size.y * pcomponent.size.y) / 12.f;// 1/12*(m*(h^2 + w^2))
				//https://en.wikipedia.org/wiki/List_of_moments_of_inertia
			}
			if (pcomponent.shapeid == circle)
			{
				pcomponent.Area = Math::PI * pcomponent.size.x / 2.f * pcomponent.size.x / 2.f; // PI * r * r
				pcomponent.Mass = pcomponent.Density * pcomponent.Area;// Mass = Density * area (not using volume for 2D)
				pcomponent.InvMass = 1.f / pcomponent.Mass;
				pcomponent.MomentofInertia = pcomponent.Mass * (pcomponent.size.x * pcomponent.size.x) / 4.f;// 1/4*(m * r^2 )
				//https://en.wikipedia.org/wiki/List_of_moments_of_inertia
			}
		}
		else
			pcomponent.InvMass = 0.f;
		
		if (pcomponent.player)
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
				RigidBody::AddForce(pcomponent, force);

			}
			
		}

		if (!pause)
		{
			RigidBody::ApplyForces(pcomponent, dt);
		}

#ifdef PHYSICSDEBUG
		PhysicsDebug::DebugDrawLine(pcomponent.position,pcomponent.position + 0.33f * (pcomponent.velocity));	
#endif


		//update shapes & vertices
		if (pcomponent.shapeid == shapetype::circle)
		{
			pcomponent.m_circle.m_center = pcomponent.position;
			pcomponent.m_circle.m_radius = 0.5f * pcomponent.size.x;
		}
		if (pcomponent.shapeid == shapetype::square)
		{
			pcomponent.m_square = { pcomponent.position,pcomponent.size };

			for (int i = 0; i < 4; i++)
			{
				pcomponent.m_square.vertices[i] = 
					Math::GetRotatedVector((pcomponent.m_square.vertices[i] - tcomponent.position_)
					, Math::DegToRad(tcomponent.rotation_)) + tcomponent.position_;
			}

		}
#ifdef PHYSICSDEBUG
		PhysicsDebug::DebugDrawShape(pcomponent);
#endif
		//to update physics system container of components
		bool am_inside{ false };
		for (int i = 0; i < physics_cont.size(); ++i)
		{
			if (physics_cont[i] == &pcomponent)
			{
				am_inside = true;
				break;
			}
		}
		if (!am_inside)
		{
			physics_cont.push_back(&pcomponent);
			transform_cont.push_back(&tcomponent);
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
					PhysicsComponent& pcomponent = *physics_cont[i];
					RigidBody::ApplyForces(pcomponent, dt);
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
				Manifold CollData{};
				if (true == Collision::CheckPhysicsCollision(componentA, componentB, CollData))
				{
					//Fix collision
					if (componentA.IsStatic)
					{
						RigidBody::Move(componentB, CollData.normal * CollData.depth );
					}
					else if (componentB.IsStatic)
					{
						RigidBody::Move(componentA, -CollData.normal * CollData.depth );
					}
					else
					{
						RigidBody::Move(componentA, -CollData.normal * CollData.depth * componentA.InvMass);
						RigidBody::Move(componentB, CollData.normal * CollData.depth * componentB.InvMass);
					}
					//Apply impulses
					Collision::ResolvePhysicsCollision(componentA, componentB, CollData.normal, CollData.depth);

				}

			}
		}

		for (int i = 0; i < transform_cont.size(); ++i)
		{
			//Set transform component for graphics to render updated attributes
			transform_cont[i]->position_ = physics_cont[i]->position;
			transform_cont[i]->rotation_ = physics_cont[i]->rotation;
		}

	}

}//JZEngine