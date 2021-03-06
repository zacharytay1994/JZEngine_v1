/*	__FILE HEADER__
*	File:		Text.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		ECS Text Renderer
*/

#pragma once

#include "../../ECS/ECS.h"
#include "../Renderers/RendererText.h"
#include "../../STL/String.h"


namespace JZEngine
{
	struct TextData
	{
		int font_id_{ 0 };
		int shader_id_{ 0 };

		Vec3f color_{ 0.0f , 0.0f ,0.0f };
		Vec2f position_{ 0.0f,0.0f };
		float font_size_{ 1.0f };
		JZEngine::String text{};
		float tracking_x_{1.0f};
		float leading_y_{2.0f};
	};

	// sprite system
	struct Text : public ECS::System
	{
		Text ();
		virtual void Update ( const float& dt ) override;
	};

}