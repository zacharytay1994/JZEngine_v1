/*	__FILE HEADER__
*	File:		Texture.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Texture2D is able to store and configure a texture in OpenGL.
				It also hosts utility functions for easy management.
*/

#pragma once

#include <glad/glad.h>
#include <string>

namespace JZEngine
{
	class Texture2D
	{
	public:
		Texture2D ();
		~Texture2D ();

		void Texture2DLoad ( GLuint width , GLuint height );
		void Texture2DLoad ( const std::string& path );

		void Bind ();
		void Unbind ();
		void FreeData ();
		void InitOpenGL ();
		void SetData ( void* data , unsigned int size );

		GLuint GetWidth () const
		{
			return width_;
		};

		GLuint GetHeight () const
		{
			return height_;
		};

		GLuint GetRendererID () const
		{
			return renderer_id_;
		}
		
		unsigned char* data{ nullptr };

		GLuint renderer_id_{};
		GLuint width_{};
		GLuint height_{};

		GLenum internal_format_{};
		GLenum data_format_{};
	};
}