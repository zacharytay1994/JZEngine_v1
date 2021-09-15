#pragma once

#include "../BuildDefinitions.h"
#include "../Math/Math.cpp"

namespace JZEngine
{

	struct LineSegment
	{
		Vec2<float>	m_pt0;
		Vec2<float>	m_pt1;
		Vec2<float>	m_normal;
	};

	void BuildLineSegment(LineSegment& lineSegment,	//Line segment reference - input
		const Vec2<float>& pos,		//Position - input
		float scale,					//Scale - input
		float dir);						//direction - input

	struct Circle
	{
		Vec2<float>  m_center;
		float	m_radius;

		// Extra credits
		float   m_mass{ 1.0f };
	};

	struct Ray
	{
		Vec2<float>	m_pt0;
		Vec2<float>	m_dir;
	};

	struct AABB
	{
		Vec2<float> min;
		Vec2<float> max;
	};

	// INTERSECTION FUNCTIONS
	int DynamicCollision_CircleLineSegment(const Circle& circle,			//Circle data - input
		const Vec2<float>& ptEnd,											//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		Vec2<float>& interPt,												//Intersection point - output
		Vec2<float>& normalAtCollision,									//Normal vector at collision time - output
		float& interTime);															//Intersection time ti - output
												
	// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
	// In the case of "dynamic circle vs static pillar", velB will be 0.0f
	int DynamicCollision_CircleCircle(const Circle& circleA,				//CircleA data - input
		const Vec2<float>& velA,														//CircleA velocity - input
		const Circle& circleB,													//CircleB data - input
		const Vec2<float>& velB,														//CircleA velocity - input
		Vec2<float>& interPtA,														//Intersection point of CircleA at collision time - output
		Vec2<float>& interPtB,														//Intersection point of CircleB at collision time - output
		float& interTime);														//intersection time - output


	// RESPONSE FUNCTIONS In this case the object bounces off the line
	void CollisionResponse_CircleLineSegment(const Vec2<float>& ptInter,							//Intersection position of the circle - input
		const Vec2<float>& normal,							//Normal vector of reflection on collision time - input
		Vec2<float>& ptEnd,									//Final position of the circle after reflection - output
		Vec2<float>& reflected);							//Normalized reflection vector direction - output


		// Extra credits
	void CollisionResponse_CircleCircle(Vec2<float>& normal,							//Normal vector of reflection on collision time - input
		const float interTime,													//Intersection time - input
		Vec2<float>& velA,															//Velocity of CircleA - input
		const float& massA,														//Mass of CircleA - input
		Vec2<float>& interPtA,														//Intersection position of circle A at collision time - input
		Vec2<float>& velB,															//Velocity of CircleB - input
		const float& massB,														//Mass of CircleB - input
		Vec2<float>& interPtB,														//Intersection position of circle B at collision time - input
		Vec2<float>& reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
		Vec2<float>& ptEndA,															//Final position of the circle A after reflection - output
		Vec2<float>& reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
		Vec2<float>& ptEndB);														//Final position of the circle B after reflection - output


	bool DynamicCollision_RectRect(const AABB& aabb1, const Vec2<float>& vel1,
		const AABB& aabb2, const Vec2<float>& vel2);

	bool StaticCollision_PointRect(const Vec2<float>& point,
		const AABB& aabb2);
}
