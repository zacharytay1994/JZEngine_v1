#pragma once
#include <JZEngine.h>
#include <string>
#include <unordered_map>

enum class MainMenuState
{
	Main,
	Options,
	Quit
};
MainMenuState current_main_menu_state = MainMenuState::Main;

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
	{ "Quit_yes",	{ "Quit_yes"		, "Quit_yes_highlight"			, "Quit_yes_clicked"}},
	{ "Quit_no",	{ "Quit_no"			, "Quit_no_highlight"			, "Quit_no_clicked"}}
};

void ToggleButton(const std::string& name, ButtonState state)
{
	Scene().GetComponent<JZEngine::Texture>(name)->texture_id_ 
		= Scene().GetTexture(button_textures[name][static_cast<int>(state)]);
}

float master_volume_{ 1.0f };
float music_volume_{ 1.0f };
float sfx_volume_{ 1.0f };
float mute_threshold{ 0.05f };

float initial_bar_scale_{ 20.0f };
float initial_bar_position_{ -128.0f };

void UpdateVolumeIcons(bool flag)
{
	if (flag)
	{
		bool master_volume = master_volume_ > 0.0f;
		bool music_volume = music_volume_ > 0.0f;
		bool sfx_volume = sfx_volume_ > 0.0f;

		Scene().EntityFlagActive("Option_master_speaker", master_volume);
		Scene().EntityFlagActive("Option_master_speaker_off", !master_volume);

		Scene().EntityFlagActive("Option_music_speaker", music_volume);
		Scene().EntityFlagActive("Option_music_speaker_off", !music_volume);

		Scene().EntityFlagActive("Option_sfx_speaker", sfx_volume);
		Scene().EntityFlagActive("Option_sfx_speaker_off", !sfx_volume);
	}
}

void UpdateVolumeSlider()
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_master_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 500.0f;
			std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold)
			{
				ratio = 1.0f;
			}
			master_volume_ = ratio;
			Scene().GetComponent<JZEngine::Transform>("Option_master_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_master_pau")->position_.x = initial_bar_position_ + ratio * 500.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_music_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 500.0f;
			std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold)
			{
				ratio = 1.0f;
			}
			music_volume_ = ratio;
			Scene().GetComponent<JZEngine::Transform>("Option_music_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_music_pau")->position_.x = initial_bar_position_ + ratio * 500.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_sfx_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 500.0f;
			std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold)
			{
				ratio = 1.0f;
			}
			sfx_volume_ = ratio;
			Scene().GetComponent<JZEngine::Transform>("Option_sfx_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_sfx_pau")->position_.x = initial_bar_position_ + ratio * 500.0f;
		}
	}
	UpdateVolumeIcons(true);
}

void ToggleOptions(bool toggle)
{
	// active/inactive option objects
	Scene().EntityFlagActive("Option_background", toggle);
	Scene().EntityFlagActive("Option_title", toggle);
	Scene().EntityFlagActive("Option_soundline", toggle);
	Scene().EntityFlagActive("Option_sound", toggle);
	Scene().EntityFlagActive("Option_master", toggle);
	Scene().EntityFlagActive("Option_music", toggle);
	Scene().EntityFlagActive("Option_sfx", toggle);
	Scene().EntityFlagActive("Option_master_speaker", toggle);
	Scene().EntityFlagActive("Option_master_speaker_off", toggle);
	Scene().EntityFlagActive("Option_music_speaker", toggle);
	Scene().EntityFlagActive("Option_music_speaker_off", toggle);
	Scene().EntityFlagActive("Option_sfx_speaker", toggle);
	Scene().EntityFlagActive("Option_sfx_speaker_off", toggle);

	Scene().EntityFlagActive("Option_master_blackbar", toggle);
	Scene().EntityFlagActive("Option_master_brownbar", toggle);
	Scene().EntityFlagActive("Option_master_pau", toggle);

	Scene().EntityFlagActive("Option_music_blackbar", toggle);
	Scene().EntityFlagActive("Option_music_brownbar", toggle);
	Scene().EntityFlagActive("Option_music_pau", toggle);

	Scene().EntityFlagActive("Option_sfx_blackbar", toggle);
	Scene().EntityFlagActive("Option_sfx_brownbar", toggle);
	Scene().EntityFlagActive("Option_sfx_pau", toggle);

	Scene().EntityFlagActive("Option_master_blackbar_border", toggle);
	Scene().EntityFlagActive("Option_music_blackbar_border", toggle);
	Scene().EntityFlagActive("Option_sfx_blackbar_border", toggle);

	Scene().EntityFlagActive("Option_x", toggle);

	// check volume icons
	UpdateVolumeIcons(toggle);
}

void ToggleQuit(bool toggle)
{
	// active/inactive option objects
	Scene().EntityFlagActive("Quit_background", toggle);
	Scene().EntityFlagActive("Quit_title", toggle);
	Scene().EntityFlagActive("Quit_yes", toggle);
	Scene().EntityFlagActive("Quit_no", toggle);
}

void UpdateMainScreen(float dt)
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_play"))
	{
		if (e->on_released_)
		{
			//Scene().ChangeScene("HawkerV2");
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
			ToggleOptions(true);
			current_main_menu_state = MainMenuState::Options;
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
			ToggleQuit(true);
			current_main_menu_state = MainMenuState::Quit;
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

void UpdateOptionsMenu(float dt)
{
	UpdateVolumeSlider(); 
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_quit_bb"))
	{
		if (e->on_released_)
		{
			ToggleOptions(false);
			current_main_menu_state = MainMenuState::Main;
		}
	}
}

void UpdateQuitMenu(float dt)
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Quit_yes_bb"))
	{
		if (e->on_released_)
		{
			ToggleQuit(false);
			current_main_menu_state = MainMenuState::Main;
		}
		if (e->on_held_)
		{
			ToggleButton("Quit_yes", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Quit_yes", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Quit_yes", ButtonState::Normal);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Quit_no_bb"))
	{
		if (e->on_released_)
		{
			ToggleQuit(false);
			current_main_menu_state = MainMenuState::Main;
		}
		if (e->on_held_)
		{
			ToggleButton("Quit_no", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Quit_no", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Quit_no", ButtonState::Normal);
		}
	}
}

void InitMainMenu()
{
	ToggleOptions(false);
	ToggleQuit(false);
}

void UpdateMainMenu(float dt)
{
	switch (current_main_menu_state)
	{
	case MainMenuState::Main:
		UpdateMainScreen(dt);
		break;
	case MainMenuState::Options:
		UpdateOptionsMenu(dt);
		break;
	case MainMenuState::Quit:
		UpdateQuitMenu(dt);
		break;
	}
}