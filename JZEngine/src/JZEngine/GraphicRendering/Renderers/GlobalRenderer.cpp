/*	__FILE HEADER__
*	File:		GlobalRenderer.h
	Primary:	Jia Min
	Date:		01/07/21
	Brief:		Handles all rendering.
*/

#include <PCH.h>
#include "GlobalRenderer.h"

/*! resource includes - START */
#include "../../Resource/ResourceManager.h"
/*! resource includes - END */

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::GlobalRenderer::Instance()___
	 * **********************************************************************
	 * Returns a reference to the GlobalRenderer singleton.
	 * **********************************************************************
	 * @return 
	 * : GlobalRenderer&
	 * : Reference to singleton.
	 * **********************************************************************
	*/
	GlobalRenderer& GlobalRenderer::Instance()
	{
		static GlobalRenderer instance;
		return instance;
	}

	/*!
	 * @brief ___JZEngine::GlobalRenderer::Initialize()___
	 * **********************************************************************
	 * Initializes the GlobalRenderer singleton and all renderers in it.
	 * **********************************************************************
	*/
	void GlobalRenderer::Initialize()
	{
		renderer_.Initialize();
		renderer_instance_.Initialize();
		renderer_debug_.Initialize();
		render_queue_.SetRenderer(&renderer_);
	}

	/*!
	 * @brief ___JZEngine::GlobalRenderer::Update(float dt)___
	 * **********************************************************************
	 * Updates all renderers.
	 * **********************************************************************
	*/
	void GlobalRenderer::Update(float dt)
	{
		UNREFERENCED_PARAMETER ( dt );
		if (resource_manager_)
		{
			// sort text data by layer
			std::sort(	renderer_text_.render_text_data_.begin(),
						renderer_text_.render_text_data_.end(),
						[] (auto const& lhs, auto const& rhs) ->bool { return lhs.layer_ < rhs.layer_; });

			// Draw everything submitted to the render queue and the text queue
			unsigned int i{ 0 };
			while (render_queue_.render_queue_.size() > 0)
			{
				const RenderQueue::RenderData& sl = render_queue_.render_queue_.top();
				while (	i < renderer_text_.render_text_data_.size() && 
						renderer_text_.render_text_data_[i].layer_ < sl.layer_)
				{
					auto const& data = renderer_text_.render_text_data_[i];
					renderer_text_.RenderText(resource_manager_, data.text_, data.x_, data.y_, data.scale_, data.color_, data.tracking_x_, data.leading_y_);
					++i;
				}
				render_queue_.DrawSprite(resource_manager_, sl.shader_id_, sl.texture_id_, sl.transform_, sl.tint_, sl.frame_, sl.rows_, sl.cols_, sl.animated_);
				render_queue_.render_queue_.pop();
			}
			while (i < renderer_text_.render_text_data_.size())
			{
				auto const& data = renderer_text_.render_text_data_[i];
				renderer_text_.RenderText(resource_manager_, data.text_, data.x_, data.y_, data.scale_, data.color_, data.tracking_x_, data.leading_y_);
				++i;
			}
			renderer_text_.render_text_data_.clear();

			// Draws all instanced objects
			renderer_instance_.Update(resource_manager_);

			// Draws all debug objects
			renderer_debug_.Update(resource_manager_);
		}
	}

	void GlobalRenderer::FrameEnd()
	{
		render_queue_.FrameEnd();
	}

	void GlobalRenderer::SetResourceManager(ResourceManager* rm)
	{
		resource_manager_ = rm;
	}

	GlobalRenderer::GlobalRenderer()
	{}
}