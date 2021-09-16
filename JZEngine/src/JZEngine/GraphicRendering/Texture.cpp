#include <PCH.h>

#include "stb_image.h"
#include "Texture.h"


namespace JZEngine
{
	Texture2D::Texture2D()
		:
		renderer_id_( 0 ),
		width_( 0 ),
		height_( 0 ),
		internal_format_( GL_RGB ),
		data_format_( GL_RGB )
	{}

	void Texture2D::Texture2DLoad( GLuint width, GLuint height )
	{
		width_ = width;
		height_ = height;

		internal_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;

		glCreateTextures( GL_TEXTURE_2D, 1, &renderer_id_ );
		glTextureStorage2D( renderer_id_, 1, internal_format_, width_, height_ );

		glTextureParameteri( renderer_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTextureParameteri( renderer_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTextureParameteri( renderer_id_, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTextureParameteri( renderer_id_, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture2D::Texture2DLoad( const std::string& path )
	{
		path_ = path;

		//int width{}, height{}, channels{};
		//stbi_set_flip_vertically_on_load( 1 );
		//stbi_uc* data = nullptr;
		//{
		//	data = stbi_load( path.c_str(), &width, &height, &channels, 0 );
		//}
		//if ( data == nullptr )
		//{
		//	std::cout << "Failed to load texture" << std::endl;
		//}
		//width_ = width;
		//height_ = height;


		//GLenum internalFormat = 0, dataFormat = 0;
		//if ( channels == 4 )
		//{
		//	internalFormat = GL_RGBA8;
		//	dataFormat = GL_RGBA;
		//}
		//else if ( channels == 3 )
		//{
		//	internalFormat = GL_RGB8;
		//	dataFormat = GL_RGB;
		//}

		//internal_format_ = internalFormat;
		//data_format_ = dataFormat;
	

		//glCreateTextures( GL_TEXTURE_2D, 1, &renderer_id_ );
		//int i = 0;
		//glTextureStorage2D( renderer_id_, 1, internalFormat, width_, height_ );

		//// setting data parameter
		//glTextureParameteri( renderer_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		//glTextureParameteri( renderer_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		//glTextureParameteri( renderer_id_, GL_TEXTURE_WRAP_S, GL_REPEAT );
		//glTextureParameteri( renderer_id_, GL_TEXTURE_WRAP_T, GL_REPEAT );

		//glTextureSubImage2D( renderer_id_, 0, 0, 0, width_, height_, dataFormat, GL_UNSIGNED_BYTE, data );

		//stbi_image_free( data );

		glGenTextures( 1, &renderer_id_ );
		glBindTexture( GL_TEXTURE_2D, renderer_id_ );
		// set the texture wrapping parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		// set texture filtering parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// unbind texture
		//glBindTexture( GL_TEXTURE_2D, 0 );

		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load( true ); // tell stb_image.h to flip loaded texture's on the y-axis.
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char* data = stbi_load( path.c_str(), &width, &height, &nrChannels, 0 );
		if ( data )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
			glGenerateMipmap( GL_TEXTURE_2D );
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free( data );
	}

	Texture2D::~Texture2D()
	{
		//glDeleteTextures( 1, &this->renderer_id_ );
	}

	void Texture2D::SetData( void* data, unsigned int size )
	{}

	/**
	 * @brief
	 * Binds an existing texture object to the texture unit numbered unit.
	 * @param slot
	 * Specifies the texture unit, to which the texture object should be bound to.
	*/
	void Texture2D::Bind( unsigned int slot )
	{
		//glBindTextureUnit( slot, renderer_id_ );
		 // bind textures on corresponding texture units
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, this->renderer_id_ );
	}
}