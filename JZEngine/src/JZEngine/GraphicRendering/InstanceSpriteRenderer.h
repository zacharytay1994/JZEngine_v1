/*	__FILE HEADER__
*	File:		InstanceSpriteRenderer.h
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		ECS system to render instanced sprites.
*/

#pragma once

#include "../ECS/ECS.h"

namespace JZEngine
{
	struct InstanceShader
	{
		int shader_id_{ 0 };
	};

	// sprite system
	struct InstanceSprite : public ECS::System
	{
		//SpriteRendererInstancing sprite_renderer_instancing_;

		InstanceSprite();

		virtual void FrameBegin( const float& dt ) override;

		virtual void Update( const float& dt ) override;
	};
}
