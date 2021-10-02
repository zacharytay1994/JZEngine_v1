#pragma once
#include "../Math/JZMath.h"
#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"
//#include "../Physics/PhysicsBody.h"

namespace JZEngine
{


	struct PhysicsComponent
	{
		int shapeid {};

		float mass {};
		float speed {};
		
		Vec2f posnex;
		Vec2f velocity {};//vel = speed * dir
		Vec2f acceleration{ 0.0f,0.0f };

		Vec2f linearVelocity;
		float rotationalVelocity;
		Vec2f force;

		float Density;
		float Mass;
		float InvMass;
		float Restitution;
		float Area;

		bool IsStatic;

		union {
			Circle m_circle;
			//AABB m_AABB;
			Square m_square;
		};
		PhysicsComponent();
		PhysicsComponent(const PhysicsComponent& s);
		~PhysicsComponent();
	};

	struct PhysicsSystem : public JZEngine::ECS::System
	{
		
		std::vector<PhysicsComponent*> physics_cont;
		//std::vector<PhysicsComponent*> polygon_cont;

		
		float gravity{ -0.0981f };

		PhysicsSystem();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;

		virtual void FrameEnd(const float& dt) override;
		
	};
}