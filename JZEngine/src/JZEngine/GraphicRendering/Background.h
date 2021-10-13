/*	__FILE HEADER__
*	File:		Background.h
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		Parallax background system.
*/

#pragma once

#include "SpriteRenderer.h"
#include "../EngineConfig.h"
#include "../ECS/ECS.h"


namespace JZEngine
{
	struct Parallax
	{
		float speed_x_{ 0.0f };
		float speed_y_{ 0.0f };
		bool is_vertical{ false };
	};

	struct ParallaxBackground : public ECS::System
	{
		//SpriteRenderer sprite_renderer_;

		ParallaxBackground ();
		virtual void Update ( const float& dt ) override;

	private:
		float win_width_div2 = Settings::window_width / 2.0f;
		float win_height_div2 = Settings::window_height / 2.0f;
	};

}
