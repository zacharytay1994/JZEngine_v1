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
#include "../Math/JZMath.h"

namespace JZEngine
{
	class Renderer;
	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		//void Init();
		void DrawSprite( int shaderid,
						 int textureid,
						 JZEngine::Vec2f position,
						 JZEngine::Vec2f size = { 10.0f , 10.0f },
						 JZEngine::Vec2f scale = { 1.0f ,1.0f },
						 float rotateDegree = 0.0f,
						 JZEngine::Vec3f color = { 1.0f, 1.0f ,1.0f } );

		Renderer* renderer_{ nullptr };

	private:
		std::string texture_path_{};
		JZEngine::Vec2<float> position_{};
		JZEngine::Vec2<float> size_{};
		JZEngine::Vec3<float> color_{};

		// Render state
		//Shader shader_{};
		//Texture2D texture_{};

	private:

		// Initializes and configures the quad's buffer and vertex attributes
		void InitRenderData();
	};

}