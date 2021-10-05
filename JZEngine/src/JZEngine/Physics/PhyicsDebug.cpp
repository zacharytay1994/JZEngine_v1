#include "PCH.h"
#include "PhyicsDebug.h"
namespace JZEngine
{
	namespace PhysicsDebug
	{
		void DebugDrawShape(const PhysicsComponent& current_pcomponent)
		{
			if (current_pcomponent.shapeid == shapetype::circle)
			{
				RendererDebug::DrawCircle(current_pcomponent.m_circle.m_center, current_pcomponent.m_circle.m_radius);
				RendererDebug::DrawPoint(current_pcomponent.m_circle.m_center);
			}
			if (current_pcomponent.shapeid == shapetype::square)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i == 3)
						RendererDebug::DrawLine(current_pcomponent.m_square.vertices[i], current_pcomponent.m_square.vertices[0]);
					else
						RendererDebug::DrawLine(current_pcomponent.m_square.vertices[i], current_pcomponent.m_square.vertices[(i + 1)]);
				}
				RendererDebug::DrawPoint(current_pcomponent.m_square.midpoint);
			}
		}
		void DebugDrawLine(const Vec2f& p0, const Vec2f& p1)
		{
			RendererDebug::DrawLine(p0, p1);
		}
	}
}
