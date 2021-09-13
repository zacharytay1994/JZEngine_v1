#include <PCH.h>
#include "Renderer.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "../Math/JZMatrix.h"

namespace JZEngine
{
	SpriteRenderer::SpriteRenderer()
	{
		Renderer::Instance().Init();
	}
	SpriteRenderer::~SpriteRenderer()
	{}
	void SpriteRenderer::DrawSprite( std::string& texture, JZEngine::Vec2<float> position, JZEngine::Vec2<float> size, float rotate, JZEngine::Vec3<float> color )
	{
		Texture2D texture_( texture );

		JZEngine::Mat3d model;




		texture_.Bind();
		Renderer::Instance().Bind();
	}
	void SpriteRenderer::InitRenderData()
	{}
}