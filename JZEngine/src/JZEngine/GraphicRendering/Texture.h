#pragma once

#include <string>

namespace JZEngine
{
	class Texture2D
	{
	public:
		Texture2D( GLuint width, GLuint height );
		Texture2D( const std::string& path );
		~Texture2D();

		void SetData( void* data, unsigned int size );
		void Bind( unsigned int slot = 0 );

		GLuint GetWidth() const
		{
			return width_;
		};

		GLuint GetHeight() const
		{
			return height_;
		};

		GLuint GetRendererID() const
		{
			return renderer_id_;
		}


	private:

		GLuint renderer_id_{};
		GLuint width_{};
		GLuint height_{};
		std::string path_{};
		GLenum internal_format_{};
		GLenum data_format_{};
	};
}