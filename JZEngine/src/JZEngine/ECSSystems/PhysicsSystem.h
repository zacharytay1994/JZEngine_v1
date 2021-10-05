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
		
		std::vector<PhysicsComponent*> physics_cont;
		//std::vector<PhysicsComponent*> polygon_cont;

		bool pause{ false };
		bool stepbystep{ false };
		float gravity{ -0.0981f };

		PhysicsSystem();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;

		virtual void FrameEnd(const float& dt) override;

	
	};
}