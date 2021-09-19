/*	__FILE HEADER__
*	File:	RendererInstancing.h
	Author: JZ
	Date:	01/07/21
	Brief:	Instancing is a technique where we draw many (equal mesh data) object
			at once with a single render call, saving us all the CPU -> GPU
			communications each time we need to render an object.
*/

#pragma once


#include <array>
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

namespace JZEngine
{
	class RendererInstancing
	{
		Shader shader_program;
		VertexArray va;

		RendererInstancing();

		std::array <float, 30 >vertices
		{
			// positions     // colors
			-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
			 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
			-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

			-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
			 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
			 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
		};

	public:

		static RendererInstancing& Instance()
		{
			static RendererInstancing Instance;
			return Instance;
		};

		void Init();
		void Draw();
		void Bind();
		void Unbind();

		Shader GetShaderProgram();
	};

}

