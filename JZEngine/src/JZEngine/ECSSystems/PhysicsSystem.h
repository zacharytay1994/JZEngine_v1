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
		AABB(Vec2f midpt, Vec2f scale)
		{
			min = midpt - (scale / 2.0f);
			max = midpt + (scale / 2.0f);
		}
	};
	struct LineSegment
	{
		Vec2f m_pt0;
		Vec2f m_pt1;
		Vec2f m_normal;

		LineSegment() : m_pt0 { }, m_pt1{}, m_normal{}	{}
		LineSegment(Vec2f pt0, Vec2f pt1) : m_pt0{ pt0 }, m_pt1{ pt1 }
		{
			m_normal.x = m_pt1.y - m_pt0.y;
			m_normal.y = -(m_pt1.x - m_pt0.x);
			m_normal.Normalize();
		}
		LineSegment(const LineSegment& k) : m_pt0{ k.m_pt0 }, m_pt1{ k.m_pt1 },m_normal{k.m_normal}
		{}
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
		float speed;
		Vec2f velocity;//vel = speed * dir
		Vec2f acceleration;
		float mass{ 1.0f };//To be added
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



		// INTERSECTION FUNCTIONS
		bool DynamicCollision_CircleLineSegment(const Circle& circle,			//Circle data - input
			const Vec2f& ptEnd,											//End circle position - input
			const LineSegment& lineSeg,												//Line segment - input
			Vec2f& interPt,												//Intersection point - output
			Vec2f& normalAtCollision,									//Normal vector at collision time - output
			float& interTime);															//Intersection time ti - output

		// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
		// In the case of "dynamic circle vs static pillar", velB will be 0.0f
		bool DynamicCollision_CircleCircle(const Circle& circleA,				//CircleA data - input
			const Vec2f& velA,														//CircleA velocity - input
			const Circle& circleB,													//CircleB data - input
			const Vec2f& velB,														//CircleA velocity - input
			Vec2f& interPtA,														//Intersection point of CircleA at collision time - output
			Vec2f& interPtB,														//Intersection point of CircleB at collision time - output
			float& interTime);														//intersection time - output


		// RESPONSE FUNCTIONS In this case the object bounces off the line
		void CollisionResponse_CircleLineSegment(const Vec2f& ptInter,							//Intersection position of the circle - input
			const Vec2f& normal,							//Normal vector of reflection on collision time - input
			Vec2f& ptEnd,									//Final position of the circle after reflection - output
			Vec2f& reflected);							//Normalized reflection vector direction - output


			// Extra credits
		void CollisionResponse_CircleCircle(Vec2f& normal,							//Normal vector of reflection on collision time - input
			const float interTime,													//Intersection time - input
			const Vec2f& velA,															//Velocity of CircleA - input
			const float& massA,														//Mass of CircleA - input
			Vec2f& interPtA,														//Intersection position of circle A at collision time - input
			const Vec2f& velB,															//Velocity of CircleB - input
			const float& massB,														//Mass of CircleB - input
			Vec2f& interPtB,														//Intersection position of circle B at collision time - input
			Vec2f& reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
			Vec2f& ptEndA,															//Final position of the circle A after reflection - output
			Vec2f& reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
			Vec2f& ptEndB);														//Final position of the circle B after reflection - output

			
		bool DynamicCollision_RectRect(const AABB& aabb1, const Vec2f& vel1,
			const AABB& aabb2, const Vec2f& vel2);

		bool StaticCollision_PointRect(const Vec2f& point,
			const AABB& aabb2);

	};
}