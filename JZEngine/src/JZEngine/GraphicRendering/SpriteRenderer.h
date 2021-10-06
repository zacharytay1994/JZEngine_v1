/*	__FILE HEADER__
*	File:	SpriteRenderer.h
	Author: JZ
	Date:	01/07/21
	Brief:	For user to pass in data to render a sprite or picture.
*/

#pragma once

#include <memory>

#include "Shader.h"
#include "Texture.h"
#include "RendererInstancing.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	class Renderer;
	class SpriteRenderer
	{
	public:
		SpriteRenderer ();
		~SpriteRenderer ();

		void DrawSprite ( int shaderid ,
						  int textureid ,
						  const Mat3f& transform ,
						  JZEngine::Vec3f tint = { 0.0f , 0.0f , 0.0f } ,
						  int frame = 0 ,
						  int rows = 1 ,
						  int cols = 1 ,
						  bool animated = false);

		Renderer* renderer_{ nullptr };
	};
}