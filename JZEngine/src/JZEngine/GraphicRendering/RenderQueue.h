#pragma once

#include "../GlobalSystems.h"
#include "../Math/JZMath.h"

#include <queue>

namespace JZEngine {
	class Renderer;
	struct RenderQueue : public GlobalSystem {
		struct RenderData
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

			RenderData(int layer, int shader_id, int texture_id, const Mat3f& transform, const Vec3f& tint, int frame, int rows, int cols, bool animated)
				: layer_(layer), shader_id_(shader_id), texture_id_(texture_id), transform_(transform), tint_(tint), frame_(frame), rows_(rows), cols_(cols), animated_(animated) { }
		};

		class CompareRenderData
		{
		public:
			bool operator() (RenderData& sl1, RenderData& sl2)
			{
				return sl1.layer_ > sl2.layer_;
			}
		};

		virtual void Update(float dt) override;

		static void DrawQueue(		int layer,
									int shaderid,
									int textureid,
									const Mat3f& transform,
									const JZEngine::Vec3f& tint = { 0.0f , 0.0f , 0.0f },
									int frame = 0,
									int rows = 1,
									int cols = 1,
									bool animated = false);

		void SetRenderer(Renderer* renderer);
	private:
		Renderer*			renderer_				{ nullptr };
		static std::priority_queue<RenderData, std::vector<RenderData>, CompareRenderData> render_queue_;

		void DrawSprite(	int shaderid,
							int textureid,
							const Mat3f& transform,
							JZEngine::Vec3f tint,
							int frame,
							int rows,
							int cols,
							bool animated);
	};
}