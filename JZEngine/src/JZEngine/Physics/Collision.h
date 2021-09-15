#pragma once

#include "../BuildDefinitions.h"
#include "../Math/Math.cpp"

namespace JZEngine
{

	struct LineSegment
	{
		Vec2f	m_pt0;
		Vec2f	m_pt1;
		Vec2f	m_normal;

		LineSegment(const Vec2f& position,
			float scale,
			float direction)
		{
			m_pt1.x = position.x + scale / 2.0f * cosf(direction);
			m_pt1.y = position.y + scale / 2.0f * sinf(direction);
			m_pt0.x = position.x + scale / 2.0f * cosf(direction + PI);
			m_pt0.y = position.y + scale / 2.0f * sinf(direction + PI);

			m_normal.x = m_pt1.y - m_pt0.y;
			m_normal.y = -(m_pt1.x - m_pt0.x);
			m_normal.Normalize();
		}

	};

	struct Circle
	{
		Vec2f  m_center;
		float	m_radius;

		float   m_mass{ 1.0f };


	};


	struct AABB
	{
		Vec2f min;
		Vec2f max;

		/**
		 * Contrust AABB
		 * 
		 * \param minn Min point
		 * \param maxx Max point
		 */
		AABB(Vec2f minn, Vec2f maxx) : min{ minn }, max{ maxx } 
		{}

		/**
		 * Contrust AABB
		 * 
		 * \param Mid-point of the instance
		 * \param x_offset	
		 * \param y_offset
		 */
		AABB(Vec2f point, float x_offset, float y_offset) :
			min{ point.x - x_offset	, point.y - y_offset }, max{ point.x + x_offset	, point.y + y_offset }
			{}
	};

	// INTERSECTION FUNCTIONS
	int DynamicCollision_CircleLineSegment(const Circle& circle,			//Circle data - input
		const Vec2f& ptEnd,											//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		Vec2f& interPt,												//Intersection point - output
		Vec2f& normalAtCollision,									//Normal vector at collision time - output
		float& interTime);															//Intersection time ti - output
												
	// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
	// In the case of "dynamic circle vs static pillar", velB will be 0.0f
	int DynamicCollision_CircleCircle(const Circle& circleA,				//CircleA data - input
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
		Vec2f& velA,															//Velocity of CircleA - input
		const float& massA,														//Mass of CircleA - input
		Vec2f& interPtA,														//Intersection position of circle A at collision time - input
		Vec2f& velB,															//Velocity of CircleB - input
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
}
