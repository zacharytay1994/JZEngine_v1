#pragma once


#include "../ECS/ECS.h"
#include "TextRenderer.h"

namespace JZEngine
{
	struct TextData
	{
		int font_id_{ 0 };
		int shader_id_{ 0 };
		Vec3f color_{ 0.0f , 0.0f ,0.0f };
		Vec2f position_{ 0.0f,0.0f };
		float scale_{ 1.0f };
	};

	// sprite system
	struct Text : public ECS::System
	{
		TextRenderer* text_renderer_{ nullptr };

		Text ();
		virtual void Update ( const float& dt ) override;
	};

}