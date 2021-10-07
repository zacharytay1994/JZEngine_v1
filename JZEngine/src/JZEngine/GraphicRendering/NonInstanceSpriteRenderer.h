#pragma once

#include "SpriteRenderer.h"

#include "../ECS/ECS.h"
#include "../Math/JZMath.h"
#include "Texture.h"

#include "RendererDebug.h"

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

	// sprite system
	struct Sprite : public ECS::System
	{
		SpriteRenderer sprite_renderer_;

		Sprite ()
		{
			RegisterComponents<Transform , Texture , Animation2D , NonInstanceShader , NotBackground> ();
		}

		virtual void FrameBegin ( const float& dt ) override
		{}

		virtual void Update(const float& dt) override;
		//{
		//	Transform& transform = GetComponent<Transform> ();
		//	Texture& texture = GetComponent<Texture> ();
		//	NonInstanceShader& shader = GetComponent<NonInstanceShader> ();
		//	Animation2D& anim2d = GetComponent<Animation2D> ();

		//	// update animation
		//	if( anim2d.animation_counter_ < anim2d.animation_speed_ )
		//	{
		//		anim2d.animation_counter_ += dt;
		//	}
		//	else
		//	{
		//		++anim2d.frame_;
		//		if( anim2d.frame_ >= anim2d.max_frames_ )
		//		{
		//			anim2d.frame_ = 0;
		//		}
		//		anim2d.animation_counter_ = 0.0f;
		//	}

		//	transform.model_transform_ = Math::GetModelTransformNonTransposed ( transform.position_ , transform.rotation_ , transform.scale_ , transform.size_ );

		//	sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ , ( Math::GetProjectionTransformNonTransposed () * transform.model_transform_ ).Transpose () , shader.tint , anim2d.frame_ , anim2d.rows_ , anim2d.column_ , anim2d.animation_check_);

		//	RendererDebug::DrawSpriteSquare ( transform.position_ , { transform.scale_.x * transform.size_.x, transform.scale_.y * transform.size_.y } );
		//}
	};
}