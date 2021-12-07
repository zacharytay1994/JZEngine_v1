/*	__FILE HEADER__
*	File:		PhysicsPlayer.cpp
	Primary:	Deon Khong
	Date:		07/12/21
	Brief:		For applying forces for player object for physics
*/
#include "PCH.h"
#include "PhysicsPlayer.h"

void JZEngine::PlayerControl(PhysicsComponent& pcomponent)
{
	float dx = 0.f;
	float dy = 0.f;
	float forcemagnitude = 2 * pcomponent.Mass * 398.1f;
	if (InputHandler::IsKeyPressed(KEY::KEY_W))
		++dy;
	if (InputHandler::IsKeyPressed(KEY::KEY_A))
		--dx;
	if (InputHandler::IsKeyPressed(KEY::KEY_S))
		--dy;
	if (InputHandler::IsKeyPressed(KEY::KEY_D))
		++dx;

	if (dx != 0.f || dy != 0.f)
	{
		Vec2f forcedirection{ dx,dy };
		forcedirection.Normalize();
		Vec2f force = forcedirection * forcemagnitude;
		ForcesManager::AddForce(pcomponent, force);

	}

}
