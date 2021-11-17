#pragma once

/*! std includes - START */
#include <memory>
#include <array>
/*! std includes - END */

/*! graphics includes - START */
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
/*! graphics includes - END */

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::BaseRenderer___
	 * **********************************************************************
	 * Virtual class that all renderer type classes have to inherit from.
	 * :
	 * The base renderer class holds all vertex and index preset data in 
	 * order to draw 2D sprites.
	 * **********************************************************************
	*/
	struct BaseRenderer
	{
		using Vertices	= std::array<float, 20>;
		using Indices	= std::array<unsigned int, 6>;
	protected:
		/*!< Vertex Data */
		Vertices	vertices
		{
			// positions			// texture coords
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,			// top right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,			// bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,			// bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f			// top left 
		};

		/*!< Index Data */
		Indices		indices
		{
			// note that we start from 0!
			0, 1, 3,									// first Triangle
			1, 2, 3										// second Triangle
		};

		Shader			shader_program_;
		VertexArray		vertex_array_;
		VertexBuffer	vertex_buffer_;
		IndexBuffer		index_buffer_;

		void Initialize();
		void Draw(ResourceManager* rm);

	};
}