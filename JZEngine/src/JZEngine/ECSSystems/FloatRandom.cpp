#include <PCH.h>
#include "FloatRandom.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	FloatRandom::FloatRandom()
	{
		RegisterComponents<Transform, RandomMovement>();
	}

	void FloatRandom::Update(const float& dt)
	{
		GetComponent<Transform>().position_ += GetComponent<RandomMovement>().direction_ * dt;
	}
}