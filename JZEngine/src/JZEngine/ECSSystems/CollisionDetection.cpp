#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	Shape::Shape() : tag_{ Shape::CIRCLE }, m_circle{} {}

	//Shape::Shape( ) : tag_{ Shape::CIRCLE }, m_circle{} {}

	Shape::Shape(const Shape& s) { std::memcpy(this, &s, sizeof(s)); }
	Shape::~Shape() {}



	CollisionDetection::CollisionDetection()
	{
		RegisterComponents<Shape, Transform>();
		shapes_.reserve(100);
	}

	void CollisionDetection::FrameBegin(const float& dt) 
	{
		j = 0;

	}

	// updates once per entity component per system per frame
	void CollisionDetection::Update(const float& dt) 
	{
		Shape& currentshape = GetComponent<Shape>();
		Transform& currenttransform = GetComponent<Transform>();




		bool am_inside{ false };
		for (int i = j; i < shapes_.size(); ++i)
		{
			// to not check with itself
			if (shapes_[i] != &currentshape)
			{
				switch (currentshape.tag_)
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
			shapes_.push_back(&currentshape);
		}
		++j;
	}













}//JZEngine