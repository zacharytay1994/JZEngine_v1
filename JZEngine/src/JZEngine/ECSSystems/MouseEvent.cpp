#include <PCH.h>
#include "../ECS/ECSConfig.h"
#include "MouseEvent.h"
#include "../Input/Input.h"
#include "../GraphicRendering/Camera.h"
#include "../GraphicRendering/RendererDebug.h"

namespace JZEngine
{
	MouseEventSystem::MouseEventSystem()
	{
		RegisterComponents<Transform, MouseEvent>();
	}

	void MouseEventSystem::FrameBegin(const float& dt)
	{
		mouse_pressed_ = InputHandler::IsMouseTriggered(MOUSE::MOUSE_BUTTON_1);
		mouse_down_ = InputHandler::IsMousePressed(MOUSE::MOUSE_BUTTON_1);
		mouse_released_ = InputHandler::IsMouseReleased(MOUSE::MOUSE_BUTTON_1);

		mouse_position_ = Camera::mouse_world_position_;
	}

	void MouseEventSystem::Update(const float& dt)
	{
		Transform& transform = GetComponent<Transform>();
		MouseEvent& me = GetComponent<MouseEvent>();
		// check if mouse is over component
		me.on_hover_ = !((mouse_position_.x < transform.position_.x - me.bounding_half_width_)	||
						(mouse_position_.x > transform.position_.x + me.bounding_half_width_)	||
						(mouse_position_.y < transform.position_.y - me.bounding_half_height_)	||
						(mouse_position_.y > transform.position_.y + me.bounding_half_height_));

		me.on_click_ = mouse_pressed_ && me.on_hover_;

		me.on_held_ = mouse_down_ && me.on_hover_;

		me.on_released_ = mouse_released_ && me.on_hover_;

		RendererDebug::DrawSquare(transform.position_, Vec2f(me.bounding_half_width_*2.0f, me.bounding_half_height_*2.0f));
	}
}