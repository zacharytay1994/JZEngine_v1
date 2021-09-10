#include "PCH.h"
#include "Collision.h"


namespace JZEngine
{
	//Dynamic AABB collision
    bool DynamicCollision_RectRect(const AABB& aabb1, const JZEngine::Vec2<float>& vel1,
        const AABB& aabb2, const JZEngine::Vec2<float>& vel2)
    {
        if ((aabb1.max.x < aabb2.min.x) || (aabb1.max.y < aabb2.min.y) || (aabb1.min.x > aabb2.max.x) || (aabb1.min.y > aabb2.max.y))
        {
            ////Step 2: Initialize and calculate the new velocity of Vb
            float tFirst = 0.0f;
            float tLast = 0; // g_dt;
            Vec2<float> RelativeVb;
            RelativeVb = vel2 - vel1;
            if (!RelativeVb.x)
                if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x)
                    return 0;
            if (!RelativeVb.y)
                if (aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y)
                    return 0;
            if (RelativeVb.x)
            {
                if (RelativeVb.x < 0)
                {
                    //case 1
                    if (aabb1.min.x > aabb2.max.x)
                    {
                        return 0;
                    }
                    //case 4
                    if (aabb1.max.x < aabb2.min.x)
                    {
                        tFirst = std::max((aabb1.max.x - aabb2.min.x) / RelativeVb.x, tFirst);
                    }
                    if (aabb1.min.x < aabb2.max.x)
                    {
                        tLast = std::max((aabb1.min.x - aabb2.max.x) / RelativeVb.x, tLast);
                    }
                }
                else if (RelativeVb.x > 0)
                {
                    //case 3
                    if (aabb1.max.x < aabb2.min.x)
                    {
                        return 0;
                    }
                    //case 2
                    if (aabb1.max.x > aabb2.min.x)
                    {
                        tFirst = std::max((aabb1.min.x - aabb2.max.x) / RelativeVb.x, tFirst);
                    }
                    if (aabb1.min.x > aabb2.max.x)
                    {
                        tLast = std::max((aabb1.max.x - aabb2.min.x) / RelativeVb.x, tLast);
                    }
                }
                if (tFirst > tLast)
                {
                    return 0;
                }
            }
            if (RelativeVb.y)
            {
                if (RelativeVb.y < 0)
                {
                    //case 1
                    if (aabb1.min.y > aabb2.max.y)
                    {
                        return 0;
                    }
                    //case 4
                    if (aabb1.max.y < aabb2.min.y)
                    {
                        tFirst = std::max((aabb1.max.y - aabb2.min.y) / RelativeVb.y, tFirst);
                    }
                    if (aabb1.min.y < aabb2.max.y)
                    {
                        tLast = std::max((aabb1.min.y - aabb2.max.y) / RelativeVb.y, tLast);
                    }
                }
                else if (RelativeVb.y > 0)
                {
                    //case 3
                    if (aabb1.max.y < aabb2.min.y)
                    {
                        return 0;
                    }
                    //case 2
                    if (aabb1.min.y > aabb2.max.y)
                    {
                        tFirst = std::max((aabb1.min.y - aabb2.max.y) / RelativeVb.y, tFirst);
                    }
                    if (aabb1.max.y > aabb2.min.y)
                    {
                        tLast = std::max((aabb1.max.y - aabb2.min.y) / RelativeVb.y, tLast);
                    }
                }
                //case 5
                if (tFirst > tLast)
                {
                    return 0;
                }
            }
            return 0;
        }
        else
        {
            return 1; //rectangles intersect
        }
    }

	//Static AABB Collision
    bool StaticCollision_PointRect(const Vec2<float>& point,
        const AABB& aabb2)
    {
        if (point.x < aabb2.max.x && point.x > aabb2.min.x && point.y < aabb2.max.y && point.y > aabb2.min.y)
            return 1;
        else return 0;
    }




	/******************************************************************************/
	/*
	 * \brief				Function to build a line segment with pt0, pt1 and normal
	 * \param lineSegment	The object to modify
	 * \param pos			The middle of The line segment
	 * \param scale			The length of The line
	 * \param dir			The angle of The line segment in radians
	 */
	 /******************************************************************************/
	void BuildLineSegment(LineSegment& lineSegment,
		const Vec2<float>& pos,
		float scale,
		float dir)
	{
		lineSegment.m_pt1.x = pos.x + scale / 2.0f * cosf(dir);
		lineSegment.m_pt1.y = pos.y + scale / 2.0f * sinf(dir);
		lineSegment.m_pt0.x = pos.x + scale / 2.0f * cosf(dir + PI);
		lineSegment.m_pt0.y = pos.y + scale / 2.0f * sinf(dir + PI);

		lineSegment.m_normal.x = lineSegment.m_pt1.y - lineSegment.m_pt0.y;
		lineSegment.m_normal.y = -(lineSegment.m_pt1.x - lineSegment.m_pt0.x);
		lineSegment.m_normal.Normalize();
	}


	/******************************************************************************/
	/*!
	 * \brief			Function to check dynamic circle vs static line collision
	 * \param circle	The circle object which contains The middle pt of The circle n radius
	 * \param circleend	The end position of The circle, Be
	 * \param lineSeg	The object line segment which contains p0 p1 n The normal
	 * \param interPt	The intersection point, Bi
	 * \param normalAtCollision		The normal at collision
	 * \param interTime		The time of intersection, Ti
	 * \return 0 or 1		Returns 1 if collison detected, else 0
	 */
	 /******************************************************************************/
	int CollisionIntersection_CircleLineSegment(const Circle& circle,			//Circle data - input
		const Vec2<float>& circleend,											//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		Vec2<float>& interPt,												//Intersection point - output
		Vec2<float>& normalAtCollision,									//Normal vector at collision time - output
		float& interTime,														//Intersection time ti - output
		bool& checkLineEdges)
	{
		// outward normal M to circle velocity
		Vec2<float> V(circleend.x - circle.m_center.x, circleend.y - circle.m_center.y);
		Vec2<float> M(circleend.y - circle.m_center.y, -(circleend.x - circle.m_center.x));
		float nbsnp0 = lineSeg.m_normal.Dot( circle.m_center) -
			lineSeg.m_normal.Dot( lineSeg.m_pt0);
		if (nbsnp0 < -circle.m_radius)
		{
			Vec2<float> p0prime = lineSeg.m_pt0 - circle.m_radius * lineSeg.m_normal;
			Vec2<float> p1prime = lineSeg.m_pt1 - circle.m_radius * lineSeg.m_normal;

			if (M.Dot(p0prime - circle.m_center) * M.Dot( p1prime - circle.m_center) < 0)
			{
				interTime = ( lineSeg.m_normal.Dot( lineSeg.m_pt0) - lineSeg.m_normal.Dot( circle.m_center) - circle.m_radius  )
					/ lineSeg.m_normal.Dot( V);
				if (0 <= interTime && interTime <= 1)
				{
					interPt = circle.m_center + V * interTime;
					normalAtCollision = -lineSeg.m_normal;
					return 1;
				}
				else
					return 0;
			}
			else
			{
				// checkmovingcircletolineedge (next part)
				return 0;
			}
		}
		else if (nbsnp0 > circle.m_radius)
		{
			Vec2<float> p0prime = lineSeg.m_pt0 + circle.m_radius * lineSeg.m_normal;
			Vec2<float> p1prime = lineSeg.m_pt1 + circle.m_radius * lineSeg.m_normal;

			if ((M.Dot( p0prime - circle.m_center) * M.Dot( p1prime - circle.m_center)) < 0)
			{
				interTime = (lineSeg.m_normal.Dot( lineSeg.m_pt0) - lineSeg.m_normal.Dot( circle.m_center) + circle.m_radius)
					/ lineSeg.m_normal.Dot( V);
				if (0 <= interTime && interTime <= 1)
				{
					interPt = circle.m_center + V * interTime;
					normalAtCollision = lineSeg.m_normal;
					return 1;
				}
				else
					return 0;
			}
			else
			{
				// checkmovingcircletolineedge (next part)
				return 0;
			}
		}
		else
		{
			return 0; // checkmovingcircletolineedge (next part)
		}
	}

	/******************************************************************************/
	/**
	 * @brief Collision checker for 2 dynamic circles
	 *
	 * @param circleA First circle object
	 * @param velA 		Velocity if first circle
	 * @param circleB Second circle object
	 * @param velB 		Velocity of second circle
	 * @param interPtA Intersection point of first circle
	 * @param interPtB Intersection point of second circle
	 * @param interTime Intersection time
	 * @return int
	 */
	 /******************************************************************************/
	int CollisionIntersection_CircleCircle(const Circle& circleA,
		const Vec2<float>& velA,
		const Circle& circleB,
		const Vec2<float>& velB,
		Vec2<float>& interPtA,
		Vec2<float>& interPtB,
		float& interTime)
	{
		Vec2<float> RV, nRV;
		RV = velA - velB;
		float RVlength =RV.Len();
		nRV = RV.GetNormalized();
		
		float m = nRV.Dot(circleB.m_center - circleA.m_center);
		//first rejection test
		if (m < 0)
			return 0;
		float n2 = (circleB.m_center - circleA.m_center).LenSq() - (m * m);
		float r = circleA.m_radius + circleB.m_radius;
		//second rejection test
		if (n2 > r * r)
			return 0;

		float s2 = r * r - n2;
		interTime = (m - sqrt(s2)) / RVlength;
		if (interTime > 0.0f && interTime < 1.0f)
		{
			interPtA = circleA.m_center + velA * interTime;
			interPtB = circleB.m_center + velB * interTime;
			return 1;
		}
		else
			return 0;
	}



	/******************************************************************************/
	/*!
	 * \brief			The function which handles The response to collision
	 * \param ptInter	The point of intersection,Bi
	 * \param normal	The normal at intersection
	 * \param ptEnd		The end of The circle applying reflection
	 * \param reflected	The reflection vector(normalized)
	 */
	 /******************************************************************************/
	void CollisionResponse_CircleLineSegment(const Vec2<float>& ptInter,
		const Vec2<float>& normal,
		Vec2<float>& ptEnd,
		Vec2<float>& reflected)
	{
		reflected = (ptEnd - ptInter) - (2.0f * normal.Dot(ptEnd - ptInter) * normal);
		ptEnd = ptInter + reflected;
		reflected.Normalize ();
	}



	/******************************************************************************/
	/*!
	 * \brief	The function reuses the collision response from circlelinesegment
	 */
	 /******************************************************************************/
	void CollisionResponse_CirclePillar(const Vec2<float>& normal,
		const float& interTime,
		const Vec2<float>& ptStart,
		const Vec2<float>& ptInter,
		Vec2<float>& ptEnd,
		Vec2<float>& reflectedVectorNormalized)
	{
		CollisionResponse_CircleLineSegment(ptInter, normal, ptEnd, reflectedVectorNormalized);
	}

	/**
	 * \brief This function handles the collision response for circle with circle objects
	 * \param normal
	 * \param interTime
	 * \param velA
	 * \param massA
	 * \param interPtA
	 * \param velB
	 * \param massB
	 * \param interPtB
	 * \param reflectedVectorA
	 * \param ptEndA
	 * \param reflectedVectorB
	 * \param ptEndB
	 */
	void CollisionResponse_CircleCircle(Vec2<float>& normal,
		const float interTime,
		Vec2<float>& velA,
		const float& massA,
		Vec2<float>& interPtA,
		Vec2<float>& velB,
		const float& massB,
		Vec2<float>& interPtB,
		Vec2<float>& reflectedVectorA,
		Vec2<float>& ptEndA,
		Vec2<float>& reflectedVectorB,
		Vec2<float>& ptEndB)
	{
		Vec2<float> nnormal;
		Vec2<float> nreflectedVectorA, nreflectedVectorB;
		//Vector2DNormalize(nnormal, normal);
		float aA = velA.Dot(normal);
		float aB = velB.Dot(normal);
		reflectedVectorA = velA - normal*((2 * (aA - aB)) / (massA + massB)) * massB ;
		reflectedVectorB = velB + normal*((2 * (aA - aB)) / (massA + massB)) * massA ;
		nreflectedVectorA = reflectedVectorA.GetNormalized();
		nreflectedVectorB = reflectedVectorB.GetNormalized();

		ptEndA = interPtA + nreflectedVectorA * (1.0f - interTime);
		ptEndB = interPtB + nreflectedVectorB * (1.0f - interTime);
	}



} //JZEngine namespace