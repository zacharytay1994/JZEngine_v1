#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  // freetype.h

#include <map>

#include "../Math/JZMath.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "../GlobalSystems.h"

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
	struct TextRenderer : public GlobalSystem
	{
		TextRenderer ();
		// holds a list of pre-compiled Characters
		//std::map<char , Character> Characters;
		// shader used for text rendering
		void Data ();
		// pre-compiles a list of characters from the given font
		//void Load ( std::string font , unsigned int fontSize );
		// renders a string of text using the precompiled list of characters
		void RenderText ( std::string text , float x , float y , float scale , JZEngine::Vec3f color = { 1.0f , 1.0f , 1.0f } , float leading = { 1.0f } );

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
