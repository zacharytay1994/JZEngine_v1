#pragma once

#include <string>

#include "../GraphicRendering/Buffer.h"
#include "../GraphicRendering/Shader.h"
#include "../GraphicRendering/Texture.h"
#include "../GraphicRendering/VertexArray.h"


namespace JZEngine
{
	class LoadScreenMain
	{
	private:

		/*set up vertex data ( and buffer ( s ) ) and configure vertex attributes
			------------------------------------------------------------------*/
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

		std::string fspath{ "Assets/Shaders/Fragment/FS_BasicTex.fs" };
		std::string vspath{ "Assets/Shaders/Vertex/VS_BasicTex.vs" };
		std::string texpath1{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-01.png" };
		std::string texpath2{ "Assets/Textures/LoadingScreen/Jump0_BlackLogo-02.png" };

		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		Shader shader_program;
		Texture2D tex2d_path1;
		Texture2D tex2d_path2;

	public:

		LoadScreenMain ();
		void Draw ();
		bool DrawLoadScreenMain{ true };

	};
}