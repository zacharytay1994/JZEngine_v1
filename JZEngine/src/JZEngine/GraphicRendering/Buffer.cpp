#include <PCH.h>
#include "Buffer.h"


namespace JZEngine
{
	/////////////////////////////////////////////////////////////////////////////
	// [START] Vertex Buffer 
	VertexBuffer::VertexBuffer ( unsigned int size )
		: size_ ( size )
	{
		glGenBuffers ( 1 , &renderer_id_ );
		glBindBuffer ( GL_ARRAY_BUFFER , renderer_id_ );
		glBufferData ( GL_ARRAY_BUFFER , size , nullptr , GL_DYNAMIC_DRAW );
	}

	VertexBuffer::VertexBuffer ( float* vertices , unsigned int size )
		: size_ ( size )
	{
		glGenBuffers ( 1 , &renderer_id_ );
		glBindBuffer ( GL_ARRAY_BUFFER , renderer_id_ );
		glBufferData ( GL_ARRAY_BUFFER , size , vertices , GL_STATIC_DRAW );
	}

	VertexBuffer::VertexBuffer( const void* vertices, unsigned int size )
		: size_( size )
	{
		glGenBuffers( 1, &renderer_id_ );
		glBindBuffer( GL_ARRAY_BUFFER, renderer_id_ );
		glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
	}

	VertexBuffer::~VertexBuffer ()
	{
		glDeleteBuffers ( 1 , &renderer_id_ );
	}

	void VertexBuffer::Bind () const
	{
		glBindBuffer ( GL_ARRAY_BUFFER , renderer_id_ );
	}

	void VertexBuffer::Unbind () const
	{
		glBindBuffer ( GL_ARRAY_BUFFER , 0 );
	}

	void VertexBuffer::SetData ( const void* data , unsigned int size )
	{
		glBindBuffer ( GL_ARRAY_BUFFER , renderer_id_ );
		glBufferSubData ( GL_ARRAY_BUFFER , 0 , size , data );
	}
	// [END] VertexBuffer 
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// [START] Index Buffer
	IndexBuffer::IndexBuffer ( unsigned int* indices , unsigned int count ) 
		:
		data_ ( indices ) ,
		count_ ( count )
	{
		glGenBuffers ( 1 , &renderer_id_ );
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer ( GL_ARRAY_BUFFER , renderer_id_ );
		glBufferData ( GL_ARRAY_BUFFER , count * sizeof ( unsigned int ) , indices , GL_STATIC_DRAW );
	}

	IndexBuffer::~IndexBuffer ()
	{
		glDeleteBuffers ( 1 , &renderer_id_ );
	}

	void IndexBuffer::Bind () const
	{
		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , renderer_id_ );
	}

	void IndexBuffer::Unbind () const
	{
		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
	}
	// [END] Index Buffer
	/////////////////////////////////////////////////////////////////////////////
}