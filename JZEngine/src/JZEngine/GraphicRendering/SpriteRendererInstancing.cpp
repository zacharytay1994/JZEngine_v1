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
