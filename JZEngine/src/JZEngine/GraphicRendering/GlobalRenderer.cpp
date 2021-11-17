#include <PCH.h>
#include "GlobalRenderer.h"

/*! graphics includes - START */
/*! graphics includes - END */

/*! resource includes - START */
#include "../Resource/ResourceManager.h"
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
		if (resource_manager_)
		{
			// renders all instanced objects
			render_queue_.Update(resource_manager_);
			renderer_instance_.Draw(resource_manager_);
			renderer_debug_.Update(resource_manager_, dt);
			renderer_text_.Update(resource_manager_, dt);
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