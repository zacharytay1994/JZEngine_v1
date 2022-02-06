#pragma once

#include "../ECS/ECS.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	struct AnimatedTransformComponent
	{
		bool active_flag { false };
		// speed should only be positive
		float speed_ { 1.0f };
		float modulate_rotation_ { 0.0f };
		Vec2f modulate_scale_ { 0.0f,0.0f };

		bool active_ { false };
		float accumulated_speed_ { 0.0f };
		bool on_init_ { true };
		float original_rotation_;
		Vec2f original_scale_;
		bool positive_ { true };

		bool repeat_ { true };
	};

	struct AnimatedTransform : public JZEngine::ECS::System
	{
		AnimatedTransform ();

		virtual void Update ( const float& dt ) override;
	private:

	};
}