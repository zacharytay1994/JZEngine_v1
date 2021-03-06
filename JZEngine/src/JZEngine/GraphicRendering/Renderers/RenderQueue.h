/*	__FILE HEADER__
*	File:		RenderQueue.cpp
	Primary:	Jee Jia Min, Zachary Tay
	Date:		19/06/21
	Brief:		Helps render sprites back to front.
*/

#pragma once

#include "../../GlobalSystems.h"
#include "../../Math/JZMath.h"

#include <queue>
#include <vector>

namespace JZEngine
{
	class Renderer;
	struct ResourceManager;
	struct RenderQueue
	{
		struct RenderData
		{
			int layer_;
			int shader_id_;
			int texture_id_;
			Mat3f transform_;
			Vec4f tint_;
			int frame_;
			int rows_;
			int cols_;
			bool animated_;

			RenderData ( int layer , int shader_id , int texture_id , const Mat3f& transform , const Vec4f& tint , int frame , int rows , int cols , bool animated )
				: layer_ ( layer ) , shader_id_ ( shader_id ) , texture_id_ ( texture_id ) , transform_ ( transform ) , tint_ ( tint ) , frame_ ( frame ) , rows_ ( rows ) , cols_ ( cols ) , animated_ ( animated )
			{}
		};

		struct LayerData
		{
			int* layer_{ nullptr };
			int		texture_id_{ 0 };

			LayerData ( int* layer , int textureId , bool isBackground = false ) : layer_ ( layer ) , texture_id_ ( textureId )
			{
				UNREFERENCED_PARAMETER ( isBackground );
			}
		};

		class CompareRenderData
		{
		public:
			bool operator() ( RenderData& sl1 , RenderData& sl2 )
			{
				return sl1.layer_ > sl2.layer_;
			}
		};

		void Update ( ResourceManager* rm );

		void FrameEnd ();

		static void DrawQueue ( int layer ,
								int shaderid ,
								int textureid ,
								const Mat3f& transform ,
								const JZEngine::Vec4f& tint = { 0.0f , 0.0f , 0.0f ,1.0f } ,
								int frame = 0 ,
								int rows = 1 ,
								int cols = 1 ,
								bool animated = false );

		static void GUILayerData ( int* layer , int textureid );

		void SetRenderer ( Renderer* renderer );

		static std::vector<LayerData> layers_;

		static std::priority_queue<RenderData, std::vector<RenderData>, CompareRenderData> render_queue_;

		void DrawSprite(ResourceManager* rm,
			int shaderid,
			int textureid,
			const Mat3f& transform,
			const JZEngine::Vec4f tint = { 0.0f , 0.0f , 0.0f ,1.0f },
			int frame = 0,
			int rows = 1,
			int cols = 1,
			bool animated = false);
	private:
		Renderer* renderer_{ nullptr };
	};
}