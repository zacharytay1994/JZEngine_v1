#pragma once
#include "../Math/JZMath.h"
namespace JZEngine
{
	struct Transform
	{
		Vec2f position_{ 0.0f, 0.0f };
		float rotation_{ 0.0f };
		Vec2f size_{ 50.0f, 50.0f };//physics system uses the size_
		Vec2f scale_{ 1.0f,1.0f };
		Mat3f model_transform_;
	};
}