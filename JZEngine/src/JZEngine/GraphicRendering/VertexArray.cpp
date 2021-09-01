#include <PCH.h>
#include "VertexArray.h"

namespace JZEngine
{
	VertexArray::VertexArray ()
	{
		glGenVertexArrays ( 1 , &renderer_id_ );
	}

	VertexArray::~VertexArray ()
	{
		glDeleteVertexArrays ( 1 , &renderer_id_ );
	}

	void VertexArray::Bind () const
	{
		glBindVertexArray ( renderer_id_ ) ;
	}

	void VertexArray::Unbind () const
	{
		glBindVertexArray ( 0 ) ;
		
	}

	void VertexArray::AddBuffer ( const VertexBuffer& vb , const VertexBufferLayout& layout )
	{
		Bind ();
		vb.Bind ();

		const auto& elements = layout.GetElement ();
		unsigned long long offset = 0 ;

		for( unsigned int i = 0 ; i < elements.size () ; ++i )
		{
			const auto& element = elements[ i ];
			glEnableVertexAttribArray ( i ) ;
			glVertexAttribPointer ( i , element.count , element.type , element.normalized , layout.GetStride () ,
									reinterpret_cast < const void* > ( offset ) ) ;
			offset += ( ( unsigned long long )element.count ) * ( ( unsigned long long ) VertexBufferElement::GetSizeOfType ( element.type ) ) ;
		}
	}
}