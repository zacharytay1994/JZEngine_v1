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

	void SpriteRenderer::DrawSprite( int shaderid, int textureid, const Mat3f& transform )
	{
		// bind buffer data
		renderer_->Bind();
		glCheckError();

		// use shader program
		renderer_->BindShader( shaderid );
		glCheckError();

		// bind texture data
		renderer_->BindTexture( textureid );
		glCheckError();

		// set shader uniforms
		renderer_->GetShaderProgram( shaderid ).SetUniform( "transform", transform );
		glCheckError();

		// draw sprite
		renderer_->Draw();

		// unbind buffer data
		renderer_->Unbind();
	}
}