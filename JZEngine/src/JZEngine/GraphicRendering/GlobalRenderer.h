#pragma once

/*! std includes - START */
#include <memory>
#include <array>
#include <vector>
/*! std includes - END */

/*! graphics includes - START */
#include "Renderer.h"
#include "RendererInstancing.h"
#include "RendererDebug.h"
#include "TextRenderer.h"
#include "RenderQueue.h"
/*! graphics includes - END */

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::GlobalRenderer___
	 * **********************************************************************
	 * Global renderer singleton, encapsulating all rendering functionality.
	 * **********************************************************************
	*/
	struct ResourceManager;
	struct GlobalRenderer
	{
		/*! MEMBER DATA */
		
		Renderer			renderer_;
		RendererInstancing	renderer_instance_;
		RendererDebug		renderer_debug_;
		TextRenderer		renderer_text_;
		RenderQueue			render_queue_;

		/*! MEMBER FUNCTIONS */

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
		static GlobalRenderer& Instance();

		/*!
		 * @brief ___JZEngine::GlobalRenderer::Initialize()___
		 * **********************************************************************
		 * Initializes the GlobalRenderer singleton and all renderers in it.
		 * **********************************************************************
		*/
		void Initialize();

		/*!
		 * @brief ___JZEngine::GlobalRenderer::Update(float dt)___
		 * **********************************************************************
		 * Updates all renderers.
		 * **********************************************************************
		*/
		void Update(float dt);

		/*!
		 * @brief ___JZEngine::GlobalRenderer::FrameEnd()___
		 * **********************************************************************
		 * Called at the end of every frame.
		 * **********************************************************************
		*/
		void FrameEnd();

		void SetResourceManager(ResourceManager* rm);

	private:
		ResourceManager* resource_manager_{ nullptr };

		GlobalRenderer();
	};
}