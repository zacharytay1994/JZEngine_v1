/*	__FILE HEADER__
*	File:		VertexArray.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Handles OpenGL vertex array objects.
*/

#include <PCH.h>
#include "VertexArray.h"

namespace JZEngine
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays( 1, &renderer_id_ );
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays( 1, &renderer_id_ );
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray( renderer_id_ );
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray( 0 );
	}

	void VertexArray::AddBuffer( const VertexBuffer& vb, const VertexBufferLayout& layout )
	{
		Bind();
		vb.Bind();

		const auto& elements = layout.GetElement();
		unsigned long long offset = 0;

		for ( unsigned int i = 0; i < elements.size(); ++i )
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray( i );
			glVertexAttribPointer( i, element.count, element.type, element.normalized, layout.GetStride(),
								   reinterpret_cast < const void* > ( offset ) );
			offset += ( ( unsigned long long )element.count ) * ( ( unsigned long long ) VertexBufferElement::GetSizeOfType( element.type ) );
		}
	}

	/**
	* This function is useful to bind different vertex attribute data to vao.
	 * \param index
	 * Specifies the index of the generic vertex attribute to be modified.
	 * eg.	If you like bind 3rd element , specify 2 as the binding range start from 0.
	 *		Do not that offset will be starting from 0.
	 * \param vb
	 * Include vertex data.
	 * \param layout
	 * Provide data from Vertex Buffer Element.
	 */
	void VertexArray::AddBuffer( const int index, const VertexBuffer& vb, const VertexBufferLayout& layout )
	{
		Bind();
		vb.Bind();

		const auto& elements = layout.GetElement();
		unsigned long long offset = 0;

		for ( unsigned int i = 0; i < elements.size(); ++i )
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray( i + index );
			// The initial value of offset will be starting is 0.
			// It is a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. 
			// eg. glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), ( void* )0 );
			glVertexAttribPointer( i + index, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast < const void* > ( offset ) );
			offset += ( ( unsigned long long )element.count ) * ( ( unsigned long long ) VertexBufferElement::GetSizeOfType( element.type ) );
		}
	}
}