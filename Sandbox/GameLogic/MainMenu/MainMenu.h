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
#include "../MainMenu/MainMenu.h"
#include "../CutScene/CutScene.h"
#include "../CutScene/FinalCreditCutScene.h"


enum class MainMenuState
{
	Main,
	Options,
	Credits,
	HowtoPlay,
	Quit
};

enum class HowtoPlayState
{
	Photo1,
	Photo2,
	Photo3,
	Photo4
};

MainMenuState current_main_menu_state = MainMenuState::Main;
HowtoPlayState how_to_play_state = HowtoPlayState::Photo1;
bool playingbgm{ false };
bool how_to_play_page1{ true };
unsigned int count{ 1 };
bool transition_main_cutscene{ false };
float master_volume_{ 0.33f };
float music_volume_{ 0.33f };
float sfx_volume_{ 0.33f };
float mute_threshold{ 0.05f };

float initial_bar_scale_{ 1.0f };
float initial_bar_position_{ -215.0f };

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
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 670.0f;
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
			
			
			Scene().GetSoundSystem()->setMasterVolume(master_volume_);
			Scene().GetComponent<JZEngine::Transform>("Option_master_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_master_pau")->position_.x = initial_bar_position_ + ratio * 670.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_music_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 670.0f;
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
			Scene().GetSoundSystem()->setBGMChannelGroupVolume(music_volume_);
			Scene().GetComponent<JZEngine::Transform>("Option_music_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_music_pau")->position_.x = initial_bar_position_ + ratio * 670.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_sfx_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_) / 670.0f;
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
			Scene().GetSoundSystem()->setEffectsChannelGroupVolume(sfx_volume_);
			Scene().GetComponent<JZEngine::Transform>("Option_sfx_brownbar")->scale_.x = ratio * initial_bar_scale_;
			Scene().GetComponent<JZEngine::Transform>("Option_sfx_pau")->position_.x = initial_bar_position_ + ratio * 670.0f;
		}
	}
	UpdateVolumeIcons(true);
}

void ToggleOptions(bool toggle)
{
	// active/inactive option objects
	Scene().EntityFlagActive("Option_background", toggle);
	//Scene().EntityFlagActive("Option_text", toggle);
	Scene().EntityFlagActive("Option_soundline", toggle);
	//Scene().EntityFlagActive("Option_sound", toggle);
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
	//Scene().EntityFlagActive("Quit_title", toggle);
	Scene().EntityFlagActive("Quit_yes", toggle);
	Scene().EntityFlagActive("Quit_no", toggle);
}

void ToggleCredits(bool toggle)
{
	// active/inactive option objects
	Scene().EntityFlagActive("Credits_background", toggle);
	Scene().EntityFlagActive("Credits_x", toggle);
}

void ToggleHowtoPlayPage(bool toggle)
{
	Scene().EntityFlagActive("How_to_play_photo", toggle);
	Scene().EntityFlagActive("How_to_play_photo2" ,toggle);
	Scene().EntityFlagActive("How_to_play_photo3", toggle);
	Scene().EntityFlagActive("How_to_play_photo4", toggle);
	Scene().EntityFlagActive("How_to_play_x", toggle);
	Scene ().EntityFlagActive ( "Arrow_left_how_to_play" , toggle );
	Scene ().EntityFlagActive ( "Arrow_right_how_to_play" , toggle );
	Scene().EntityFlagActive("Arrow_right_how_to_play_fade", toggle);
	Scene().EntityFlagActive("Arrow_left_how_to_play_fade", toggle);
}

void InitLoadToMenuTransition ()
{
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Load_to_menu" )->tint.w = 1.0f;
}

void UpdateLoadToMenuTransition (float dt)
{
	float& tint = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Load_to_menu" )->tint.w;
	if ( tint > 0.0f )
	{
		tint -= dt;
	}
}

//Handle logic for main menu
void UpdateMainScreen(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_play"))
	{
		if (e->on_released_)
		{
			transition_main_cutscene = true ;
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
	if( transition_main_cutscene )
	{
		float & TransitionBlack = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black" )->tint.w;
		if( TransitionBlack < 1.0f )
		{
			TransitionBlack += dt;
		}
		else
		{
			Cutscene::day = Days::One;
			Scene().ChangeScene("CutScene");
			transition_main_cutscene = false;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_options"))
	{
		if (e->on_released_)
		{
			ToggleOptions(true);
			Scene().EntityFlagActive("Credits", true);
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
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_howtoplay"))
	{
		if (e->on_released_)
		{
			ToggleHowtoPlayPage (true);
			current_main_menu_state = MainMenuState::HowtoPlay;
		}
		if (e->on_held_)
		{
			ToggleButton("how_to_play", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("how_to_play", ButtonState::Hover);
		}
		else
		{
			ToggleButton("how_to_play", ButtonState::Normal);
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
			ToggleButton("Quit_Game", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Quit_Game", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Quit_Game", ButtonState::Normal);
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
			Scene().EntityFlagActive("Credits", false);
			Scene().EntityFlagActive("Quit", false);
			current_main_menu_state = MainMenuState::Main;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_credits"))
	{
		if (e->on_released_)
		{
			//ToggleCredits(true);
			from_main_menu = true;
			Scene ().ChangeScene ( "FinalCreditScene" );
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
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Credits_x_bb"))
	{
		if (e->on_released_)
		{
			ToggleCredits(false);
		}
	}
	// JM: comment this out , as "Quit Game" in "Option" no longer needed.
	/*if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_Quit"))
	{
		if (e->on_released_)
		{
			ToggleOptions(false);
			Scene().EntityFlagActive("Credits", false);
			Scene().EntityFlagActive("Quit", false);
			current_main_menu_state = MainMenuState::Main;
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
	}*/
}

void UpdateQuitMenu(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Quit_yes_bb"))
	{
		if (e->on_released_)
		{
			ToggleQuit(false);
			//current_main_menu_state = MainMenuState::Main;
			Scene ().CloseApplication ();
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

//void UpdateCreditsMenu(float dt)
//{
//	UNREFERENCED_PARAMETER(dt);
//	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Credits_x_bb"))
//	{
//		if (e->on_released_)
//		{
//			ToggleCredits(false);
//			current_main_menu_state = MainMenuState::Main;
//		}
//	}
//}

void UpdateHowtoPlayMenu(float dt)
{
	UNREFERENCED_PARAMETER ( dt );

	unsigned int max{ 4 };
	unsigned int min{ 1 };
	bool first{ false }, last{false};

	if( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Arrow_left_how_to_play" ) )
	{
		if( e->on_released_ )
		{
			if (count > min)
			{
				--count;
			}

			//std::cout << "count is " << count << "\n";
		}
		if (e->on_held_)
		{
			ToggleButton("Arrow_left_how_to_play", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Arrow_left_how_to_play", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Arrow_left_how_to_play", ButtonState::Normal);
		}
	}

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Arrow_right_how_to_play"))
	{
		if (e->on_released_)
		{
			if (count < max)
			{
				++count;
			}

			if (count == 4)
			{
				Scene().GetComponent<JZEngine::MouseEvent>("Arrow_right_how_to_play")->on_released_ = false;
			}
			//std::cout << "count is " << count << "\n";
		}
		if (e->on_held_)
		{
			ToggleButton("Arrow_right_how_to_play", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Arrow_right_how_to_play", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Arrow_right_how_to_play", ButtonState::Normal);
		}

	}
	
	if (count == 1)
	{
		how_to_play_state = HowtoPlayState::Photo1;
		first = true;
		//last = false;
	}
	if (count == 2)
	{
		how_to_play_state = HowtoPlayState::Photo2;
		first = false;
		//last = false;
	}
	if (count == 3)
	{
		how_to_play_state = HowtoPlayState::Photo3;
		first = false;
		last = false;
	}
	if (count == 4)
	{
		how_to_play_state = HowtoPlayState::Photo4;
		first = false;
		last = true;
	}

	if (how_to_play_state == HowtoPlayState::Photo1)
	{
		Scene().EntityFlagActive("How_to_play_photo", true);
		Scene().EntityFlagActive("How_to_play_photo2", false);
		Scene().EntityFlagActive("How_to_play_photo3", false);
		Scene().EntityFlagActive("How_to_play_photo4", false);
	}
	if (how_to_play_state == HowtoPlayState::Photo2)
	{
		Scene().EntityFlagActive("How_to_play_photo", false);
		Scene().EntityFlagActive("How_to_play_photo2", true);
		Scene().EntityFlagActive("How_to_play_photo3", false);
		Scene().EntityFlagActive("How_to_play_photo4", false);
	}
	if (how_to_play_state == HowtoPlayState::Photo3)
	{
		Scene().EntityFlagActive("How_to_play_photo", false);
		Scene().EntityFlagActive("How_to_play_photo2", false);
		Scene().EntityFlagActive("How_to_play_photo3", true);
		Scene().EntityFlagActive("How_to_play_photo4", false);
	}
	if (how_to_play_state == HowtoPlayState::Photo4)
	{
		Scene().EntityFlagActive("How_to_play_photo", false);
		Scene().EntityFlagActive("How_to_play_photo2", false);
		Scene().EntityFlagActive("How_to_play_photo3", false);
		Scene().EntityFlagActive("How_to_play_photo4", true);
	}

	if (first == true)
	{
		Scene().EntityFlagActive("Arrow_left_how_to_play", false);
		Scene().EntityFlagActive("Arrow_left_how_to_play_fade", true);
	}
	if (!first)
	{
		Scene().EntityFlagActive("Arrow_left_how_to_play", true);
		Scene().EntityFlagActive("Arrow_left_how_to_play_fade", false);
	}
	if (last == true)
	{
		Scene().EntityFlagActive("Arrow_right_how_to_play", false);
		Scene().EntityFlagActive("Arrow_right_how_to_play_fade", true);
	}
	if (!last)
	{
		Scene().EntityFlagActive("Arrow_right_how_to_play", true);
		Scene().EntityFlagActive("Arrow_right_how_to_play_fade", false);
	}

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("How_to_play_x"))
	{
		if (e->on_released_)
		{
			ToggleHowtoPlayPage (false);
			current_main_menu_state = MainMenuState::Main;
		}
	}
}

void InitMainMenu()
{
	current_main_menu_state = MainMenuState::Main;
	if (playingbgm == false)
	{
		Scene().PlaySound("bgm", true);
		playingbgm = true;
	}
	ToggleOptions(false);
	ToggleQuit(false);
	ToggleCredits(false);
	Scene().EntityFlagActive("Credits", false);
	Scene().EntityFlagActive("Quit", false);
	ToggleHowtoPlayPage (false);
	//Scene().GetComponent<JZEngine::TextData>("Option_text")->text = JZEngine::String("OPTIONS");
	//Scene().GetComponent<JZEngine::TextData>("Option_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black" )->tint.w = 0.0f;

	InitLoadToMenuTransition ();
}

void UpdateMainMenu(float dt)
{
	UpdateLoadToMenuTransition (dt);
	if (JZEngine::InputHandler::IsMouseTriggered(JZEngine::MOUSE::MOUSE_BUTTON_1))
		Scene().PlaySound("click", false);

	//if (JZEngine::InputHandler::IsKeyTriggered(JZEngine::KEY::KEY_P))
	//{
	//	Scene().GetSoundSystem()->setPauseSoundSystem(true);
	//}
	//if (JZEngine::InputHandler::IsKeyTriggered(JZEngine::KEY::KEY_O))
	//{
	//	Scene().GetSoundSystem()->setPauseSoundSystem(false);
	//}

	switch (current_main_menu_state)
	{
	case MainMenuState::Main:
		UpdateMainScreen(dt);
		break;
	case MainMenuState::Options:
		UpdateOptionsMenu(dt);
		break;
	/*case MainMenuState::Credits:
		UpdateCreditsMenu(dt);
		break;*/
	case MainMenuState::HowtoPlay:
		UpdateHowtoPlayMenu(dt);
		break;
	case MainMenuState::Quit:
		UpdateQuitMenu(dt);
		break;
	}
}