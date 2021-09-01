#include <PCH.h>
#include "stb_image.h"
#include "Texture.h"

#include <glad/glad.h>

namespace JZEngine
{
	Texture2D::Texture2D ( GLuint width , GLuint height )
		:
		width_ ( width ) ,
		height_ ( height )
	{
		internal_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;

		glCreateTextures ( GL_TEXTURE_2D , 1 , &renderer_id_ );
		glTextureStorage2D ( renderer_id_ , 1 , internal_format_ , width_ , height_ );

		glTextureParameteri ( renderer_id_ , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_MAG_FILTER , GL_NEAREST );

		glTextureParameteri ( renderer_id_ , GL_TEXTURE_WRAP_S , GL_REPEAT );
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_WRAP_T , GL_REPEAT );
	}

	Texture2D::Texture2D ( const std::string& path )
		:
		path_ ( path )
	{
		int width{} , height{} , channels{};
		stbi_set_flip_vertically_on_load ( 1 );
		stbi_uc* data = nullptr;
		{
			//HZ_PROFILE_SCOPE ( "stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)" );
			data = stbi_load ( path.c_str () , &width , &height , &channels , 0 );
		}
		width_ = width ;
		height_ = height;


		GLenum internalFormat = 0 , dataFormat = 0;
		if( channels == 4 )
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if( channels == 3 )
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		internal_format_ = internalFormat;
		data_format_ = dataFormat;

		//HZ_CORE_ASSERT ( internalFormat & dataFormat , "Format not supported!" );

		glCreateTextures ( GL_TEXTURE_2D , 1 , &renderer_id_ );
		glTextureStorage2D ( renderer_id_ , 1 , internalFormat , width_ , height_ );

		// setting data parameter
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_MAG_FILTER , GL_NEAREST );

		glTextureParameteri ( renderer_id_ , GL_TEXTURE_WRAP_S , GL_REPEAT );
		glTextureParameteri ( renderer_id_ , GL_TEXTURE_WRAP_T , GL_REPEAT );

		glTextureSubImage2D ( renderer_id_ , 0 , 0 , 0 , width_ , height_ , dataFormat , GL_UNSIGNED_BYTE , data );

		stbi_image_free ( data );
	}

	Texture2D::~Texture2D ()
	{
		glDeleteTextures ( 1 , &renderer_id_ );
	}

	void Texture2D::SetData ( void* data , unsigned int size )
	{}

	void Texture2D::Bind ( unsigned int slot  )
	{
		glBindTextureUnit ( slot , renderer_id_ );
	}
}