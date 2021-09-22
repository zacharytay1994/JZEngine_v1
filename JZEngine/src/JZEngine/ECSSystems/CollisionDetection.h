#pragma once

#include "../ECS/ECS.h"
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
		union
		{
			Circle m_circle; Line m_line;
		};
		Shape() : tag_{ Shape::CIRCLE }, m_circle{} {}
		Shape(const Shape& s) { std::memcpy(this, &s, sizeof(s)); }
		~Shape() {}
	};
	/* ________________________________ COLLISION DETECTION COMPONENTS ___________________________*/

	/* ________________________________ COLLISION DETECTION SYSTEMS __________________*/
	struct CollisionDetection : public JZEngine::ECS::System
	{
		std::vector<Shape*> shapes_;
		unsigned int j{ 0 };

		CollisionDetection()
		{
			RegisterComponents<Shape>();
			shapes_.reserve(100);
		}

		virtual void FrameBegin(const float& dt) override
		{
			j = 0;
		}

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override
		{
			Shape& shape = GetComponent<Shape>();

			bool am_inside{ false };
			for (int i = j; i < shapes_.size(); ++i)
			{
				// to not check with itself
				if (shapes_[i] != &shape)
				{
					switch (shape.tag_)
					{
					case Shape::CIRCLE:
						switch (shapes_[i]->tag_)
						{
						case Shape::CIRCLE:
							// do circle circle code
							Log::Info("Collision", "is circle circle colliding");
							break;
						case Shape::LINE:
							Log::Info("Collision", "is circle line colliding");
							// do circle line
							break;
						}
						break;
					case Shape::LINE:
						switch (shapes_[i]->tag_)
						{
						case Shape::CIRCLE:
							// do line circle
							Log::Info("Collision", "is line circle colliding");
							break;
						case Shape::LINE:
							// do line line
							Log::Info("Collision", "is line line colliding");
							break;
						}
						break;
					}
				}
				else
				{
					am_inside = true;
				}
			}
			if (!am_inside)
			{
				shapes_.push_back(&shape);
			}
			++j;
		}
	};
}