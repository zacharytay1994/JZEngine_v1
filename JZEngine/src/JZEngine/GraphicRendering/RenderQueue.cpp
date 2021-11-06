#include <PCH.h>
#include "RenderQueue.h"
#include "Renderer.h"
#include "OpenGLDebug.h"
#include "../DebugTools/PerformanceData.h"

namespace JZEngine {
	std::priority_queue<RenderQueue::RenderData, std::vector<RenderQueue::RenderData>, RenderQueue::CompareRenderData> RenderQueue::render_queue_;
	std::vector<RenderQueue::LayerData> RenderQueue::layers_;

	void RenderQueue::Update(float dt) {
		// flush the draw queue and render all data
		if (renderer_) {
			while (render_queue_.size() > 0) {
				const RenderData& sl = render_queue_.top();
				DrawSprite(sl.shader_id_, sl.texture_id_, sl.transform_, sl.tint_, sl.frame_, sl.rows_, sl.cols_, sl.animated_);
				render_queue_.pop();
			}
		}
	}

	void RenderQueue::FrameEnd() {
		layers_.clear();
	}

	void RenderQueue::DrawQueue(int layer,
								int shaderid,
								int textureid,
								const Mat3f& transform,
								const JZEngine::Vec3f& tint,
								int frame,
								int rows,
								int cols,
								bool animated) 
	{
		render_queue_.emplace(layer, shaderid, textureid, transform, tint, frame, rows, cols, animated);
	}

	void RenderQueue::GUILayerData(int* layer, int textureid)
	{
		layers_.emplace_back(layer, textureid);
	}

	void RenderQueue::DrawSprite(	int shaderid,
									int textureid,
									const Mat3f& transform,
									JZEngine::Vec3f tint,
									int frame,
									int rows,
									int cols,
									bool animated) {
		// bind buffer data
		renderer_->Bind();
		glCheckError();

		// use shader program
		renderer_->BindShader(shaderid);
		glCheckError();

		// bind texture data
		renderer_->BindTexture(textureid);
		glCheckError();

		// set shader uniforms
		renderer_->GetShaderProgram(shaderid).SetUniform("transform", transform);
		renderer_->GetShaderProgram(shaderid).SetUniform("tint", tint);
		//Log::Info("Main", "{}", PerformanceData::time_elapsed_);
		renderer_->GetShaderProgram(shaderid).SetUniform("time", PerformanceData::time_elapsed_);
		glCheckError();

		if (animated)
		{
			// draw animated sprite
			renderer_->Draw(frame, rows, cols);
		}
		else
		{
			renderer_->Draw();
		}

		// unbind buffer data
		renderer_->Unbind();
	}

	void RenderQueue::SetRenderer(Renderer* renderer) {
		renderer_ = renderer;
	}
}