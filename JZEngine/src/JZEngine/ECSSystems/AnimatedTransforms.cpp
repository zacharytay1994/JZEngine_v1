#include <PCH.h>
#include "AnimatedTransforms.h"

#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	AnimatedTransform::AnimatedTransform ()
	{
		RegisterComponents<AnimatedTransformComponent , Transform> ();
	}

	void AnimatedTransform::Update ( const float& dt )
	{
		AnimatedTransformComponent& atc = GetComponent<AnimatedTransformComponent> ();
		Transform& transform = GetComponent<Transform> ();
		
		if ( atc.on_init_ )
		{
			atc.original_rotation_ = transform.rotation_;
			atc.original_scale_ = transform.scale_;
			atc.on_init_ = false;
		}

		if ( atc.active_flag != atc.active_ )
		{
			transform.rotation_ = atc.original_rotation_;
			transform.scale_ = atc.original_scale_;
			atc.active_ = atc.active_flag;
			atc.accumulated_speed_ = 0.0f;
			return;
		}

		if ( atc.active_ )
		{
			if ( atc.positive_ )
			{
				if ( atc.accumulated_speed_ > 1.0f )
				{
					atc.positive_ = false;
				}
				else
				{
					atc.accumulated_speed_ += atc.speed_ * dt;
				}
			}
			/*else
			{
				if ( atc.accumulated_speed_ < 0.0f )
				{
					atc.positive_ = true;
				}
				else
				{
					atc.accumulated_speed_ -= atc.speed_ * dt;
				}
			}*/

			transform.rotation_ = atc.original_rotation_ + ( atc.accumulated_speed_ * ( atc.modulate_rotation_ - atc.original_rotation_ ) );
			transform.scale_.x = atc.original_scale_.x + ( atc.accumulated_speed_ * atc.modulate_scale_.x * atc.original_scale_.x );
			transform.scale_.y = atc.original_scale_.y + ( atc.accumulated_speed_ * atc.modulate_scale_.y * atc.original_scale_.y );
		}
	}
}