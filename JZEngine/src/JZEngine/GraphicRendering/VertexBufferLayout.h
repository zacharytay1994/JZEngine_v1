/*	__FILE HEADER__
*	File:		VertexBufferLayout.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Handles OpenGL vertex buffer layouts.
*/

#pragma once

#include <glad/glad.h>
#include <vector>
#include "../DebugTools/Assert.h"

namespace JZEngine
{
	struct VertexBufferElement
	{
		unsigned int type ;
		unsigned int count ;
		unsigned char normalized ;

		static unsigned int GetSizeOfType ( unsigned int type )
		{
			switch( type )
			{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4 ;
				case GL_UNSIGNED_BYTE: return 1 ;
				default: return 0 ;
			}
			JZ_ASSERT ( false , "VertexBufferElement" )( type );
			return 0 ;
		}
	};


	class VertexBufferLayout
	{
	private:

		std::vector < VertexBufferElement> m_element ;
		unsigned int m_stride{ 0 };

	public:

		VertexBufferLayout ()
			: m_stride ( 0 )
		{};


		template <typename T > void Push ( unsigned int count );

		template <> void Push <float> ( unsigned int count )
		{
			m_element.push_back ( { GL_FLOAT, count , GL_FALSE } );
			m_stride += count * VertexBufferElement::GetSizeOfType ( GL_FLOAT );
		}

		template <> void Push <unsigned int> ( unsigned int count )
		{
			m_element.push_back ( { GL_UNSIGNED_INT, count , GL_FALSE } );
			m_stride += count * VertexBufferElement::GetSizeOfType ( GL_UNSIGNED_INT );
		}

		template <> void Push <unsigned char> ( unsigned int count )
		{
			m_element.push_back ( { GL_UNSIGNED_BYTE, count , GL_TRUE } );
			m_stride += count * VertexBufferElement::GetSizeOfType ( GL_UNSIGNED_BYTE );
		}

		inline const std::vector < VertexBufferElement > GetElement () const
		{
			return m_element;
		}

		inline unsigned int GetStride () const
		{
			return  m_stride;
		}
	};

}