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
						  JZEngine::Vec2f position ,
						  JZEngine::Vec2f size = { 10.0f , 10.0f } ,
						  JZEngine::Vec2f scale = { 1.0f ,1.0f } ,
						  float rotateDegree = 0.0f ,
						  JZEngine::Vec3f color = { 1.0f, 1.0f ,1.0f } ,
						  JZEngine::Vec3f tint = { 0.0f , 0.0f , 0.0f } );

		Renderer* renderer_{ nullptr };
	};
}