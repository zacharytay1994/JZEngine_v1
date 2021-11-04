/*	__FILE HEADER__
*	File:		Buffer.h
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		OpenGL vertex buffer wrapper.
				Vertex buffer and Index buffer are stored here.
*/

#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>

#include "VertexBufferLayout.h"

namespace JZEngine
{
	class VertexBuffer
	{
	public:

		VertexBuffer ( unsigned int size );
		VertexBuffer ( float* vertices , unsigned int size );
		VertexBuffer ( const void* vertices , unsigned int size );

		~VertexBuffer ();

		void Bind () const;
		void Unbind () const;

		void SetData ( const void* data , unsigned int size );

		const VertexBufferLayout& GetLayout () const
		{
			return layout_;
		}
		void SetLayout ( const VertexBufferLayout& layout )
		{
			layout_ = layout;
		}

		unsigned int GetRendererId ()
		{
			return renderer_id_;
		}

	private:
		unsigned int renderer_id_{ 0 };
		unsigned int size_{};
		VertexBufferLayout layout_{};
	};

	class IndexBuffer
	{
	private:
		unsigned int renderer_id_{};
		unsigned int count_{};
		const unsigned int* data_{ nullptr };

	public:
		IndexBuffer ( unsigned int* indices , unsigned int count );
		~IndexBuffer ();

		void Bind () const;
		void Unbind () const;

		inline const unsigned int* GetData () const
		{
			return data_;
		}

		unsigned int GetCount () const
		{
			return count_;
		}
	};
}