#pragma once
#include "../GraphicRendering/RendererDebug.h"
#include "../Physics/PhysicsComponent.h"
namespace JZEngine
{
	namespace PhysicsDebug
	{

		void DebugDrawShape(const PhysicsComponent& pcomponent);

		void DebugDrawLine(const Vec2f& p0, const Vec2f& p1);
	}
}