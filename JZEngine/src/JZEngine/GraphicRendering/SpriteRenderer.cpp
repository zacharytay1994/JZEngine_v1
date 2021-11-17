/*	__FILE HEADER__
*	File:		SpriteRenderer.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		ECS sprite renderer to render non instanced sprites.
*/

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
	SpriteRenderer::SpriteRenderer ()
	{}
	SpriteRenderer::~SpriteRenderer ()
	{}

	void SpriteRenderer::DrawSprite ( int shaderid ,
									  int textureid ,
									  const Mat3f& transform ,
									  JZEngine::Vec3f tint ,
									  int frame ,
									  int rows ,
									  int cols ,
									  bool animated )
	{
		//// bind buffer data
		//renderer_->Bind ();
		//glCheckError ();

		//// use shader program
		//renderer_->BindShader ( shaderid );
		//glCheckError ();

		//// bind texture data
		//renderer_->BindTexture ( textureid );
		//glCheckError ();

		//// set shader uniforms
		//renderer_->GetShaderProgram ( shaderid ).SetUniform ( "transform" , transform );
		//renderer_->GetShaderProgram ( shaderid ).SetUniform ( "tint" , tint );
		//glCheckError ();

		//if( animated )
		//{
		//	// draw animated sprite
		//	renderer_->Draw ( frame , rows , cols );
		//}
		//else
		//{
		//	renderer_->Draw ();
		//}

		//// unbind buffer data
		//renderer_->Unbind ();
	}

	void SpriteRenderer::DrawSpriteQueue(	int layer,
											int shaderid,
											int textureid,
											const Mat3f& transform,
											const JZEngine::Vec3f& tint,
											int frame,
											int rows,
											int cols,
											bool animated)
	{
		draw_queue_.emplace(layer, shaderid, textureid, transform, tint, frame, rows, cols, animated);
	}


	void SpriteRenderer::FlushDrawAllSprites()
	{
		while (draw_queue_.size() > 0)
		{
			const SpriteLayer& sl = draw_queue_.top();
			DrawSprite(sl.shader_id_, sl.texture_id_, sl.transform_, sl.tint_, sl.frame_, sl.rows_, sl.cols_, sl.animated_);
			draw_queue_.pop();
		}
	}
}