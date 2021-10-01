#pragma once

//#include "../ECSSystems/PhysicsSystem.h"
#include "../Math/JZMath.h"

#include <vector>

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
			max = midpt + (scale / 2.0f);//to change
		}
	};

	struct Square
	{
		struct {
			Vec2f topleft;
			Vec2f topright;
			Vec2f botleft;
			Vec2f botright;
			Vec2f midpoint;
		};
		//std::vector<Vec2f> vertices_;

		Square(Vec2f midpt, Vec2f scale) : midpoint{ midpt }
		{
			//vertices_.reserve(4);
			botleft = midpt - (scale / 2.0f);
			botright = { botleft.x + scale.x, botleft.y };
			topright = botleft + scale ;
			topleft = { topright.x - scale.x, topright.y };
		}
	};
	struct LineSegment
	{
		Vec2f m_pt0;
		Vec2f m_pt1;
		Vec2f m_normal;

		LineSegment() : m_pt0{ }, m_pt1{}, m_normal{}	{}
		LineSegment(Vec2f pt0, Vec2f pt1) : m_pt0{ pt0 }, m_pt1{ pt1 }
		{
			m_normal.x = m_pt1.y - m_pt0.y;
			m_normal.y = -(m_pt1.x - m_pt0.x);
			m_normal.Normalize();
		}
		LineSegment(const LineSegment& k) : m_pt0{ k.m_pt0 }, m_pt1{ k.m_pt1 }, m_normal{ k.m_normal }
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


	namespace Collision
	{
		bool IntersectCirclePolygon(const Circle& circle, const Square& squareA,
			Vec2f& normal, float& depth);

		int FindClosestPointOnPolygon(const Vec2f& point, std::vector<Vec2f>& vertices);

		void ProjectCircle(const Circle& circle, const Vec2f& axis, float& min, float& max);

		bool IntersectPolygons(const Square& squareA, const Square& squareB, Vec2f& normal, float depth);

		void ProjectVertices(const std::vector<Vec2f>& vertices, const Vec2f& axis, float& min, float& max);


		bool DynamicCollision_CircleSquare(const Circle& circle,			//Circle data - input
			const Vec2f& ptEnd,											//End circle position - input
			const Square& m_square,												//square data - input
			Vec2f& interPt,												//Intersection point - output
			Vec2f& normalAtCollision,									//Normal vector at collision time - output
			float& interTime,
			bool checkLineEdges);										//Intersection time ti - output

		// INTERSECTION FUNCTIONS
		bool DynamicCollision_CircleLineSegment(const Circle& circle,			//Circle data - input
			const Vec2f& ptEnd,											//End circle position - input
			const LineSegment& lineSeg,												//Line segment - input
			Vec2f& interPt,												//Intersection point - output
			Vec2f& normalAtCollision,									//Normal vector at collision time - output
			float& interTime,
			bool checkLineEdges);										//Intersection time ti - output


		// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
		// In the case of "dynamic circle vs static pillar", velB will be 0.0f
		bool DynamicCollision_CircleCircle(const Circle& circleA,				//CircleA data - input
			const Vec2f& velA,														//CircleA velocity - input
			const Circle& circleB,													//CircleB data - input
			const Vec2f& velB,														//CircleA velocity - input
			Vec2f& interPtA,														//Intersection point of CircleA at collision time - output
			Vec2f& interPtB,														//Intersection point of CircleB at collision time - output
			float& interTime														//intersection time - output
		);														


		// RESPONSE FUNCTIONS In this case the object bounces off the line
		void CollisionResponse_CircleLineSegment(const Vec2f& ptInter,							//Intersection position of the circle - input
			const Vec2f& normal,							//Normal vector of reflection on collision time - input
			Vec2f& ptEnd,									//Final position of the circle after reflection - output
			Vec2f& reflected);							//Normalized reflection vector direction - output



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

		bool CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
			const Circle& circle,													//Circle data - input
			const Vec2f& ptEnd,													//End circle position - input
			const LineSegment& lineSeg,												//Line segment - input
			Vec2f& interPt,														//Intersection point - output
			Vec2f& normalAtCollision,												//Normal vector at collision time - output
			float& interTime);




	}//Collision
}//JZEngine
