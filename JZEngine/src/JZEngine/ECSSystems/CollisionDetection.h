#pragma once


#include "../Math/JZMath.h"
#include "../DebugTools/Log.h"


namespace JZEngine
{
	/* ________________________________ COLLISION DETECTION COMPONENTS ___________________________*/
	struct Circle
	{
		Vec2f m_center;
		float m_radius;
		float m_mass;
	};

	struct Line
	{
		Vec2f m_pt0;
		Vec2f m_pt1;
		Vec2f m_normal;
	};

	struct Shape
	{
		enum {CIRCLE, LINE} tag_;
		Circle m_circle; 
		Line m_line;

		//union {
		//	Circle m_circle;
		//	Line m_line;
		//};

		Shape();
		Shape(const Shape& s);
		~Shape();
	};


	/* ________________________________ COLLISION DETECTION COMPONENTS ___________________________*/

	/* ________________________________ COLLISION DETECTION SYSTEMS __________________*/
	struct CollisionDetection : public JZEngine::ECS::System
	{
		std::vector<Shape*> shapes_;
		//std::vector<Line*> shapes_;

		unsigned int j{ 0 };

		CollisionDetection();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;
	};
}