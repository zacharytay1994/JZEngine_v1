#pragma once

#include "../Math/JZMath.h"
namespace JZEngine
{
	
	class Rect {
	public:
		Rect() = default;

		Rect(const Vec2f& pos, const Vec2f& size)
			:
			rectCenter(pos),
			width(size.x),
			height(size.y)
		{}

		Rect(const Vec2f& rectcenter, const float& width, const float& height)
			:
			rectCenter(rectcenter),
			width(width),
			height(height)
		{}
		Rect(const Vec2f& topleft, const Vec2f& topright, const Vec2f& bottomleft, const Vec2f& bottomright)
			:
			Rect(Vec2f(topleft.x + (topright.x - topleft.x) / 2, topleft.y + (bottomleft.y - topleft.y) / 2), topright.x - topleft.x, bottomleft.y - topleft.y)
		{
			UNREFERENCED_PARAMETER(bottomright);
		}
		Rect(const Rect& rect)
			:
			Rect(rect.rectCenter, rect.width, rect.height)
		{}
		bool IsOverlap(const Vec2f& position) {
			return position.x < rightBound&&
				position.x > leftBound &&
				position.y < upperBound&&
				position.y > lowerBound;
		}
		// checks to see if rect is overlapping another rect
		bool IsOverlapRect(const Rect& rectIn) {
			return !(rightBound < rectIn.leftBound ||
				leftBound > rectIn.rightBound ||
				upperBound < rectIn.lowerBound ||
				lowerBound > rectIn.upperBound);
		}
	public:
		Vec2f rectCenter;
		float width;
		float height;
		// aabb of rectangle
		float leftBound = rectCenter.x - width / 2.0f;
		float rightBound = rectCenter.x + width / 2.0f;
		float upperBound = rectCenter.y + height / 2.0f;
		float lowerBound = rectCenter.y - height / 2.0f;
	};
}
