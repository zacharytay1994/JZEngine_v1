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
#include "RendererText.h"
#include "RenderQueue.h"
/*! graphics includes - END */

/*! engine includes - START */
#include "../../Math/JZMath.h"
#include "../../DebugTools/Assert.h"
/*! engine includes - END */

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

	struct ShaderManager
	{
		/*! SHADER TYPES 
			- Shader types are structs that holds the uniform structure for various shaders.
		*/
		struct DefaultShaderUniforms
		{
			Mat3f transform_;
			Vec4f tint_;
			float time_;
		};

		struct AnotherShaderUniform
		{
			Mat3f transform_;
			float ft;
		};

		template <typename SHADERTYPE>
		static std::vector<SHADERTYPE> shader_container_;

		template <typename SHADERTYPE>
		int RegisterShaderUniform()
		{
			shader_container_<SHADERTYPE>.emplace_back();
			return shader_container_<SHADERTYPE>.size() - 1;
		}

		template <typename SHADERTYPE>
		SHADERTYPE& GetShaderUniform(int i)
		{
			JZ_ASSERT((i < shader_container_<SHADERTYPE>.size()), "Accessing shader uniform out of bounds.") (i);
			return shader_container_<SHADERTYPE>[i];
		}
	};
}