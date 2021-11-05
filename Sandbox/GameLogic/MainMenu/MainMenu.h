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

std::unordered_map<std::string, ButtonTextures> button_textures {
	{ "Play",		{ "button_play"		, "button_play_highlight"		, "button_play_clicked" } },
	{ "Options",	{ "button_options"	, "button_options_highlight"	, "button_options_clicked" } },
	{ "Credits",	{ "button_credits"	, "button_credits_highlight"	, "button_credits_clicked" } },
	{ "Quit",		{ "button_quit"		, "button_quit_highlight"		, "button_quit_clicked" } },

};

void ToggleButton(const std::string& name, ButtonState state)
{
	Scene().GetComponent<JZEngine::Texture>(name)->texture_id_ 
		= Scene().GetTexture(button_textures[name][static_cast<int>(state)]);
}

void InitMainMenu()
{
	
}

void UpdateMainMenu(float dt)
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_play"))
	{
		if (e->on_released_)
		{
			Scene().ChangeScene("HawkerV2");
		}
		if (e->on_held_)
		{
			ToggleButton("Play", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Play", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Play", ButtonState::Normal);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_options"))
	{
		if (e->on_released_)
		{
		}
		if (e->on_held_)
		{
			ToggleButton("Options", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Options", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Options", ButtonState::Normal);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_credits"))
	{
		if (e->on_released_)
		{
		}
		if (e->on_held_)
		{
			ToggleButton("Credits", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Credits", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Credits", ButtonState::Normal);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_quit"))
	{
		if (e->on_released_)
		{
		}
		if (e->on_held_)
		{
			ToggleButton("Quit", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Quit", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Quit", ButtonState::Normal);
		}
	}
}