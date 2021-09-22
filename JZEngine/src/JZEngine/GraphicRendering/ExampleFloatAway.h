#pragma once

#include "../ECS/ECS.h"

namespace JZEngine
{
	struct IsUnicorn
	{
		char flag;
	};

	struct FloatAwayAllUnicorn : public ECS::System
	{
		FloatAwayAllUnicorn();

		virtual void Update( const float& dt ) override;
	};

	struct IsInputAffected
	{
		float val{ 0.0f };
	};

	struct MakeUnicornAffectedByInput : public ECS::System
	{
		MakeUnicornAffectedByInput();

		virtual void Update( const float& dt ) override;
	};
}
