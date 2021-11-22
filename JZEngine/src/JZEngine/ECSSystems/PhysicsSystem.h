/*	__FILE HEADER__
*	File:		PhysicsSystem.h
	Primary:	Deon Khong
	Secondary:
	Date:		07/10/2021
	Brief:
	Physics system handles collision and resolution of physics objects.
*/

#pragma once
#include "../GraphicRendering/Systems/TransformComponent.h"

#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/CollisionComponent.h"
#include "../Physics/CollisionSystem.h"
#include "../Physics/ResolveSystem.h"
#include "../Physics/Force.h"
#include "../Input/Input.h"
#include "../Physics/QuadTree.h"
#include "../Physics/RigidBody.h"
#include "../EngineConfig.h"


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
		std::vector<Transform*> transform_cont;
		std::vector<CollisionComponent*> collision_cont;



		bool pause{ false };
		bool stepbystep{ false };
	};


}