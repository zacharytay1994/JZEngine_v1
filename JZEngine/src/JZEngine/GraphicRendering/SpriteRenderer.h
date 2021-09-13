#pragma once

#include <PCH.h>
#include "Shader.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"

namespace JZEngine
{
	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void DrawSprite( std::string& texture,
						 JZEngine::Vec2<float> position,
						 JZEngine::Vec2<float> size = { 10.0f ,10.0f },
						 float rotate = 0.0f,
						 JZEngine::Vec3<float> color = { 1.0f, 1.0f ,1.0f } );

	private:
		std::string texture_path_{};
		JZEngine::Vec2<float> position_{};
		JZEngine::Vec2<float> size_{};
		JZEngine::Vec3<float> color_{};

		// Render state
		Shader shader_{};


	private:

		// Initializes and configures the quad's buffer and vertex attributes
		void InitRenderData();

	};

}