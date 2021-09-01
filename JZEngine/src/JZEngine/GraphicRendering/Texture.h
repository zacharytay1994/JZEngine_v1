#pragma once

#include <string>

namespace JZEngine
{
	class Texture2D
	{
	public:
		Texture2D ( GLuint width , GLuint height );
		Texture2D ( const std::string& path );
		~Texture2D ();

		void SetData ( void* data , unsigned int size );
		void Bind ( unsigned int slot = 0 );

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


	private:

		std::string path_{};
		GLuint width_{};
		GLuint height_{};
		GLuint renderer_id_{};
		GLenum internal_format_ , data_format_;
	};
}