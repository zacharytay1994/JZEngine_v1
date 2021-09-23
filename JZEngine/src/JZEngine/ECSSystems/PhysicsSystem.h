#pragma once
#include "../Math/JZMath.h"
#include "../DebugTools/Log.h"


namespace JZEngine
{
	struct Circle
	{
		Vec2f m_center;
		float m_radius;
		float m_mass;//to be used
	};

	struct AABB
	{
		Vec2f min;
		Vec2f max;
	};
	struct LineSegment
	{
		Vec2f m_pt0;
		Vec2f m_pt1;
		Vec2f m_normal;
	};

	struct Shape
	{
		union {
			Circle m_circle;
			AABB m_AABB;
		};
		Shape();
		Shape(const Shape& s);
		~Shape();
	};

	struct PhysicsComponent
	{
		Vec2f velocity;
		Vec2f acceleration;
		float mass;//To be added
		int shapeid{ 0 }; //0 for circle //1 for AABB
		union {
			Circle m_circle;
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