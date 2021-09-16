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

	void SpriteRenderer::DrawSprite( JZEngine::Vec2f position, JZEngine::Vec2f scale, float rotateDegree, JZEngine::Vec3f color )
	{
		UNREFERENCED_PARAMETER( position );
		UNREFERENCED_PARAMETER( rotateDegree );
		UNREFERENCED_PARAMETER( scale );

		JZEngine::Mat3f transform; // make sure to initialize matrix to identity matrix first
		transform *= JZEngine::Mat3f::RotateZ( ( float )glfwGetTime() * ( PI / 180.0f ) );
		transform *= JZEngine::Mat3f::Scale( scale.x, scale.y, 1.0f );
		JZEngine::Mat4f transform4 = static_cast < JZEngine::Mat4f > ( transform );

		Renderer::Instance().Bind();
		glCheckError();
		texture_.Bind();
		glCheckError();
		shader_.SetUniform( "transform", transform4 );
		glCheckError();
		Renderer::Instance().Draw();
		Renderer::Instance().Unbind();
	}

	void SpriteRenderer::InitRenderData()
	{}
}