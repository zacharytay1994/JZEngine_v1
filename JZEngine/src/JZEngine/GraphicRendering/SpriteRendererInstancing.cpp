/*	__FILE HEADER__
*	File:		SpriteRendererInstancing.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		ECS sprite renderer to render instanced sprites.
*/

#include <PCH.h>
#include "SpriteRendererInstancing.h"
#include "RendererInstancing.h"

namespace JZEngine
{
	SpriteRendererInstancing::SpriteRendererInstancing()
	{

	}

	SpriteRendererInstancing::~SpriteRendererInstancing()
	{

	}

	void SpriteRendererInstancing::DrawInstances()
	{
		if ( renderer_ )
		{
			renderer_->Draw();
		}
	}
}
