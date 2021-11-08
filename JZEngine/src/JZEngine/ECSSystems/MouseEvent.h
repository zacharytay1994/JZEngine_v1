#pragma once

#include "../ECS/ECS.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	struct MouseEvent
	{
		float bounding_half_width_{ 1.0f };
		float bounding_half_height_{ 1.0f };

		bool on_click_{ false };	// returns if mouse was clicked within the bounding area
		bool on_held_{ false };		// returns if the mouse is still within the bounding area and mouse is down
		bool on_hover_{ false };	// returns if the mouse if within the bounding area
		bool on_drag_{ false };
		//bool on_drop_{ false };
		bool on_released_{ false };
	};

	struct MouseEventSystem : public ECS::System
	{
		bool mouse_pressed_{ false };
		bool mouse_down_{ false };
		bool mouse_released_{ false };

		Vec2f mouse_position_{};

		MouseEventSystem();

		virtual void FrameBegin(const float& dt);
		virtual void Update(const float& dt);
	};
}