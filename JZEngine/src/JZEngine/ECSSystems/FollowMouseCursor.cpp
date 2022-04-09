#include <PCH.h>
#include "FollowMouseCursor.h"
#include "../ECS/ECSConfig.h"
#include "../GraphicRendering/Camera.h"
#include "../EngineConfig.h"
#include <algorithm>

namespace JZEngine
{
	FollowMouseCursorSystem::FollowMouseCursorSystem ()
	{
		RegisterComponents<Transform , FollowMouseCursor> ();
	}

	void FollowMouseCursorSystem::Update ( const float& dt )
	{
		UNREFERENCED_PARAMETER ( dt );
		//GetComponent<Transform> ().position_ = Camera::mouse_world_position_;

		float window_half_width = Settings::camera_width / 2.0f;
		float window_half_height = Settings::camera_height / 2.0f;

		GetComponent<Transform> ().position_.x = std::clamp ( Camera::mouse_world_position_.x , -window_half_width , window_half_width );

		GetComponent<Transform> ().position_.y = std::clamp ( Camera::mouse_world_position_.y , -window_half_height , window_half_height );
	}
}