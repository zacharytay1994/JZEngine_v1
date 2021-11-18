/*	__FILE HEADER__
*	File:		InstanceSpriteRenderer.cpp
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		ECS system to render instanced sprites.
*/

#include <PCH.h>
#include "InstanceSpriteRenderer.h"
#include "NonInstanceSpriteRenderer.h"
#include "../Renderers/RendererDebug.h"
#include "../Renderers/GlobalRenderer.h"

namespace JZEngine
{
	InstanceSprite::InstanceSprite()
	{
		RegisterComponents<Transform, Texture, InstanceShader>();
	}

	void InstanceSprite::FrameBegin( const float& dt )
	{
		UNREFERENCED_PARAMETER(dt);
		//sprite_renderer_instancing_.DrawInstances();
	}

	void InstanceSprite::Update( const float& dt )
	{
		UNREFERENCED_PARAMETER(dt);
		Transform& transform = GetComponent<Transform>();
		Texture& texture = GetComponent<Texture>();
		InstanceShader& shader = GetComponent<InstanceShader>();

		GlobalRenderer::Instance().renderer_instance_.AddTransform( shader.shader_id_, texture.texture_id_,
															 Math::GetTransform(transform.position_, transform.rotation_, transform.scale_, transform.size_));

		RendererDebug::DrawSpriteSquare(transform.position_, { transform.scale_.x * transform.size_.x, transform.scale_.y * transform.size_.y });
	}
}

