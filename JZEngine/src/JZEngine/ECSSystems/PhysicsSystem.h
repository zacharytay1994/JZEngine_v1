/*	__FILE HEADER__
*	File:		PhysicsSystem.h
	Primary:	Deon Khong
	Secondary:
	Date:		07/10/2021
	Brief:
	Physics system handles collision and resolution of physics objects.
*/

#pragma once

#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/Collision.h"

#include "../Physics/RigidBody.h"

namespace JZEngine
{
	struct PhysicsSystem : public JZEngine::ECS::System
	{
		PhysicsSystem();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;

		virtual void FrameEnd(const float& dt) override;
	private:
		std::vector<PhysicsComponent*> physics_cont;

		bool pause{ false };
		bool stepbystep{ false };
	};
}