/*	__FILE HEADER__
*	File:		Force.cpp
	Primary:	Deon Khong
	Date:		11/11/21
	Brief:		For applying forces for physics objects
*/

#include "PCH.h"
#include "Force.h"

namespace JZEngine
{
	Vec2f ForcesManager::gravity{ 0.f, -398.1f };

	void ForcesManager::ApplyGravity(PhysicsComponent& pcomponent)
	{
		if (pcomponent.IsStatic)
			return;
		pcomponent.acceleration = gravity;
	}

	void ForcesManager::AddForce(PhysicsComponent& pcomponent, const Vec2f& force)
	{
		pcomponent.totalforce += force;
	}

}
