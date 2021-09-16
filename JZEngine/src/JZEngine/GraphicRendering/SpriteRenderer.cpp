#include <PCH.h>
#include "SpriteRenderer.h"
#include "Renderer.h"
#include <math.h>
#include "../Math/JZMatrix.h"

#define PI 3.14159265359f

namespace JZEngine
{
	SpriteRenderer::SpriteRenderer()
	{}
	SpriteRenderer::~SpriteRenderer()
	{}
	void SpriteRenderer::Init( const std::string& texture )
	{
		Renderer::Instance().Init();
		texture_.Texture2DLoad( texture );
	}

	void SpriteRenderer::DrawSprite( JZEngine::Vec2f position, JZEngine::Vec2f size, float rotateDegree, JZEngine::Vec3f color )
	{

		JZEngine::Mat3f model;
		model *= JZEngine::Mat3f::Translate( position.x, position.y );
		model *= JZEngine::Mat3f::Translate( 0.5f * size.x, 0.5f * size.y );
		model *= JZEngine::Mat3f::RotateZ( rotateDegree * ( PI / 180.0f ) );
		model *= JZEngine::Mat3f::Translate( -0.5f * size.x, -0.5f * size.y );
		model *= JZEngine::Mat3f::Scale( size.x, size.y, 1.0f );


		shader_.SetUniform( "model", model );
		shader_.SetUniform( "spriteColor", color );
		texture_.Bind();
		Renderer::Instance().Draw();
	}

	void SpriteRenderer::InitRenderData()
	{}
}