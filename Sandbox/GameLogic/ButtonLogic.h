/*	__FILE HEADER__
*	File:		ButtonLogic.h
	Primary:	Zachary Tay
	Date:		19/06/21
	Brief:		Button logic.
*/

#pragma once
#include <JZEngine.h>
#include <string>
#include <unordered_map>

enum class ButtonState
{
	Normal,
	Hover,
	Clicked
};

struct ButtonTextures
{
	std::string texture_names_[3];
	ButtonTextures() = default;
	ButtonTextures(const std::string& normal, const std::string& hover, const std::string& clicked)
	{
		texture_names_[0] = normal;
		texture_names_[1] = hover;
		texture_names_[2] = clicked;
	}
	std::string const& operator[](int i)
	{
		return texture_names_[i];
	}
};


//here is where the button textures are created
//{ "OBJECTNAME",		{ "exactTextureName_play}
// in the scene create a new object, type the same name, rename, add sprite and mouse event
std::unordered_map<std::string, ButtonTextures> button_textures{
	{ "Play",		{ "Play(OG)_Button_MainMenu"		, "Play(Highlight)_Button_MainMenu"		, "Play(Clicked)_Button_MainMenu" } },
	{ "Options",	{ "Options(OG)_Button_MainMenu"	, "Options(Highlight)_Button_MainMenu"	, "Options(Clicked)_Button_MainMenu" } },
	{ "Credits",	{ "Credits(OG)_Button_MainMenu"	, "Credits(Highlight)_Button_MainMenu"	, "Credits(Clicked)_Button_MainMenu" } },
	{ "how_to_play",{ "HowToPlay(OG)_Button_MainMenu", "HowToPlay(Highlight)_Button_MainMenu"  , "HowToPlay(Clicked)_Button_MainMenu"} },
	{ "Quit_Game",	{ "QuitGame(OG)_Button_MainMenu", "QuitGame(Highlight)_Button_MainMenu"	, "QuitGame(Clicked)_Button_MainMenu" } },
	{ "Quit",       { "QuitGame(OG)_Button_MainMenu", "QuitGame(Highlight)_Button_MainMenu"	, "QuitGame(Clicked)_Button_MainMenu" } },
	{ "Quit_yes",	{ "Yes(OG)_Button_MainMenu"		, "Yes(Highlight)_Button_MainMenu"			, "Yes(Clicked)_Button_MainMenu"}},
	{ "Quit_no",	{ "No(OG)_Button_MainMenu"			, "No(Highlight)_Button_MainMenu"			, "No(Clicked)_Button_MainMenu"}},
	{ "Win_restart",{ "Restart(OG)_Button_MainMenu"	, "Restart(Highlight)_Button_MainMenu"	, "Restart(Clicked)_Button_MainMenu"}},
	{ "Win_exit",	{ "Exit(OG)_Button_MainMenu"		, "Exit(Highlight)_Button_MainMenu"		, "Exit(clicked)_Button_MainMenu"}},
	{ "Skip",       { "Skip(OG)_Button_MainMenu"      , "Skip(Highlight)_Button_MainMenu"       , "Skip(Clicked)_Button_MainMenu"}},
	{ "Album_1960_button1", {"Album_photo_button_normal", "Album_photo_onhover", ""}},
	{ "Album_1960_button2", {"Album_photo_button_normal", "Album_photo_onhover", ""}}
};


void ToggleButton(const std::string& name, ButtonState state)
{
	Scene().GetComponent<JZEngine::Texture>(name)->texture_id_
		= Scene().GetTexture(button_textures[name][static_cast<int>(state)]);
}