#pragma once

#include "../ECS/ECS.h"
#include "SpriteRendererInstancing.h"

namespace JZEngine
{
	struct InstanceShader
	{
		int shader_id_{ 0 };
	};

	// sprite system
	struct InstanceSprite : public ECS::System
	{
		SpriteRendererInstancing sprite_renderer_instancing_;

		InstanceSprite();

		virtual void FrameBegin( const float& dt ) override;

		virtual void Update( const float& dt ) override;
	};
}
