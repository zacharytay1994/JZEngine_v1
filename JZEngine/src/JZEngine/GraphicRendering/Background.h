#pragma once

#include "../ECS/ECS.h"
#include "SpriteRenderer.h"
#include "../EngineConfig.h"


namespace JZEngine
{
	struct Background
	{
		float speed_x_{ 0.0f };
		float speed_y_{ 0.0f };
	};

	struct BackgroundSystem : public ECS::System
	{
		SpriteRenderer sprite_renderer_;

		BackgroundSystem ();
		virtual void Update ( const float& dt ) override;

	private:
		float win_width_div2 = Settings::window_width / 2.0f;
		float win_height_div2 = Settings::window_height / 2.0f;
	};

}
