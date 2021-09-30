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
		Vec2f size_{ 50.0f, 50.0f };//physics system uses the size_
		Vec2f scale_{ 1.0f,1.0f };
		Mat3f model_transform_;
	};

	// sprite component
	struct Texture
	{
		int texture_id_{ 0 };
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

	// sprite system
	struct Sprite : public ECS::System
	{
		SpriteRenderer sprite_renderer_;

		Sprite ()
		{
			RegisterComponents<Transform , Texture , NonInstanceShader , NotBackground> ();
		}

		virtual void FrameBegin ( const float& dt ) override
		{
			//sprite_renderer_.ClearPackets();
		}

		/*virtual void FrameStart(const float& dt)
		{
			sprite_renderer_.DrawAllInstances();
		}*/

		virtual void Update ( const float& dt ) override
		{
			Transform& transform = GetComponent<Transform> ();
			Texture& texture = GetComponent<Texture> ();
			NonInstanceShader& shader = GetComponent<NonInstanceShader> ();

			transform.model_transform_ = Math::GetModelTransformNonTransposed(transform.position_, transform.rotation_, transform.scale_, transform.size_);
			// else use default render
			// sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ ,
			// 							  transform.position_ , transform.size_ , transform.scale_ , transform.rotation_ , { 1.0f,1.0f,1.0f }, shader.tint);
			sprite_renderer_.DrawSprite( shader.shader_id_, texture.texture_id_, (Math::GetProjectionTransformNonTransposed() * transform.model_transform_).Transpose(),shader.tint);
		}
	};
}