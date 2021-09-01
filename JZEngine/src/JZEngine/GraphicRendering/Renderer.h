#pragma once


#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <vector>

#include <string>

namespace JZEngine
{

	class Renderer
	{

		Shader shader_program ;
		

	public:
		void SetupVao ();
		void Draw ();
		void Clear ();
		void Bind ( const VertexArray& va , const IndexBuffer& ib , const Shader& shader ) const ;
	};

}