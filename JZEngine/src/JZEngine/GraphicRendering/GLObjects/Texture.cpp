/*	__FILE HEADER__
*	File:		Texture.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Handles OpenGL textures.
*/

#include <PCH.h>

#include "Texture.h"
#include "stb_image.h"
#include "../OpenGLDebug.h"

namespace JZEngine
{
	Texture2D::Texture2D ()
		:
		renderer_id_ ( 0 ) ,
		width_ ( 0 ) ,
		height_ ( 0 ) ,
		internal_format_ ( GL_RGB ) ,
		data_format_ ( GL_RGB )
	{}

	void Texture2D::Texture2DLoad ( GLuint width , GLuint height )
	{
		width_ = width;
		height_ = height;

		internal_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;

		glCreateTextures ( GL_TEXTURE_2D , 1 , &renderer_id_ );
		glTextureStorage2D ( renderer_id_ , 1 , internal_format_ , width_ , height_ );

		glTextureParameteri ( renderer_id_ , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_MAG_FILTER , GL_NEAREST );

		glTextureParameteri ( renderer_id_ , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_BORDER );
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_BORDER );
	}

	void Texture2D::Texture2DLoad ( const std::string& path )
	{
		// load image, create texture and generate mipmaps
		int width , height , channels;
		// tell stb_image.h to flip loaded texture's on the y-axis
		stbi_set_flip_vertically_on_load ( true );

		data = stbi_load ( path.c_str () , &width , &height , &channels , 0 );
		width_ = width;
		height_ = height;

		if( channels == 4 )
		{
			// specifies the number of color components in the texture
			internal_format_ = GL_RGBA8;
			// specifies the format of the pixel data
			data_format_ = GL_RGBA;
		}
		else if( channels == 3 )
		{
			internal_format_ = GL_RGB8;
			data_format_ = GL_RGB;
		}
	}

	Texture2D::~Texture2D ()
	{}

	void Texture2D::SetData ( void* data , unsigned int size )
	{
		unsigned int bpp = data_format_ == GL_RGBA ? 4 : 3;
		bool result = size == ( width_ * height_ * bpp );
		JZ_ASSERT ( result , "Data must be entire texture!" );
		glTextureSubImage2D ( renderer_id_ , 0 , 0 , 0 , width_ , height_ , data_format_ , GL_UNSIGNED_BYTE , data );
	}

	/**
	 * @brief
	 * Binds an existing texture object to the texture unit numbered unit.
	 * @param slot
	 * Specifies the texture unit, to which the texture object should be bound to.
	*/
	void Texture2D::Bind ()
	{
		// bind textures on corresponding texture units
		glActiveTexture ( GL_TEXTURE0 );
		glBindTexture ( GL_TEXTURE_2D , renderer_id_ );
	}

	void Texture2D::Unbind ()
	{
		glBindTexture ( GL_TEXTURE_2D , 0 );
	}

	void Texture2D::FreeData ()
	{
		if( data )
			stbi_image_free ( data );
	}

	void Texture2D::InitOpenGL ()
	{
		glCheckError ();
		glGenTextures ( 1 , &renderer_id_ );
		glBindTexture ( GL_TEXTURE_2D , renderer_id_ );
		// set the texture wrapping parameters
		glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );
		// set texture filtering parameters
		glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );

		if( data )
		{
			Bind ();
			glTexImage2D ( GL_TEXTURE_2D , 0 , internal_format_ , width_ , height_ , 0 , data_format_ , GL_UNSIGNED_BYTE , data );
			glGenerateMipmap ( GL_TEXTURE_2D );
			Unbind ();
			FreeData ();
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
	}
}