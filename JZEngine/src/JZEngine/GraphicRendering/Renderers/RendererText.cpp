/*	__FILE HEADER__
*	File:		TextRenderer.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Renderer for rendering text.
*/

#include "PCH.h"

#include "../OpenGLDebug.h"
#include "RendererText.h"
#include "../../EngineConfig.h"
//#include "../../Resource/ResourceManager.h"
#include "../GLObjects/VertexBufferLayout.h"
#include "../../EngineGUI/EngineGUI.h"

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
	void TextRenderer::RenderText ( ResourceManager* rm , std::string text , float x , float y , float scale , JZEngine::Vec3f color , float tracking_x , float leading_y, Paragraph alignment )
	{
		scale = scale / 10.0f;

		// activate corresponding render state
		rm->font_shader_programs_[ 0 ].shader_program_.Bind ();
		rm->font_shader_programs_[ 0 ].shader_program_.SetUniform ( "textColor" , color );
		va.Bind ();

	
		std::queue <float> line_offset_x ;

		float offset_x{ 0 };
		float offset_y{ 0 };

		float offset_x_temp{ 0 };
		float offset_x_past{ 0 };
		float offset_x_start{ x };

		auto& Characters = rm->font_characters_[ 0 ];
		std::string::const_iterator c;

		for( c = text.begin (); c != text.end (); c++ )
		{
			ResourceManager::Character ch = Characters[ *c ];
			if( *c != '\n' )
			{
				offset_x_temp += ( ch.advance >> 6 );
			}
			else
			{
				line_offset_x.push ( offset_x_temp );
				offset_x_temp = 0 ;
			}
		}
		line_offset_x.push ( offset_x_temp );
		offset_x_temp = 0 ;

		switch( alignment )
		{
			case Paragraph::AlignLeft:
				offset_x = 0;
				break;
			case Paragraph::AlignCenter:
				if( line_offset_x.empty () )
				{
					x = -( offset_x_temp / 2.0f ) * scale ;
				}
				else
				{
					x = -( line_offset_x.front () / 2.0f ) * scale ;
					line_offset_x.pop ();
				}
				break;
			case Paragraph::AlignRight:
				if( line_offset_x.empty () )
				{
					x = -offset_x_temp * scale ;
				}
				else
				{
					x = -line_offset_x.front () * scale ;
					offset_x_past = x ;
					line_offset_x.pop ();
				}
				break;
		}

		offset_y = -Characters[ 'H' ].size_.y / 2 * scale ;

		// iterate through all characters
		for( c = text.begin (); c != text.end (); c++ )
		{
			if( *c == '\n' )
			{
				switch( alignment )
				{
					case Paragraph::AlignLeft:
						x = offset_x_start;
						break;
					case Paragraph::AlignCenter:
						if( !line_offset_x.empty () )
						{
							x = -( line_offset_x.front () / 2.0f ) * scale ;
							line_offset_x.pop ();
						}
						else
						{
							x = offset_x_start;
						}
						break;
					case Paragraph::AlignRight:
						if( !line_offset_x.empty () )
						{
							x = -line_offset_x.front () * scale ;
							offset_x_past = x;
							line_offset_x.pop ();
						}
						else
						{
							x = ( offset_x_past + offset_x_start ) / 2.0f;
						}

						break;

				}


				y += offset_y * leading_y;
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

				JZEngine::Mat3f camwin_to_ndc_xform =
				{
					{2.0f / Settings::camera_width, 0.0f, 0.0f},
					{0.0f, -2.0f / Settings::camera_height, 0.0f},
					{0.0f, 0.0f, 1.0f}
				};

				Mat3f cam_transform = EngineGUI::GetCameraTransform ();
				// need to invert y for some reason, mysterious

				cam_transform[ 1 ][ 2 ] *= -1;

				rm->font_shader_programs_[ 0 ].shader_program_.SetUniform ( "projection" , ( camwin_to_ndc_xform * cam_transform ).Transpose () );
				// render quad

				glDrawArrays ( GL_TRIANGLES , 0 , 6 );
				// now advance cursors for next glyph
				x += ( ch.advance >> 6 ) * scale * tracking_x  ; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)

			}

		}
		va.Unbind ();
		glBindTexture ( GL_TEXTURE_2D , 0 );
		glCheckError ();
	}

}