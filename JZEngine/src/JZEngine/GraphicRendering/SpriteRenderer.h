#pragma once

#include "Shader.h"
#include "../Math/JZMath.h"

namespace JZEngine
{
	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void Init();
		void DrawSprite( const std::string& texture,
						 JZEngine::Vec2f position,
						 JZEngine::Vec2f size = { 10.0f ,10.0f },
						 float rotateDegree = 0.0f,
						 JZEngine::Vec3f color = { 1.0f, 1.0f ,1.0f } );

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