#pragma once


#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

namespace JZEngine
{
	class Renderer
	{
		/*set up vertex data ( and buffer ( s ) ) and configure vertex attributes
			------------------------------------------------------------------*/
		float vertices [12] 
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		unsigned int indices [6] 
		{  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		Shader shader_program ;
		VertexArray va ;
		IndexBuffer ib ;
		VertexBuffer vb ;


		Renderer ();

	public:
		static Renderer& Instance ()
		{
			static Renderer Instance ;
			return Instance;
		};
		void Init ();
		void Draw ();
		void Clear ();
		void Bind ( const VertexArray& va , const IndexBuffer& ib , const Shader& shader ) const ;
	};


}