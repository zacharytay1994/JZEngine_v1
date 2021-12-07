/*	__FILE HEADER__
*	File:		CollisionShapeSystem.h
	Primary:	Deon Khong
	Date:		11/11/21
	Brief:		Header file For updating vertices of physics shapes
*/
#pragma once

#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

#include "../Physics/QuadTree.h"
#include "../GraphicRendering/Systems/TransformComponent.h"

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