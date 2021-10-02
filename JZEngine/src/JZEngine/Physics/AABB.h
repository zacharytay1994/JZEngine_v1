#pragma once
#include "../Math/JZMath.h"


namespace JZEngine
{
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
