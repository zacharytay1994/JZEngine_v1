#pragma once


#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"
#include <vector>

namespace JZEngine
{
	class Collision
	{


	public:
		static bool CheckPhysicsComponentCollision(PhysicsComponent& componentA, PhysicsComponent& componentB, Vec2f& normal, float& depth);
		static void ResolvePhysicsComponentCollision(PhysicsComponent& componentA, PhysicsComponent& componentB, const Vec2f& normal, const float& depth);
	private:
		
		static bool IntersectCircles(const Circle& circleA, const Circle& circleB, Vec2f& normal, float& depth);

		static bool IntersectCirclePolygon(const Circle& circle, const Square& squareA,
			Vec2f& normal, float& depth);

		static int FindClosestPointOnPolygon(const Vec2f& point, std::vector<Vec2f>& vertices);

		static void ProjectCircle(const Circle& circle, const Vec2f& axis, float& min, float& max);

		static bool IntersectPolygons(const Square& squareA, const Square& squareB, Vec2f& normal, float depth);

		static void ProjectVertices(const std::vector<Vec2f>& vertices, const Vec2f& axis, float& min, float& max);


		static bool DynamicCollision_CircleSquare(const Circle& circle,			//Circle data - input
			const Vec2f& ptEnd,											//End circle position - input
			const Square& m_square,												//square data - input
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


		static bool DynamicCollision_RectRect(const AABB& aabb1, const Vec2f& vel1,
			const AABB& aabb2, const Vec2f& vel2);

		static bool StaticCollision_PointRect(const Vec2f& point,
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
