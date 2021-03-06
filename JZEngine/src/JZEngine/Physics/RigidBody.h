/*	__FILE HEADER__
*	File:		RegidBody.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Physics rigidbodies.
*/

#pragma once

#include "../Math/JZMath.h"
#include "../Physics/PhysicsComponent.h"


namespace JZEngine
{
	class RigidBody
	{
	
	public:
		static void Update(PhysicsComponent& pcomponent, const float& dt);

		

		static void Move(PhysicsComponent& pcomponent, const Vec2f& moveby);




	};


}


