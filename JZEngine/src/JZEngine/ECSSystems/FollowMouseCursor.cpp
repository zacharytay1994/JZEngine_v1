#include <PCH.h>
#include "FollowMouseCursor.h"
#include "../ECS/ECSConfig.h"
#include "../GraphicRendering/Camera.h"

namespace JZEngine
{
	FollowMouseCursorSystem::FollowMouseCursorSystem()
	{
		RegisterComponents<Transform, FollowMouseCursor>();
	}

	void FollowMouseCursorSystem::Update(const float& dt)
	{
		GetComponent<Transform>().position_ = Camera::mouse_world_position_;
	}
}