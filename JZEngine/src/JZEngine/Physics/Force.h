/*	__FILE HEADER__
*	File:		Force.h
	Primary:	Deon Khong
	Date:		11/11/21
	Brief:		Header file For applying forces for physics objects
*/
#pragma once

#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"


namespace JZEngine
{
	class ForcesManager
	{

	public:
		

		static void ApplyGravity(PhysicsComponent& pcomponent);

		static void AddForce(PhysicsComponent& pcomponent, const Vec2f& force);

		

	private:
		static Vec2f gravity;// m / s*s

	};


}
