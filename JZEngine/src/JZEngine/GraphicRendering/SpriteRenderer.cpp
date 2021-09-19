#include <PCH.h>
#include <math.h>
#include <assert.h>
#include "OpenGLDebug.h"
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "../EngineConfig.h"
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

	void SpriteRenderer::DrawSprite( JZEngine::Vec2f position, JZEngine::Vec2f size, JZEngine::Vec2f scale, float rotateDegree, JZEngine::Vec3f color )
	{
		// To Be Fixed
		JZEngine::Mat3f mat_scale = JZEngine::Mat3f::Scale( scale.x * size.x, scale.y * size.y, 1.0f );
		JZEngine::Mat3f mat_rotate = JZEngine::Mat3f::RotateZ( JZEngine::Math::RadToDeg( rotateDegree ) );
		JZEngine::Mat3f mat_translate = JZEngine::Mat3f::Translate( position.x, position.y );

		JZEngine::Mat3f camwin_to_ndc_xform = { {2.0f / ( Settings::aspect_ratio * Settings::window_height ), 0.0f, 0.0f},
												{0.0f, 2.0f / Settings::window_height, 0.0f},
												{0.0f, 0.0f, 1.0f} };

		JZEngine::Mat3f transform = mat_translate * ( mat_rotate * mat_scale );
		transform = camwin_to_ndc_xform * transform;
		transform.Transpose();

		Renderer::Instance().Bind();
		glCheckError();
		texture_.Bind();
		glCheckError();
		shader_.SetUniform( "transform", transform );
		glCheckError();
		Renderer::Instance().Draw();
		Renderer::Instance().Unbind();
	}

	void SpriteRenderer::InitRenderData()
	{}

	void SpriteRenderer::InstancingDraw()
	{

	}
}