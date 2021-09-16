#include <PCH.h>
#include <math.h>
#include <assert.h>
#include "OpenGLDebug.h"
#include "SpriteRenderer.h"
#include "Renderer.h"
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
		shader_ = Renderer::Instance().GetShaderProgram();
	}

	void SpriteRenderer::DrawSprite( JZEngine::Vec2f position, JZEngine::Vec2f size, float rotateDegree, JZEngine::Vec3f color )
	{
		UNREFERENCED_PARAMETER( position );
		UNREFERENCED_PARAMETER( rotateDegree );
		UNREFERENCED_PARAMETER( rotateDegree );



		//JZEngine::Mat3f model3;
		//std::cout << "-----------------------START-----------------\n";
		//model3 *= JZEngine::Mat3f::Translate( position.x, position.y );
		//std::cout << model3;
		//model3 *= JZEngine::Mat3f::Translate( 0.5f * size.x, 0.5f * size.y );
		//std::cout << model3;
		//model3 *= JZEngine::Mat3f::RotateZ( rotateDegree * ( PI / 180.0f ) );
		//std::cout << model3;
		//model3 *= JZEngine::Mat3f::Translate( -0.5f * size.x, -0.5f * size.y );
		//std::cout << model3;
		//model3 *= JZEngine::Mat3f::Scale( size.x, size.y, 1.0f );
		//JZEngine::Mat4f model4 =static_cast < JZEngine::Mat4f> (model3);
		//std::cout << "-----------------------END-------------------\n";

		Renderer::Instance().Bind();
		glCheckError();
		texture_.Bind();
		glCheckError();
	/*	shader_.SetUniform( "model", model4 );
		glCheckError();
		shader_.SetUniform( "spriteColor", color );
		glCheckError();*/
		Renderer::Instance().Draw();
		Renderer::Instance().Unbind();
	}

	void SpriteRenderer::InitRenderData()
	{}
}