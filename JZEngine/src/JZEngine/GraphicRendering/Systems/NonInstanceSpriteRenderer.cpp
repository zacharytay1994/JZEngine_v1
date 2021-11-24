/*	__FILE HEADER__
*	File:		NonInstanceSpriteRenderer.cpp
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		ECS system to render non instanced sprites.
*/

#include <PCH.h>
#include "NonInstanceSpriteRenderer.h"
#include "../../EngineGUI/EngineGUI.h"
#include "../Renderers/RenderQueue.h"
#include "../Renderers/GlobalRenderer.h"

namespace JZEngine
{
	void Sprite::Update(const float& dt)
	{
		Transform& transform = GetComponent<Transform>();
		Texture& texture = GetComponent<Texture>();
		NonInstanceShader& shader = GetComponent<NonInstanceShader>();
		Animation2D& anim2d = GetComponent<Animation2D>();

		// update animation
		if (anim2d.animation_counter_ < anim2d.animation_speed_)
		{
			anim2d.animation_counter_ += dt;
		}
		else
		{
			++anim2d.frame_;
			if (anim2d.frame_ >= anim2d.max_frames_)
			{
				anim2d.frame_ = 0;
			}
			anim2d.animation_counter_ = 0.0f;
		}

		transform.model_transform_ = Math::GetModelTransformNonTransposed(transform.position_, transform.rotation_, transform.scale_, transform.size_);

		SpriteLayer& layer = GetComponent<SpriteLayer>();
		GlobalRenderer::Instance().render_queue_.DrawQueue(layer.layer_, shader.shader_id_, texture.texture_id_, (Math::GetProjectionTransformNonTransposed() * EngineGUI::GetCameraTransform() * transform.model_transform_).Transpose(), shader.tint, anim2d.frame_, anim2d.rows_, anim2d.column_, anim2d.animation_check_);
		GlobalRenderer::Instance().render_queue_.GUILayerData(&layer.layer_, texture.texture_id_);

		RendererDebug::DrawSpriteSquare(transform.position_, { transform.scale_.x * transform.size_.x, transform.scale_.y * transform.size_.y });
	}
}