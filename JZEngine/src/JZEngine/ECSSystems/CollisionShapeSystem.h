#pragma once

#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

#include "../GraphicRendering/TransformComponent.h"

namespace JZEngine
{
	struct CollisionShapeSystem : public JZEngine::ECS::System
	{
		CollisionShapeSystem();

		virtual void FrameBegin(const float& dt) override;

		// updates once per entity component per system per frame
		virtual void Update(const float& dt) override;

		virtual void FrameEnd(const float& dt) override;
	private:

	};


}