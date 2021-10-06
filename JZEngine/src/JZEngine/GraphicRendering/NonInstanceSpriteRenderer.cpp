#include <PCH.h>
#include "NonInstanceSpriteRenderer.h"
#include "../EngineGUI/EngineGUI.h"

namespace JZEngine
{
	void Sprite::Update(const float& dt)
	{
		Transform& transform = GetComponent<Transform>();
		Texture& texture = GetComponent<Texture>();
		NonInstanceShader& shader = GetComponent<NonInstanceShader>();

		transform.model_transform_ = Math::GetModelTransformNonTransposed(transform.position_, transform.rotation_, transform.scale_, transform.size_);
		// else use default render
		// sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ ,
		// 							  transform.position_ , transform.size_ , transform.scale_ , transform.rotation_ , { 1.0f,1.0f,1.0f }, shader.tint);
		sprite_renderer_.DrawSprite(shader.shader_id_, texture.texture_id_, (Math::GetProjectionTransformNonTransposed() * EngineGUI::GetCameraTransform() * transform.model_transform_).Transpose(), shader.tint);

		RendererDebug::DrawSpriteSquare(transform.position_, { transform.scale_.x * transform.size_.x, transform.scale_.y * transform.size_.y });
	}
}