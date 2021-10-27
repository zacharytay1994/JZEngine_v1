/*	__FILE HEADER__
*	File:		PhysicsDebug.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Debugs engine physics.
*/

#pragma once
#include "../GraphicRendering/RendererDebug.h"
#include "../Physics/CollisionComponent.h"
namespace JZEngine
{
	namespace PhysicsDebug
	{

		void DebugDrawShape(const CollisionComponent& pcomponent);

		void DebugDrawLine(const Vec2f& p0, const Vec2f& p1);

		void DebugDrawPoint(const Vec2f& p0);
	}
}