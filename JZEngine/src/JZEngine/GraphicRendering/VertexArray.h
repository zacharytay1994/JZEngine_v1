/*	__FILE HEADER__
*	File:	VertexArray.h
	Author: JZ
	Date:	01/07/21
	Brief:	For user to pass in data to render a sprite or picture.
*/

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
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddBuffer( const VertexBuffer& vb, const VertexBufferLayout& layout );
		void AddBuffer( const int index , const VertexBuffer& vb, const VertexBufferLayout& layout );
	};
}