#pragma once

#include "../BuildDefinitions.h"
#include "../Math/JZMath.h"

struct GLFWwindow;
namespace JZEngine
{
	struct JZENGINE_API Camera
	{
		static bool fullscreen;
		static float camera_zoom_;
		static Vec2f camera_position_;
		static Vec2f mouse_world_position_;
		static Mat3f camera_transform_;

		static void CalculateMouseWorldPosition(GLFWwindow* window);
	};
}