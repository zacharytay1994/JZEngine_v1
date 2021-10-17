/*	__FILE HEADER__
*	File:		Collision.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Collision Detection
*/

#pragma once

#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"



namespace JZEngine
{
	struct Manifold
	{
		float depth;
		Vec2f normal;
		Vec2f contacts[2];
		int contact_count;
		Manifold()
			: depth{ 0 }, normal{ 0.f,0.f }, contact_count{ 0 }
		{
			for (auto i : contacts)
				i = { 0.0f,0.0f };
		}
	};

	class Collision
	{
	public:
		static bool CheckPhysicsCollision(const PhysicsComponent& componentA, const PhysicsComponent& componentB, Manifold& colldata);

		static void ResolvePhysicsCollision(PhysicsComponent& componentA, PhysicsComponent& componentB, const Vec2f& normal, const float& depth);
		
	private:
		
		static bool IntersectCircles(const Circle& circleA, const Circle& circleB, Manifold& colldata);

		static bool IntersectCirclePolygon(const Circle& circle, const Square& squareA,
			Manifold& colldata);

		static int FindClosestPointOnPolygon(const Vec2f& point, const std::array<Vec2f, 4>& vertices);

		static void ProjectCircle(const Circle& circle, const Vec2f& axis, float& min, float& max);

		static bool IntersectPolygons(const Square& squareA, const Square& squareB, Manifold& colldata);

		//For now only takes in polygons with 4 vertices
		static void ProjectVertices(const std::array<Vec2f, 4>& vertices, const Vec2f& axis, float& min, float& max);


		static bool DynamicCollision_CircleAABB(const Circle& circle,			//Circle data - input
			const Vec2f& ptEnd,											//End circle position - input
			const AABB& m_square,												//square data - input
			Vec2f& interPt,												//Intersection point - output
			Vec2f& normalAtCollision,									//Normal vector at collision time - output
			float& interTime,
			bool checkLineEdges);										//Intersection time ti - output

		// INTERSECTION FUNCTIONS
		static bool DynamicCollision_CircleLineSegment(const Circle& circle,			//Circle data - input
			const Vec2f& ptEnd,											//End circle position - input
			const LineSegment& lineSeg,												//Line segment - input
			Vec2f& interPt,												//Intersection point - output
			Vec2f& normalAtCollision,									//Normal vector at collision time - output
			float& interTime,
			bool checkLineEdges);										//Intersection time ti - output


		// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
		// In the case of "dynamic circle vs static pillar", velB will be 0.0f
		static bool DynamicCollision_CircleCircle(const Circle& circleA,				//CircleA data - input
			const Vec2f& velA,														//CircleA velocity - input
			const Circle& circleB,													//CircleB data - input
			const Vec2f& velB,														//CircleA velocity - input
			Vec2f& interPtA,														//Intersection point of CircleA at collision time - output
			Vec2f& interPtB,														//Intersection point of CircleB at collision time - output
			float& interTime														//intersection time - output
		);


		// RESPONSE FUNCTIONS In this case the object bounces off the line
		static void CollisionResponse_CircleLineSegment(const Vec2f& ptInter,							//Intersection position of the circle - input
			const Vec2f& normal,							//Normal vector of reflection on collision time - input
			Vec2f& ptEnd,									//Final position of the circle after reflection - output
			Vec2f& reflected);							//Normalized reflection vector direction - output



		static void CollisionResponse_CircleCircle(Vec2f& normal,							//Normal vector of reflection on collision time - input
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


		static bool DynamicCollision_AABB(const AABB& aabb1, const Vec2f& vel1,
			const AABB& aabb2, const Vec2f& vel2);

		static bool StaticCollision_PointAABB(const Vec2f& point,
			const AABB& aabb2);

		static bool CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
			const Circle& circle,													//Circle data - input
			const Vec2f& ptEnd,													//End circle position - input
			const LineSegment& lineSeg,												//Line segment - input
			Vec2f& interPt,														//Intersection point - output
			Vec2f& normalAtCollision,												//Normal vector at collision time - output
			float& interTime);




	}; //Collision
}//JZEngine
