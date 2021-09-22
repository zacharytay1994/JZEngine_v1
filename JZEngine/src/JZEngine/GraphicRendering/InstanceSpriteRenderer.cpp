#include <PCH.h>
#include "InstanceSpriteRenderer.h"
#include "NonInstanceSpriteRenderer.h"

namespace JZEngine
{
	InstanceSprite::InstanceSprite()
	{
		RegisterComponents<Transform, Texture, InstanceShader>();
	}

	void InstanceSprite::FrameBegin( const float& dt )
	{
		sprite_renderer_instancing_.DrawInstances();
	}

	void InstanceSprite::Update( const float& dt )
	{
		Transform& transform = GetComponent<Transform>();
		Texture& texture = GetComponent<Texture>();
		InstanceShader& shader = GetComponent<InstanceShader>();

		sprite_renderer_instancing_.renderer_->AddTransform( shader.shader_id_, texture.texture_id_,
															 Math::GetTransform(transform.position_, transform.rotation_, transform.scale_, transform.size_));
	}
}

