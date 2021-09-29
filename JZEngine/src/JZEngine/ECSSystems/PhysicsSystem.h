#pragma once
#include "../Math/JZMath.h"
#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"


namespace JZEngine
{
	enum shapetype
	{
		circle = 0,
		aabb = 1
	};

	struct PhysicsComponent
	{
		int shapeid {};

		float mass{ 1.0f };//To be added
		float speed {};
		
		//Vec2f position_next;
		Vec2f velocity {};//vel = speed * dir
		Vec2f acceleration{ 0.0f,0.0f };

		union {
			Circle m_circle{};
			AABB m_AABB;
		};
		PhysicsComponent();
		PhysicsComponent(const PhysicsComponent& s);
		~PhysicsComponent();
	};

	struct PhysicsSystem : public JZEngine::ECS::System
	{
		
		std::vector<PhysicsComponent*> physics_cont;

		unsigned int j{ 0 };
		float gravity{ -0.0981f };

		PhysicsSystem();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;

		
	};
}