#include "PCH.h"

#include "OpenGLDebug.h"
#include "TextRenderer.h"
#include "../EngineConfig.h"
#include "../Resource/ResourceManager.h"
#include "VertexBufferLayout.h"



namespace JZEngine
{
	TextRenderer::TextRenderer ()
		: vb ( sizeof ( float ) * 6 * 4 )
	{
		Data ();
	}

	void TextRenderer::Data ()
	{
		VertexBufferLayout layout;
		layout.Push<float> ( 4 );
		va.AddBuffer ( vb , layout );
		va.Unbind ();
		vb.Unbind ();
	}

	/**
	 * @brief
	 * Render line of text.
	 * To render a character, extract the corresponding Character struct of the Characters map and calculate the quad's dimensions using the character's metrics.
	 * @param text
	 * String of text that you like to render.
	 * @param x
	 * [-1, 1] OpenGL Window Coordinates
	 * Do note that (0,0) of string located at top right of the string.
	 * @param y
	 * [-1, 1] OpenGL Window Coordinates
	 * @param scale
	   Scaling dimension.
	 * @param color
	 * Default colour is white { 1.0f , 1.0f , 1.0f };
	*/
	void TextRenderer::RenderText ( std::string text , float x , float y , float scale , JZEngine::Vec3f color )
	{
		scale = scale / 10.0f;

		// activate corresponding render state
		GetSystem<ResourceManager> ()->font_shader_programs_[ 0 ].shader_program_.Bind ();
		GetSystem<ResourceManager> ()->font_shader_programs_[ 0 ].shader_program_.SetUniform ( "textColor" , color );
		va.Bind ();

		std::string::const_iterator c;

		int offset_x{ 0 };
		int offset_y{ 0 };

		int temp_offset_x{ 0 };
		//auto& test_c = GetSystem<ResourceManager> ()->font_characters_;
		auto& Characters = GetSystem<ResourceManager> ()->font_characters_[ 0 ];
		int start_x = x ;
		switch( GetAlignment () )
		{
			case Paragraph::AlignLeft:
				offset_x = 0;
				break;
			case Paragraph::AlignCenter:
				for( c = text.begin (); c != text.end (); c++ )
				{
					ResourceManager::Character ch = Characters[ *c ];
					if( *c != '\n' )
					{
						temp_offset_x += ( ch.advance >> 6 );
					}
					else
					{
						offset_x = temp_offset_x > offset_x ? temp_offset_x : offset_x;
						temp_offset_x = 0 ;
					}
				}
				offset_x = temp_offset_x > offset_x ? temp_offset_x : offset_x;
				offset_x = ( -offset_x / 2 ) * scale;
				break;
			case Paragraph::AlignRight:
				for( c = text.begin (); c != text.end (); c++ )
				{
					ResourceManager::Character ch = Characters[ *c ];
					offset_x += ( ch.advance >> 6 );
				}
				offset_x = ( -offset_x );
				break;
		}

		offset_y = static_cast < int >( -Characters[ 'H' ].size_.y / 2 * scale );

		// iterate through all characters
		for( c = text.begin (); c != text.end (); c++ )
		{
			if( *c == '\n' )
			{
				x = start_x;
				y += offset_y;
			}
			else
			{
				ResourceManager::Character ch = Characters[ *c ];

				float xpos = offset_x + x + ch.bearing_.x * scale;
				// edited (-) infront of y axis
				float ypos = offset_y + -y + ( Characters[ 'H' ].bearing_.y - ch.bearing_.y ) * scale;

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

				glActiveTexture ( GL_TEXTURE0 );
				glBindTexture ( GL_TEXTURE_2D , ch.texture_id_ );
				// update content of VBO memory

				// be sure to use glBufferSubData and not glBufferData
				vb.SetData ( vertices , sizeof ( vertices ) );
				vb.Unbind ();

				// render quad
				glDrawArrays ( GL_TRIANGLES , 0 , 6 );
				// now advance cursors for next glyph
				x += ( ch.advance >> 6 ) * scale   ; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)

			}

		}
		va.Unbind ();

		glBindTexture ( GL_TEXTURE_2D , 0 );
		glCheckError ();
	}

}