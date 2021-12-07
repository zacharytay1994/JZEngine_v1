/*	__FILE HEADER__
*	File:		LSMain.h
	Primary:	Jee Jia Min
	Date:		24/11/21
	Brief:		Jump Zero loading screen during the startup of the engine .
*/

#pragma once

#include "../GLObjects/Buffer.h"
#include "../GLObjects/Shader.h"
#include "../GLObjects/Texture.h"
#include "../GLObjects/VertexArray.h"
#include <memory>

// Uncomment the following define for debugging
#define LSMainDebug 

namespace JZEngine
{
	struct ResourceManager;
	struct TextRenderer;

	class LSMain
	{
	private:
		// set up vertex data ( and buffer ( s ) ) and configure vertex attributes
		std::array < float , 20 > vertices
		{
			// positions         // texture coords
		   1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // top right
		   1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom right
		  -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom left
		  -1.0f,  1.0f, 0.0f,  0.0f, 1.0f  // top left 

		};

		std::array < unsigned int , 6 > indices
		{  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		Shader shader_program;
		Texture2D tex2d_path1;
		Texture2D tex2d_path2;
		Texture2D tex2d_path3;
		Texture2D tex2d_path4;

		bool reverse_dot_{ false };
		float dot_1_alpha_{ 1.0f };
		float dot_2_alpha_{ 0.0f };
		float dot_3_alpha_{ 0.0f };

		// Initialised Data
		std::string fspath{ "Assets/Shaders/Fragment/FS_BasicTex.fs" };
		std::string vspath{ "Assets/Shaders/Vertex/VS_BasicTex.vs" };
		std::string texpath1{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-01.png" };
		std::string texpath2{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-02.png" };
		std::string texpath3{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-03.png" };
		std::string texpath4{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-04.png" };

		ResourceManager* resource_manager_{ nullptr };
		std::unique_ptr< TextRenderer> renderer_text_{ nullptr };

		int window_width_;
		int window_height_;
	public:
		LSMain ( ResourceManager* ResourceManager );
		~LSMain ();
		void PreDraw ();
		void DrawLoadingScreen ( std::string Information , double DeltaTime) ;
		void DrawExitScreen ();
		void DrawFadeOut ();
		void PostDraw ();
	};
}