#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

#include "../Physics/PhyicsDebug.h"

#include "CollisionShapeSystem.h"

#define COLLISIONDEBUG 
namespace JZEngine
{
	CollisionShapeSystem::CollisionShapeSystem()
	{
		RegisterComponents<CollisionComponent, Transform>();
	}

	void CollisionShapeSystem::FrameBegin(const float& dt)
	{
	}

	//update shapes & vertices according to a offset for the collision
	void CollisionShapeSystem::Update(const float& dt)
	{

		Transform& tcomponent = GetComponent<Transform>();
		CollisionComponent& ccomponent = GetComponent<CollisionComponent>();

		if (ccomponent.shapeid == shapetype::circle)
		{
			ccomponent.m_circle.m_center = tcomponent.position_ + ccomponent.offset;
			ccomponent.m_circle.m_radius = 0.5f * ccomponent.size.x;
		}
		if (ccomponent.shapeid == shapetype::square)
		{
			ccomponent.m_square = { tcomponent.position_ + ccomponent.offset,ccomponent.size };

			for (int i = 0; i < 4; i++)
			{
				ccomponent.m_square.vertices[i] =
					Math::GetRotatedVector((ccomponent.m_square.vertices[i] - tcomponent.position_)
						, Math::DegToRad(tcomponent.rotation_)) + tcomponent.position_;

			}
			//pcomponent.ModeltoWorld = Math::GetModelTransformNonTransposed(pcomponent.position, pcomponent.rotation, tcomponent.scale_, pcomponent.size);
		}
		if (ccomponent.shapeid == shapetype::aabb)
		{
			ccomponent.m_aabb = { tcomponent.position_ + ccomponent.offset , ccomponent.size };
		}



#ifdef COLLISIONDEBUG
		PhysicsDebug::DebugDrawShape(ccomponent);
#endif
	}

	void CollisionShapeSystem::FrameEnd(const float& dt)
	{
	}

}