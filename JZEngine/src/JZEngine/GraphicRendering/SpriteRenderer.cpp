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
	//void SpriteRenderer::Init()
	//{
	//	//Renderer::Instance().Init();
	//	//texture_.Texture2DLoad( texture );
	//	//shader_ = Renderer::Instance().GetShaderProgram();
	//}

	void SpriteRenderer::DrawSprite(int shaderid, int textureid, JZEngine::Vec2f position, JZEngine::Vec2f size, JZEngine::Vec2f scale, float rotateDegree, JZEngine::Vec3f color )
	{
		JZEngine::Mat3f mat_scale = JZEngine::Mat3f::Scale(size.x * scale.x , size.y * scale.y, 1.0f);
		JZEngine::Mat3f mat_rotate = JZEngine::Mat3f::RotateZ( Math::DegToRad(rotateDegree) );
		JZEngine::Mat3f mat_translate = JZEngine::Mat3f::Translate(position.x, position.y);

		JZEngine::Mat3f camwin_to_ndc_xform = { {2.0f / ( Settings::aspect_ratio * Settings::window_height ), 0.0f, 0.0f},
												{0.0f, 2.0f / Settings::window_height, 0.0f},
												{0.0f, 0.0f, 1.0f} };

		JZEngine::Mat3f transform = mat_translate * ( mat_rotate * mat_scale );
		transform = camwin_to_ndc_xform * transform;
		transform.Transpose();

		// bind buffer data
		//Renderer::Instance().Bind();
		renderer_->Bind();
		glCheckError();
		// use shader program
		renderer_->BindShader(shaderid);
		glCheckError();

		// bind texture
		//texture_.Bind();
		//renderer_->BindTexture("unicorn");
		renderer_->BindTexture(textureid);
		glCheckError();
		//Renderer::Instance().GetShaderProgram().SetUniform( "transform", transform );
		renderer_->GetShaderProgram(shaderid).SetUniform("transform", transform);
		glCheckError();

		renderer_->Draw();

		renderer_->Unbind();
		//renderer_->UnbindShader(shaderid);
		/*Renderer::Instance().Draw();
		Renderer::Instance().Unbind();*/
	}

	void SpriteRenderer::InitRenderData()
	{}

	void SpriteRenderer::InstancingDraw()
	{}
}