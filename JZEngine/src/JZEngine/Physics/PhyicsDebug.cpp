/*	__FILE HEADER__
*	File:		PhysicsDebug.cpp
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Debugs engine physics.
*/

#include "PCH.h"
#include "PhyicsDebug.h"
namespace JZEngine
{
	namespace PhysicsDebug
	{
		void DebugDrawShape(const PhysicsComponent& pcomponent)
		{
			if (pcomponent.shapeid == shapetype::circle)
			{
				RendererDebug::DrawCircle(pcomponent.m_circle.m_center, pcomponent.m_circle.m_radius);
				RendererDebug::DrawPoint(pcomponent.m_circle.m_center);
			}
			if (pcomponent.shapeid == shapetype::square)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i == 3)
						RendererDebug::DrawLine(pcomponent.m_square.vertices[i], pcomponent.m_square.vertices[0]);
					else
						RendererDebug::DrawLine(pcomponent.m_square.vertices[i], pcomponent.m_square.vertices[(i + 1)]);
				}
				RendererDebug::DrawPoint(pcomponent.m_square.midpoint);
			}
		}
		void DebugDrawLine(const Vec2f& p0, const Vec2f& p1)
		{
			RendererDebug::DrawLine(p0, p1);
		}
	}
}
