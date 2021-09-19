#pragma once

#include "SpriteRenderer.h"

#include "../ECS/ECS.h"
#include "../Math/JZMath.h"
#include "Texture.h"

namespace JZEngine
{
	// transform component
	struct Transform
	{
		Vec2f position_{ 0.0f, 0.0f };
		float rotation_{ 0.0f };
		Vec2f size_{ 50.0f, 50.0f };
		Vec2f scale_{ 1.0f,1.0f };
	};

	// sprite component
	struct Texture
	{
		int texture_id_{ 0 };
		int shader_id_{ 0 };
	};

	// sprite system
	struct Sprite : public ECS::System
	{
		SpriteRenderer sprite_renderer_;

		Sprite()
		{
			RegisterComponents<Transform, Texture>();
		}

		virtual void Update(const float& dt) override
		{
			Transform& transform = GetComponent<Transform>();
			Texture& texture = GetComponent<Texture>();
			sprite_renderer_.DrawSprite(texture.shader_id_, texture.texture_id_, 
				transform.position_, transform.size_, transform.scale_, transform.rotation_, { 1.0f,1.0f,1.0f });
		}
	};
}