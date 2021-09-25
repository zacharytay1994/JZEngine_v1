#include "PCH.h"
#include <ft2build.h>
#include FT_FREETYPE_H  // freetype.h

#include "TextRenderer.h"

namespace JZEngine
{
	void TextRenderer::Data ( unsigned int width, unsigned int height )
	{

		// configure VAO/VBO for texture quads
		glGenVertexArrays( 1, &va );
		glGenBuffers( 1, &vb );
		glBindVertexArray( va );
		glBindBuffer( GL_ARRAY_BUFFER, vb );
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 6 * 4, NULL, GL_DYNAMIC_DRAW );
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );

		shader_program.CompileShaderFromFile( GL_VERTEX_SHADER, "Assets/Shaders/Vertex/Font.vs" );
		shader_program.CompileShaderFromFile( GL_FRAGMENT_SHADER, "Assets/Shaders/Fragment/Font.fs" );
		shader_program.Link();

		if ( GL_FALSE == shader_program.IsLinked() )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program.GetLog() << std::endl;
			std::exit( EXIT_FAILURE );
		}
		JZEngine::Mat4f projection = JZEngine::Mat4f( JZEngine::Math::GetTransform( { static_cast< float >( width ), static_cast< float >( height ) } , 0, { 1.0f , 1.0f }, { 1.0f , 1.0f } ) );
		shader_program.SetUniform( "projection", projection );
		shader_program.SetUniform( "text", 0 );
	}

	void TextRenderer::Load( std::string font, unsigned int fontSize , unsigned int width , unsigned int height )
	{
		Data ( width , height );

		// first clear the previously loaded Characters
		Characters.clear();

		// then initialize and load the FreeType library
		FT_Library ft;
		// all functions return a value different than 0 whenever an error occurred
		if ( FT_Init_FreeType( &ft ) )
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// load font as face 
		FT_Face face;
		// FT_New_Face ( Return : FreeType error code. 0~means success.)
		if ( FT_New_Face( ft, font.c_str(), 0, &face ) )
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// set size to load glyphs as
		FT_Set_Pixel_Sizes( face, 0, fontSize );

		// disable byte-alignment restriction
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

		// then for the first 128 ASCII characters, pre-load/compile their characters and store them
		for ( GLubyte c = 0; c < 128; c++ )
		{
			// load character glyph 
			if ( FT_Load_Char( face, c, FT_LOAD_RENDER ) )
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			// generate texture
			unsigned int texture;
			glGenTextures( 1, &texture );
			glBindTexture( GL_TEXTURE_2D, texture );
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			// set texture options
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			// now store character for later use
			Character character = {
				texture,
				JZEngine::Vec2f( face->glyph->bitmap.width, face->glyph->bitmap.rows ),
				JZEngine::Vec2f( face->glyph->bitmap_left, face->glyph->bitmap_top ),
				face->glyph->advance.x
			};
			Characters.insert( std::pair<char, Character>( c, character ) );
		}
		glBindTexture( GL_TEXTURE_2D, 0 );
		// destroy FreeType once we're finished
		FT_Done_Face( face );
		FT_Done_FreeType( ft );


	}

	void TextRenderer::RenderText( std::string text, float x, float y, float scale, JZEngine::Vec3f color )
	{
		// activate corresponding render state
		shader_program.Bind();
		shader_program.SetUniform( "textColor", color );
		glActiveTexture( GL_TEXTURE0 );
		glBindVertexArray( va );

		// iterate through all characters
		std::string::const_iterator c;
		for( c = text.begin (); c != text.end (); c++ )
		{
			Character ch = Characters[ *c ];

			float xpos = x + ch.bearing_.x * scale;
			float ypos = y + ( this->Characters[ 'H' ].bearing_.y - ch.bearing_.y ) * scale;

			float w = ch.size_.x * scale;
			float h = ch.size_.y * scale;
			// update VBO for each character
			float vertices[ 6 ][ 4 ] = {
				{ xpos,     ypos + h,   0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 0.0f },

				{ xpos,     ypos + h,   0.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture ( GL_TEXTURE_2D , ch.texture_id_ );
			// update content of VBO memory
			glBindBuffer ( GL_ARRAY_BUFFER , vb );
			glBufferSubData ( GL_ARRAY_BUFFER , 0 , sizeof ( vertices ) , vertices ); // be sure to use glBufferSubData and not glBufferData
			glBindBuffer ( GL_ARRAY_BUFFER , 0 );
			// render quad
			glDrawArrays ( GL_TRIANGLES , 0 , 6 );
			// now advance cursors for next glyph
			x += ( ch.advance >> 6 ) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
		}
		glBindVertexArray ( 0 );
		glBindTexture ( GL_TEXTURE_2D , 0 );
	}

}