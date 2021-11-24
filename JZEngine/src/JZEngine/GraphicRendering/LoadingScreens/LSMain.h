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

// Uncomment the following define for debugging
#define LSMainDebug 

namespace JZEngine
{
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

		bool draw_load_screen_{ true };
		float myAlpha{ 0.0f };

		std::string fspath{ "Assets/Shaders/Fragment/FS_BasicTex.fs" };
		std::string vspath{ "Assets/Shaders/Vertex/VS_BasicTex.vs" };
		std::string texpath1{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-01.png" };
		std::string texpath2{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-02.png" };

	public:
		LSMain ();
		~LSMain ();
		void PreDraw ();
		void Draw () ;
		void PostDraw ();
	};
}