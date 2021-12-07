/*	__FILE HEADER__
*	File:		PhysicsPlayer.h
	Primary:	Deon Khong
	Date:		11/11/21
	Brief:		Header file For applying forces for player object for physics
*/
#pragma once
#include "../Physics/PhysicsComponent.h"
#include "../Physics/Force.h"
#include "../Input/Input.h"
namespace JZEngine
{
	void PlayerControl(PhysicsComponent& pcomponent);

}