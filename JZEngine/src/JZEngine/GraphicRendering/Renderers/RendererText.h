/*	__FILE HEADER__
*	File:		TextRenderer.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Renderer for rendering text.
*/

#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  // freetype.h

#include <map>

#include "../../Math/JZMath.h"
#include "../GLObjects/VertexArray.h"
#include "../GLObjects/Buffer.h"
#include "../GLObjects/Shader.h"
#include "../../Resource/ResourceManager.h"

//struct ResourceManager;
namespace JZEngine
{
	// Holds all state information relevant to a character as loaded using FreeType
	struct Character
	{
		FT_Face				face_{};
		unsigned int        texture_id_{ 0 };		// ID handle of the glyph texture
		JZEngine::Vec2f     size_{ 1.0f , 1.0f };	// size of glyph
		JZEngine::Vec2f		bearing_{ 0.0f,0.0f };	// offset from baseline to left/top of glyph
		unsigned int		advance{ 0 };			// horizontal offset to advance to next glyph
	};


	enum class Paragraph
	{
		AlignLeft , AlignCenter , AlignRight /*, JustifyLeft , JustifyCenter , JustifyRight , JustifyFull*/
	};

	// A renderer class for rendering text displayed by a font loaded using the 
	// FreeType library. A single font is loaded, processed into a list of Character
	// items for later rendering.
	struct TextRenderer
	{
		TextRenderer ();
		// holds a list of pre-compiled Characters
		//std::map<char , Character> Characters;
		// shader used for text rendering
		void Data ();
		// pre-compiles a list of characters from the given font
		//void Load ( std::string font , unsigned int fontSize );
		// renders a string of text using the precompiled list of characters
		void RenderText
		(
			ResourceManager* rm,
			std::string text ,
			float x ,
			float y ,
			float scale ,
			JZEngine::Vec3f color = { 1.0f , 1.0f , 1.0f } ,
			float tracking_x = { 1.0f },
			float leading_y = { 2.0f }
		);

		struct RenderTextData
		{
			int layer_;
			std::string text_;
			float x_;
			float y_;
			float scale_;
			Vec3f color_;
			float tracking_x_;
			float leading_y_;
			RenderTextData(int layer, const std::string& text, float x, float y, float scale, const Vec3f color, float tracking_x, float leading_y)
				:
				layer_(layer),
				text_(text),
				x_(x),
				y_(y),
				scale_(scale),
				color_(color),
				tracking_x_(tracking_x),
				leading_y_(leading_y)
			{}
		};
		std::vector<RenderTextData> render_text_data_;

		void RenderTextQueue(
			int layer,
			std::string text,
			float x,
			float y,
			float scale,
			JZEngine::Vec3f color = { 1.0f , 1.0f , 1.0f },
			float tracking_x = { 1.0f },
			float leading_y = { 2.0f })
		{
			render_text_data_.emplace_back(layer, text, x, y, scale, color, tracking_x, leading_y);
		}

		void Update(ResourceManager* rm)
		{
			for (auto& data : render_text_data_)
			{
				RenderText(rm, data.text_, data.x_, data.y_, data.scale_, data.color_, data.tracking_x_, data.leading_y_);
			}
			render_text_data_.clear();
		}

		void Alignment ( Paragraph aligment = Paragraph::AlignLeft )
		{
			aligning_text_ = aligment;
		};

		Paragraph GetAlignment ()
		{
			return aligning_text_;
		};

		// render state
		Shader shader_program;
		VertexArray va ;
		VertexBuffer vb;

		float text_width_{};
		float text_height_{};
		int scaled_kerning_{ 100 } ;
		Paragraph aligning_text_{ Paragraph::AlignCenter };

	};

}
