#pragma once



#include "../Math/JZMath.h"
#include "Shader.h"
#include <map>

namespace JZEngine
{
	// Holds all state information relevant to a character as loaded using FreeType
	struct Character
	{
		unsigned int        texture_id_{ 0 };		// ID handle of the glyph texture
		JZEngine::Vec2f     size_{ 1.0f , 1.0f };	// size of glyph
		JZEngine::Vec2f		bearing_{ 0.0f,0.0f };	// offset from baseline to left/top of glyph
		unsigned int		advance{ 0 };		// horizontal offset to advance to next glyph
	};


	// A renderer class for rendering text displayed by a font loaded using the 
	// FreeType library. A single font is loaded, processed into a list of Character
	// items for later rendering.
	class TextRenderer
	{
	public:
		// holds a list of pre-compiled Characters
		std::map<char , Character> Characters;
		// shader used for text rendering
		Shader shader_program;
		void Data ( unsigned int width , unsigned int height );
		// pre-compiles a list of characters from the given font
		void Load ( std::string font , unsigned int fontSize , unsigned int width , unsigned int height );
		// renders a string of text using the precompiled list of characters
		void RenderText ( std::string text , float x , float y , float scale , JZEngine::Vec3f color = { 1.0f , 1.0f , 1.0f } );
		
	private:
		// render state
		unsigned int va{} , vb{};
	};

}
