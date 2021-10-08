#pragma once
#include "../ECS/ECS.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	struct RandomMovement
	{
		Vec2f direction_{0.0f, 0.0f};
	};

	struct FloatRandom : public ECS::System
	{
		FloatRandom();

		virtual void Update(const float& dt) override;
	};
}