#pragma once

#include "../ECS/ECS.h"

namespace JZEngine
{
	struct FollowMouseCursor
	{
		char flag_{'\0'};
	};

	struct FollowMouseCursorSystem : public ECS::System
	{
		FollowMouseCursorSystem();
		virtual void Update(const float& dt);
	};
}