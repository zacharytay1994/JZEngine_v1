#pragma once


#include "../GlobalSystems.h"
#include "../Resource/ResourceManager.h"
#include "../EngineConfig.h"
#include "Shader.h"
#include "Texture.h"


namespace JZEngine
{
	class PostProcessor 
	{
	public:

		ResourceManager* resource_manager_{ nullptr };

		// state
		Shader shader_program_;
		Texture2D texture_;
		unsigned int width_{ 0 };
		unsigned int height_{ 0 };

		// options
		bool confuse_{ false };
		bool chaos_{ false };
		bool shake_{ false };

		//static PostProcessor& GetInstance ()
		//{
		//	static PostProcessor instance ;
		//	return instance;
		//};




		void Init ( unsigned int width , unsigned int height );
		// prepares the postprocessor's framebuffer operations before rendering the game
		void Bind ();
		// should be called after rendering the game, so it stores all the rendered data into a texture object
		void Unbind ();
		// renders the PostProcessor texture quad (as a screen-encompassing large sprite)
		void Render ( float time );
	private:

		// render state
		unsigned int MSFBO , FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
		unsigned int RBO; // RBO is used for multisampled color buffer
		unsigned int VAO;
		// initialize quad for rendering postprocessing texture
		void initRenderData ();
	};

}