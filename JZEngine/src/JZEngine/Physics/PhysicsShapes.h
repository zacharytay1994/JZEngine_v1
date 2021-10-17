/*	__FILE HEADER__
*	File:		PhysicsShapes.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Physics shapes.
*/

#pragma once
#include "../Math/JZMath.h"
#include <array>
namespace JZEngine {

	enum shapetype
	{
		circle = 0,
		aabb = 1,
		square = 2
	
	};

	struct Circle
	{
		Vec2f m_center;
		float m_radius;
		Circle() = default;
		~Circle() = default;
	};


	// a square is a 4 point polygon
	struct Square
	{
		Vec2f midpoint;
		std::array<Vec2f,4> vertices;
		std::array<Vec2f, 4> normal;

		Square() = default;
		Square(Vec2f midpt, Vec2f scale) : midpoint{ midpt }
		{
			//ccw
			vertices[0] = midpt - (scale / 2.0f);//botleft
			vertices[1] = { vertices[0].x + scale.x,vertices[0].y };//bot right
			vertices[2] = vertices[0] + scale;//top right
			vertices[3] = { vertices[2].x - scale.x, vertices[2].y };//top left
		}
		Vec2f& botleft()
		{
			return vertices[0];
		}
		Vec2f& botright()
		{
			return vertices[1];
		}
		Vec2f& topright()
		{
			return vertices[2];
		}
		Vec2f& topleft()
		{
			return vertices[3];
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

	struct AABB
	{
		Vec2f min;
		Vec2f max;
		AABB() = default;
		AABB(Vec2f midpt, Vec2f scale)
		{
			min = midpt - (scale / 2.0f);
			max = midpt + (scale / 2.0f);
		}
	};


}
