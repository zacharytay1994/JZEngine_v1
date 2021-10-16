/*	__FILE HEADER__
*	File:		SpriteRenderer.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		For user to pass in data to render a sprite or picture.
*/

#pragma once

#include <memory>

#include "Shader.h"
#include "Texture.h"
#include "RendererInstancing.h"
#include "../Math/JZMath.h"
#include <queue>

namespace JZEngine
{
	class Renderer;
	class SpriteRenderer
	{
		struct SpriteLayer
		{
			int layer_;
			int shader_id_;
			int texture_id_;
			Mat3f transform_;
			Vec3f tint_;
			int frame_;
			int rows_;
			int cols_;
			bool animated_;

			SpriteLayer ( int layer , int shader_id , int texture_id , const Mat3f& transform , const Vec3f& tint , int frame , int rows , int cols , bool animated )
				:
				layer_ ( layer ) ,
				shader_id_ ( shader_id ) ,
				texture_id_ ( texture_id ) ,
				transform_ ( transform ) ,
				tint_ ( tint ) ,
				frame_ ( frame ) ,
				rows_ ( rows ) ,
				cols_ ( cols ) ,
				animated_ ( animated )
			{}
		};

		class CompareSpriteLayer
		{
		public:
			bool operator() ( SpriteLayer& sl1 , SpriteLayer& sl2 )
			{
				return sl1.layer_ > sl2.layer_;
			}
		};

	public:

		std::priority_queue<SpriteLayer , std::vector<SpriteLayer> , CompareSpriteLayer> draw_queue_;

		SpriteRenderer ();
		~SpriteRenderer ();

		void DrawSprite ( int shaderid ,
						  int textureid ,
						  const Mat3f& transform ,
						  JZEngine::Vec3f tint = { 0.0f , 0.0f , 0.0f } ,
						  int frame = 0 ,
						  int rows = 1 ,
						  int cols = 1 ,
						  bool animated = false );

		void DrawSpriteQueue ( int layer ,
							   int shaderid ,
							   int textureid ,
							   const Mat3f& transform ,
							   const JZEngine::Vec3f& tint = { 0.0f , 0.0f , 0.0f } ,
							   int frame = 0 ,
							   int rows = 1 ,
							   int cols = 1 ,
							   bool animated = false );

		void FlushDrawAllSprites ();

		Renderer* renderer_{ nullptr };
	};
}