#pragma once

#include "Buffer.h"
#include "VertexBufferLayout.h"

namespace JZEngine
{
	class VertexArray
	{
	private:
		unsigned int renderer_id_{ 0 };

	public:
		VertexArray ();
		~VertexArray ();

		void Bind () const;
		void Unbind () const ;

		void AddBuffer ( const VertexBuffer& vb , const VertexBufferLayout& layout );
	};
}