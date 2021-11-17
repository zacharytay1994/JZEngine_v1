/*	__FILE HEADER__
*	File:		MainMenu.h
	Primary:	Zachary Tay
	Date:		19/06/21
	Brief:		Main Menu logic.
*/

#pragma once
#include <JZEngine.h>
#include <string>
#include <unordered_map>

#include "../ButtonLogic.h"


enum class MainMenuState
{
	Main,
	Options,
	Credits,
	Quit
};
MainMenuState current_main_menu_state = MainMenuState::Main;

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
			ratio = std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold)
			{
				ratio = 1.0f;
			}
			master_volume_ = ratio;
			
			//JZEngine::global_systems_->GetSystem<SoundSystem>()->setMastervolume(master_volume_);
			
			Scene().GetSoundSystem()->setMasterVolume(master_volume_);
			Scene().GetComponent<JZEngine::Transform>("Option_master_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_master_pau")->position_.x = initial_bar_position_ + ratio * 500.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_music_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 500.0f;
			ratio = std::clamp(ratio, 0.0f, 1.0f);
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
			ratio = std::clamp(ratio, 0.0f, 1.0f);
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

void ToggleCredits(bool toggle)
{
	// active/inactive option objects
	Scene().EntityFlagActive("Credits_background", toggle);
	Scene().EntityFlagActive("Credits_x", toggle);
}

void UpdateMainScreen(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_play"))
	{
		if (e->on_released_)
		{
			Scene().ChangeScene("CutScene");
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
			ToggleCredits(true);
			current_main_menu_state = MainMenuState::Credits;
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
	UNREFERENCED_PARAMETER(dt);
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
	UNREFERENCED_PARAMETER(dt);
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

void UpdateCreditsMenu(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Credits_x_bb"))
	{
		if (e->on_released_)
		{
			ToggleCredits(false);
			current_main_menu_state = MainMenuState::Main;
		}
	}
}

void InitMainMenu()
{
	current_main_menu_state = MainMenuState::Main;

	ToggleOptions(false);
	ToggleQuit(false);
	ToggleCredits(false);
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
	case MainMenuState::Credits:
		UpdateCreditsMenu(dt);
		break;
	case MainMenuState::Quit:
		UpdateQuitMenu(dt);
		break;
	}
}