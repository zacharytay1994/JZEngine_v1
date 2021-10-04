#pragma once
#include "../Math/JZMath.h"

namespace JZEngine {

	enum shapetype
	{
		circle = 0,
		aabb = 1,
		square = 2,
	};

	struct Circle
	{
		Vec2f m_center;
		float m_radius;
		float m_mass;//to be used
	};


	// a square is a 4 point polygon
	struct Square
	{
		union {
			struct
			{
				Vec2f botleft;
				Vec2f botright;
				Vec2f topright;
				Vec2f topleft;
				Vec2f midpoint;
			};
			Vec2f vertices[5];
		};

		Square(Vec2f midpt, Vec2f scale) : midpoint{ midpt }
		{
			//vertices_.reserve(4);
			vertices[0] = midpt - (scale / 2.0f);//botleft
			vertices[1] = { vertices[0].x + scale.x,vertices[0].y };//bot right
			vertices[2] = vertices[0] + scale;//top right
			vertices[3] = { vertices[2].x - scale.x, vertices[2].y };//top left
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
