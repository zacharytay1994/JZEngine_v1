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

std::unordered_map<std::string, ButtonTextures> button_textures{
	{ "Play",		{ "button_play"		, "button_play_highlight"		, "button_play_clicked" } },
	{ "Options",	{ "button_options"	, "button_options_highlight"	, "button_options_clicked" } },
	{ "Credits",	{ "button_credits"	, "button_credits_highlight"	, "button_credits_clicked" } },
	{ "how_to_play",{ "button_HowToPlay", "button_HowToPlay_highlight"  , "button_HowToPlay_clicked"} },
	{ "Quit_Game",	{ "button_quit_game", "button_quit_game_highlight"	, "button_quit_game_clicked" } },
	{ "Quit",       { "button_quit"     , "button_quit_highlight"       , "button_quit_clicked" } },
	{ "Quit_yes",	{ "Quit_yes"		, "Quit_yes_highlight"			, "Quit_yes_clicked"}},
	{ "Quit_no",	{ "Quit_no"			, "Quit_no_highlight"			, "Quit_no_clicked"}},
	{ "Win_restart",{ "button_restart"	, "button_restart_highlight"	, "button_restart_clicked"}},
	{ "Win_exit",	{ "button_exit"		, "button_exit_highlight"		, "button_exit_clicked"}},
	{ "Skip",       { "cs_Skip"         , "cs_Skip_highlight"           , "cs_Skip_clicked"}},
	{ "Album_1960_button1", {"Album_photo_button_normal", "Album_photo_onhover", ""}},
	{ "Album_1960_button2", {"Album_photo_button_normal", "Album_photo_onhover", ""}}
};

void ToggleButton(const std::string& name, ButtonState state)
{
	Scene().GetComponent<JZEngine::Texture>(name)->texture_id_
		= Scene().GetTexture(button_textures[name][static_cast<int>(state)]);
}