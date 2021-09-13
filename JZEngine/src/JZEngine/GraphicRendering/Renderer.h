#pragma once

#include <array>
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

namespace JZEngine
{
	enum RenderingMode
	{
		Instancing,
	};

	class Renderer
	{
	private :

		/*set up vertex data ( and buffer ( s ) ) and configure vertex attributes
			------------------------------------------------------------------*/

		std::array < float, 12 > vertices
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		std::array < unsigned int, 6 > indices
		{  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		Shader shader_program;
		VertexArray va;
		IndexBuffer ib;
	
		Renderer();


	public:
		static Renderer& Instance()
		{
			static Renderer Instance;
			return Instance;
		};
		void Init();
		void Draw();
		void Clear();
		void Bind( const VertexArray& va, const IndexBuffer& ib, const Shader& shader ) const;
	};


}