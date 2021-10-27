/*	__FILE HEADER__
*	File:		NonInstanceSpriteRenderer.h
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		ECS system to render non instanced sprites.
*/

#pragma once

#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "../ECS/ECS.h"
#include "../Math/JZMath.h"
#include "Texture.h"

#include "RendererDebug.h"

namespace JZEngine
{

	// sprite component
	struct Texture
	{
		int texture_id_{ 0 };
	};

	struct Animation2D
	{
		int frame_{ 0 };
		int max_frames_{ 1 };
		int rows_{ 1 };
		int column_{ 1 };
		float animation_speed_{ 1.0f };
		float animation_counter_{ 0.0f };
		bool animation_check_{ false };
	};

	struct NonInstanceShader
	{
		int shader_id_{ 0 };
		Vec3f tint{ 0.0f , 0.0f ,0.0f };
	};

	struct NotBackground
	{
		char flag;
	};

	struct SpriteLayer
	{
		int layer_{ 0 };
	};

	// sprite system
	struct Sprite : public ECS::System
	{
		//SpriteRenderer sprite_renderer_;

		Sprite ()
		{
			RegisterComponents<Transform , Texture , Animation2D , NonInstanceShader, SpriteLayer> ();
		}

		//virtual void FrameEnd(const float& dt) override;

		virtual void Update(const float& dt) override;
		
	};
}