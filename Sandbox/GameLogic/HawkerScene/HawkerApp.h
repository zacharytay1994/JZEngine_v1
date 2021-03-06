/*	__FILE HEADER__
*	File:		HawkerApp.h
	Primary:	Yu Ching Yin
	Date:		05/12/21
	Brief:		Apps logic.
*/

#pragma once

#include "../ButtonLogic.h"
#include "HawkerQueue.h"
#include <string>
#include <map>

enum class HawkerAppState
{
	MainScreen,
	Theresapp,
	Album,
	HowtoPlay,
	Options,
	ShopApp
};

enum class htpState
{
	Photo1,
	Photo2,
	Photo3,
	Photo4
};

HawkerAppState current_app_state = HawkerAppState::MainScreen;
htpState htp_state = htpState::Photo1;

float hp_text_leading{ 3.0f };
float scrolling_speed{ 40.0f };
float top_boundary{ 267.0f };
float bottom_boundary{ -348.0f };
float top_line{ 220.0f };
float top_line_day3{ 200.0f };
float bottom_line{ -340.0f };
float bottom_line_day2{ -333.0f };
float bottom_line_day3{ -300.0f };
float upper_bound{ 270.0f };
bool scroll_up{ false };
bool scroll_down{ false };
bool paused{ false };
bool quit_confirmation{ false };
bool main_menu_confirmation{ false };
bool restart_confirmation{ false };
float original_wallet_amt { 100.0f };
JZEngine::Vec2f shiftup_day1inday2{ 0.0,1000.0 };
JZEngine::Vec2f shiftup_day1inday3{ 0.0,1100.0 };
JZEngine::Vec2f shiftup_day2{ 0.0,1200.0 };
unsigned int Count{ 1 };

//Options
float master_volume_phone{ 0.33f };
float music_volume_phone{ 0.33f };
float sfx_volume_phone{ 0.33f };
float mute_threshold_phone{ 0.05f };
float initial_bar_scale_phone{ 1.0f };
float initial_bar_position_phone{ -215.0f };

// Use in UpdateAlbum()
bool Photo1960{ false }, Photo1980{ false }, Photo2021{ false }, PhotoSelected{ false };

//Original position of messages variables
//Day1
JZEngine::Vec2f original_day1msg1_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg2_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg3_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg4_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg5_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg6_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg7_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg8_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg9_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg10_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg11_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg12_position{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg13_position{ 0.0,0.0 };

JZEngine::Vec2f original_day1msg1_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg2_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg3_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg4_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg5_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg6_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg7_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg8_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg9_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg10_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg11_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg12_position_dup{ 0.0,0.0 };
JZEngine::Vec2f original_day1msg13_position_dup{ 0.0,0.0 };

//Day2
JZEngine::Vec2f original_day2msg1_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg2_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg3_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg4_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg5_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg6_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg7_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg8_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg9_position{ 0.0,0.0 };
JZEngine::Vec2f original_day2msg10_position{ 0.0,0.0 };

//Day3
JZEngine::Vec2f original_day3msg1_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg2_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg3_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg4_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg5_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg6_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg7_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg8_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg9_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg10_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg11_position{ 0.0,0.0 };
JZEngine::Vec2f original_day3msg12_position{ 0.0,0.0 };


enum class SHOPAPP_STATE
{
	FOOD,
	EQUIPMENT,
	PROJECTION,
	INFO
};
SHOPAPP_STATE shopapp_state = SHOPAPP_STATE::FOOD;


void FlagRestartConfirmation( bool flag )
{
	restart_confirmation = flag;
	Scene().EntityFlagActive( "Restart_panel_yes", flag );
	Scene().EntityFlagActive( "Restart_panel_yes_bb", flag );
	Scene().EntityFlagActive( "Restart_panel_no", flag );
	Scene().EntityFlagActive( "Restart_panel_no_bb", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Restart_panel_no_bb" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Restart_panel", flag );
}

void FlagQuitConfirmation( bool flag )
{
	quit_confirmation = flag;
	Scene().EntityFlagActive( "Quit_yes", flag );
	Scene().EntityFlagActive( "Quit_yes_bb", flag );
	Scene().EntityFlagActive( "Quit_no", flag );
	Scene().EntityFlagActive( "Quit_no_bb", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Quit_no_bb" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Quit_bg", flag );
}

void FlagExitToMainMenu( bool flag )
{
	main_menu_confirmation = flag;
	Scene().EntityFlagActive( "ExitToMainMenu", flag );
	Scene().EntityFlagActive( "MainMenuExit_yes", flag );
	Scene().EntityFlagActive( "MainMenuExit_no", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "MainMenuExit_no" )->on_released_ = false;
	}
}

void FlagPhone( bool flag )
{
	Scene().EntityFlagActive( "Phone_outercase", flag );
	Scene().EntityFlagActive( "Phone_battery", flag );
	Scene().EntityFlagActive( "Phone_time", flag );
}

void FlagPhoneHomeScreen( bool flag )
{
	Scene().EntityFlagActive( "Phone_main_screen", flag );
	Scene().EntityFlagActive( "Theresapp", flag );
	Scene().EntityFlagActive( "Album", flag );
	//Scene().EntityFlagActive("Shop", flag);
	Scene().EntityFlagActive( "How_to_Play_app", flag );
	Scene().EntityFlagActive( "Main_Menu_app", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Resume" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Resume", flag );
	Scene().EntityFlagActive( "Restart", flag );
	Scene().EntityFlagActive( "Options", flag );
	Scene().EntityFlagActive( "Exit", flag );

}

void FlagTheresappScreen( bool flag )
{
	Scene().EntityFlagActive( "Phone_blacker_bg", flag );
	Scene().EntityFlagActive( "Theresapp_main_screen", flag );
	Scene().EntityFlagActive( "Theresapp_Dad_chat", flag );
	Scene().EntityFlagActive( "Theresapp_back_arrow", flag );
}

void FlagPhoneAlbumScreen( bool flag )
{
	Scene().EntityFlagActive( "Album_blacker_bg", flag );
	Scene().EntityFlagActive( "Album_main_screen", flag );
	Scene().EntityFlagActive( "Album_top", flag );
	Scene().EntityFlagActive( "Album_time", flag );
	Scene().EntityFlagActive( "Album_battery", flag );
	Scene().EntityFlagActive( "Album_text", flag );
	Scene().EntityFlagActive( "Album_back_arrow", flag );
}

void FlagPhoneAlbumScreenPhoto1960( bool flag )
{
	Scene().EntityFlagActive( "Album_photo_1960s", flag );
	Scene().EntityFlagActive( "black_cover_1960s", flag );
	Scene().EntityFlagActive( "text_1960s", flag );
}

void FlagPhoneAlbumScreenPhoto1980( bool flag )
{
	Scene().EntityFlagActive( "Album_photo_1980s", flag );
	Scene().EntityFlagActive( "black_cover_1980s", flag );
	Scene().EntityFlagActive( "text_1980s", flag );
}

void FlagPhoneAlbumScreenPhoto2021( bool flag )
{
	Scene().EntityFlagActive( "Album_photo_2021s", flag );
	Scene().EntityFlagActive( "black_cover_2021s", flag );
	Scene().EntityFlagActive( "text_2021s", flag );
}

void FlagAlbumPhoto1960( bool flag )
{
	Scene().EntityFlagActive( "Album_1960_big_photo", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Album_1960_big_photo_quit" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Album_1960_big_photo_quit", flag );
	Scene().EntityFlagActive( "Album_1960_button1", flag );
	Scene().EntityFlagActive( "Album_1960_button2", flag );
}

void FlagAlbumPhoto1980( bool flag )
{
	Scene().EntityFlagActive( "Album_1980_big_photo", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Album_1980_big_photo_quit" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Album_1980_big_photo_quit", flag );
	Scene().EntityFlagActive( "Album_1980_button1", flag );
	Scene().EntityFlagActive( "Album_1980_button2", flag );
}

void FlagAlbumPhoto2021( bool flag )
{
	Scene().EntityFlagActive( "Album_2021_big_photo", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Album_2021_big_photo_quit" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Album_2021_big_photo_quit", flag );
	Scene().EntityFlagActive( "Album_2021_button1", flag );
	Scene().EntityFlagActive( "Album_2021_button2", flag );
}

void FlagHowtoPlayScreen( bool flag )
{
	Scene().EntityFlagActive("How_to_play_photo1", flag);
	Scene().EntityFlagActive("How_to_play_photo2", flag);
	Scene().EntityFlagActive("How_to_play_photo3", flag);
	Scene().EntityFlagActive("How_to_play_photo4", flag);
	Scene().EntityFlagActive( "How_to_Play_x", flag );
	Scene().EntityFlagActive("Arrow_left_how_to_play", flag);
	Scene().EntityFlagActive("Arrow_right_how_to_play", flag);
	Scene().EntityFlagActive("Arrow_right_how_to_play_fade", flag);
	Scene().EntityFlagActive("Arrow_left_how_to_play_fade", flag);
}

void FlagOptionsScreen( bool flag )
{
	Scene().EntityFlagActive( "Option_background", flag );
	Scene().EntityFlagActive( "Option_soundline", flag );
	Scene().EntityFlagActive( "Option_master", flag );
	Scene().EntityFlagActive( "Option_music", flag );
	Scene().EntityFlagActive( "Option_sfx", flag );
	Scene().EntityFlagActive( "Option_master_speaker", flag );
	Scene().EntityFlagActive( "Option_music_speaker", flag );
	Scene().EntityFlagActive( "Option_sfx_speaker", flag );

	Scene().EntityFlagActive( "Option_master_blackbar", flag );
	Scene().EntityFlagActive( "Option_master_brownbar", flag );
	Scene().EntityFlagActive( "Option_master_pau", flag );
	Scene().EntityFlagActive( "Option_master_blackbar_border", flag );

	Scene().EntityFlagActive( "Option_music_blackbar", flag );
	Scene().EntityFlagActive( "Option_music_brownbar", flag );
	Scene().EntityFlagActive( "Option_music_pau", flag );
	Scene().EntityFlagActive( "Option_music_blackbar_border", flag );

	Scene().EntityFlagActive( "Option_sfx_blackbar", flag );
	Scene().EntityFlagActive( "Option_sfx_brownbar", flag );
	Scene().EntityFlagActive( "Option_sfx_pau", flag );
	Scene().EntityFlagActive( "Option_sfx_blackbar_border", flag );

	Scene().EntityFlagActive( "Option_master_speaker_off", flag );
	Scene().EntityFlagActive( "Option_music_speaker_off", flag );
	Scene().EntityFlagActive( "Option_sfx_speaker_off", flag );

	Scene().EntityFlagActive( "Option_x", flag );
}

void FlagCreditsScreen( bool flag )
{
	Scene().EntityFlagActive( "Credits_background", flag );
	Scene().EntityFlagActive( "Credits_x", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Credits_x" )->on_released_ = false;
	}
}

void FlagQuitGameScreen( bool flag )
{
	Scene().EntityFlagActive( "QuitGame_bg", flag );
	Scene().EntityFlagActive( "QuitGame_yes", flag );
	Scene().EntityFlagActive( "QuitGame_no", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "QuitGame_no" )->on_released_ = false;
	}
}

void FlagMsg1( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_1_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_1_emoji", flag );
}

void FlagMsg2( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_2_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_2_emoji", flag );
}

void FlagMsg3( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_3_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_3_emoji", flag );
}

void FlagMsg4( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_4_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_4_emoji", flag );
}

void FlagMsg5( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_5_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_5_emoji", flag );
}

void FlagMsg6( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_6_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_6_emoji", flag );
}

void FlagMsg7( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_7_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_7_emoji", flag );
}

void FlagMsg8( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_8_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_8_emoji", flag );
}

void FlagMsg9( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_9_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_9_emoji", flag );
}

void FlagMsg10( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_10_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_10_emoji", flag );
}

void FlagMsg11( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_11_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_11_emoji", flag );
}

void FlagMsg12( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_12_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_12_emoji", flag );
}

void FlagMsg13( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_13_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_13_emoji", flag );
}

void FlagDay2Msgs(bool flag)
{
	Scene().EntityFlagActive("Day2_msg1_bg", flag);
	Scene().EntityFlagActive("Day2_msg2_bg", flag);
	Scene().EntityFlagActive("Day2_msg3_bg", flag);
	Scene().EntityFlagActive("Day2_msg4_bg", flag);
	Scene().EntityFlagActive("Day2_msg5_bg", flag);
	Scene().EntityFlagActive("Day2_msg6_bg", flag);
	Scene().EntityFlagActive("Day2_msg7_bg", flag);
	Scene().EntityFlagActive("Day2_msg8_bg", flag);
	Scene().EntityFlagActive("Day2_msg9_bg", flag);
	Scene().EntityFlagActive("Day2_msg10_bg", flag);
	Scene().EntityFlagActive("Day2_msg1_emoji", flag);
	Scene().EntityFlagActive("Day2_msg2_emoji", flag);
	Scene().EntityFlagActive("Day2_msg3_emoji", flag);
	Scene().EntityFlagActive("Day2_msg4_emoji", flag);
	Scene().EntityFlagActive("Day2_msg5_emoji", flag);
	Scene().EntityFlagActive("Day2_msg6_emoji", flag);
	Scene().EntityFlagActive("Day2_msg7_emoji", flag);
	Scene().EntityFlagActive("Day2_msg8_emoji", flag);
	Scene().EntityFlagActive("Day2_msg9_emoji", flag);
	Scene().EntityFlagActive("Day2_msg10_emoji", flag);
}

void FlagDay3Msgs(bool flag)
{
	Scene().EntityFlagActive("Day3_msg1_bg", flag);
	Scene().EntityFlagActive("Day3_msg2_bg", flag);
	Scene().EntityFlagActive("Day3_msg3_bg", flag);
	Scene().EntityFlagActive("Day3_msg4_bg", flag);
	Scene().EntityFlagActive("Day3_msg5_bg", flag);
	Scene().EntityFlagActive("Day3_msg6_bg", flag);
	Scene().EntityFlagActive("Day3_msg7_bg", flag);
	Scene().EntityFlagActive("Day3_msg8_bg", flag);
	Scene().EntityFlagActive("Day3_msg9_bg", flag);
	Scene().EntityFlagActive("Day3_msg10_bg", flag);
	Scene().EntityFlagActive("Day3_msg11_bg", flag);
	Scene().EntityFlagActive("Day3_msg12_bg", flag);
	Scene().EntityFlagActive("Day3_msg1_emoji", flag);
	Scene().EntityFlagActive("Day3_msg2_emoji", flag);
	Scene().EntityFlagActive("Day3_msg3_emoji", flag);
	Scene().EntityFlagActive("Day3_msg4_emoji", flag);
	Scene().EntityFlagActive("Day3_msg5_emoji", flag);
	Scene().EntityFlagActive("Day3_msg6_emoji", flag);
	Scene().EntityFlagActive("Day3_msg7_emoji", flag);
	Scene().EntityFlagActive("Day3_msg8_emoji", flag);
	Scene().EntityFlagActive("Day3_msg9_emoji", flag);
	Scene().EntityFlagActive("Day3_msg10_emoji", flag);
	Scene().EntityFlagActive("Day3_msg11_emoji", flag);
	Scene().EntityFlagActive("Day3_msg12_emoji", flag);
}

void InitPhoneScreen()
{
	current_app_state = HawkerAppState::MainScreen;

	FlagRestartConfirmation( false );
	FlagQuitConfirmation( false );
	FlagExitToMainMenu( false );

	FlagPhone( false );
	FlagPhoneHomeScreen( false );
	FlagTheresappScreen( false );
	FlagPhoneAlbumScreen( false );

	FlagPhoneAlbumScreenPhoto1960( false );
	FlagPhoneAlbumScreenPhoto1980( false );
	FlagPhoneAlbumScreenPhoto2021( false );

	FlagAlbumPhoto1960( false );
	FlagAlbumPhoto1980( false );
	FlagAlbumPhoto2021( false );

	FlagHowtoPlayScreen( false );
	FlagOptionsScreen( false );
	FlagCreditsScreen( false );
	FlagQuitGameScreen( false );
	Scene().EntityFlagActive( "Credits", false );
	Scene().EntityFlagActive( "Quit", false );
	FlagMsg1( false );
	FlagMsg2( false );
	FlagMsg3( false );
	FlagMsg4( false );
	FlagMsg5( false );
	FlagMsg6( false );
	FlagMsg7( false );
	FlagMsg8( false );
	FlagMsg9( false );
	FlagMsg10( false );
	FlagMsg11( false );
	FlagMsg12( false );
	FlagMsg13( false );

	FlagDay2Msgs(false);
	FlagDay3Msgs(false);

	Scene().EntityFlagActive( "Phone_black_bg", false );
	Scene().GetComponent<JZEngine::NonInstanceShader>( "Phone_black_bg" )->tint.w = 0.0f;

	//Get the original position of all messages
	original_day1msg1_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_;
	original_day1msg2_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_;
	original_day1msg3_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_;
	original_day1msg4_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_;
	original_day1msg5_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_;
	original_day1msg6_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_;
	original_day1msg7_position_dup = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_;
	original_day1msg8_position_dup = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_;
	original_day1msg9_position_dup = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_;
	original_day1msg10_position_dup = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_;
	original_day1msg11_position_dup = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_;
	original_day1msg12_position_dup = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_;
	original_day1msg13_position_dup = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_;

	original_day2msg1_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_;
	original_day2msg2_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_;
	original_day2msg3_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_;
	original_day2msg4_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_;
	original_day2msg5_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_;
	original_day2msg6_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_;
	original_day2msg7_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_;
	original_day2msg8_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_;
	original_day2msg9_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_;
	original_day2msg10_position = Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_;

	original_day3msg1_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg1_bg")->position_;
	original_day3msg2_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg2_bg")->position_;
	original_day3msg3_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg3_bg")->position_;
	original_day3msg4_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg4_bg")->position_;
	original_day3msg5_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg5_bg")->position_;
	original_day3msg6_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg6_bg")->position_;
	original_day3msg7_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg7_bg")->position_;
	original_day3msg8_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg8_bg")->position_;
	original_day3msg9_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg9_bg")->position_;
	original_day3msg10_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg10_bg")->position_;
	original_day3msg11_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg11_bg")->position_;
	original_day3msg12_position = Scene().GetComponent<JZEngine::Transform>("Day3_msg12_bg")->position_;


	//Text section for messages
	/*Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_1_text" )->text =
		JZEngine::String( "   Okay okayyy. Let me\nsleep for an hour first." );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_1_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_1_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_2_text" )->text =
		JZEngine::String( "I will text you if you need\nguidance!" );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_2_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_3_text" )->text =
		JZEngine::String( "Well, it?s your school\nholiday. Help your dad\nout..." );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_3_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_4_text" )->text =
		JZEngine::String( "         Do I have to? I've\n  never done it before." );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_4_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_4_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_5_text" )->text =
		JZEngine::String( "Ai yo... I told you to be\n                           careful!" );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_5_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_5_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_6_text" )->text =
		JZEngine::String( "Baozi, can you help me\nrun the stall today?" );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_6_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_7_text" )->text =
		JZEngine::String( "It seems like I may need\nto stay a few days in the\nhospital though." );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_7_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_8_text" )->text =
		JZEngine::String( "Oh dear..." );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_8_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_9_text" )->text =
		JZEngine::String( "I slipped and fell at the\nhawker centre while\npreparing for the day." );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_9_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_10_text" )->text =
		JZEngine::String( "      WHAT! WHY? ARE\n                  YOU HURT?" );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_10_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_10_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_11_text" )->text = JZEngine::String( "I'm in the hospital." );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_12_text" )->text = JZEngine::String( "           Yea, what's up?" );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_12_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_13_text" )->text = JZEngine::String( "Baozi, are you still up?" );*/

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// -----------------------------------------------------------------------------------------------------------------------------
	//Text section for Album app
	Scene().EntityFlagActive( "Album_black_layer_3", false );
	Scene().EntityFlagActive( "Album_1960_hovertext1_bg", false );
	Scene().EntityFlagActive( "Album_1960_hovertext1", false );
	Scene().EntityFlagActive( "Album_1960_hovertext2_bg", false );
	Scene().EntityFlagActive( "Album_1960_hovertext2", false );

	Scene().EntityFlagActive( "Album_1980_hovertext1_bg", false );
	Scene().EntityFlagActive( "Album_1980_hovertext1", false );
	Scene().EntityFlagActive( "Album_1980_hovertext2_bg", false );
	Scene().EntityFlagActive( "Album_1980_hovertext2", false );


	Scene().EntityFlagActive( "Album_2021_hovertext1_bg", false );
	Scene().EntityFlagActive( "Album_2021_hovertext1", false );
	Scene().EntityFlagActive( "Album_2021_hovertext2_bg", false );
	Scene().EntityFlagActive( "Album_2021_hovertext2", false );


	Scene().GetComponent<JZEngine::TextData>( "Album_text" )->text = JZEngine::String( "My Albums" );
	Scene().GetComponent<JZEngine::TextData>( "text_2021s" )->text = JZEngine::String( "2021s" );
	Scene().GetComponent<JZEngine::TextData>( "text_2021s" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "text_1980s" )->text = JZEngine::String( "1980s" );
	Scene().GetComponent<JZEngine::TextData>( "text_1980s" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "text_1960s" )->text = JZEngine::String( "1960s" );
	Scene().GetComponent<JZEngine::TextData>( "text_1960s" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );

	//Text section for Album1960 app photo hover
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext1" )->text = JZEngine::String
	( "In the past, there were no dedicated\nseating areas, not even a hawker\ncentre.There were only street stalls,\nand patrons would sit around the stall\nto enjoy their meals." );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext1" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext1" )->leading_y_ = hp_text_leading;

	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext2" )->text = JZEngine::String
	( "Without a proper location, hawkers\nwill have to manage the entire stall\non their own.From opening the\nstreet cart for the day, serving orders,\nto washing the used cutleries." );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext2" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext2" )->leading_y_ = hp_text_leading;

	//Text section for Album1980 app photo hover
	Scene().GetComponent<JZEngine::TextData>( "Album_1980_hovertext1" )->text = JZEngine::String
	( "Street carts were relocated to hawker\ncentres! Now, seating areas,utility\nservices, even toilets (at certain places)\ncan be found, vastly improving\nboth diners? and hawkers? quality of life." );
	Scene().GetComponent<JZEngine::TextData>( "Album_1980_hovertext1" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_1980_hovertext1" )->leading_y_ = hp_text_leading;

	Scene().GetComponent<JZEngine::TextData>( "Album_1980_hovertext2" )->text = JZEngine::String
	( "Some recipes were even passed down\nfrom generation to generation!\n\nDo go visit a hawker to try out local\ncuisines like chicken rice and dim sum!" );
	Scene().GetComponent<JZEngine::TextData>( "Album_1980_hovertext2" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_1980_hovertext2" )->leading_y_ = hp_text_leading;


	//Text section for Album2021 app photo hover
	Scene().GetComponent<JZEngine::TextData>( "Album_2021_hovertext1" )->text = JZEngine::String
	( "An automated tray system can be\nfound at certain hawker centres.\n\nTake the initiative to return your\nused cutleries and tray!" );
	Scene().GetComponent<JZEngine::TextData>( "Album_2021_hovertext1" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_2021_hovertext1" )->leading_y_ = hp_text_leading;

	Scene().GetComponent<JZEngine::TextData>( "Album_2021_hovertext2" )->text = JZEngine::String
	( "With the advancement of technology,\nautomations further improve\nthe quality of life at hawker centres!" );
	Scene().GetComponent<JZEngine::TextData>( "Album_2021_hovertext2" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_2021_hovertext2" )->leading_y_ = hp_text_leading;

}

void ResetDay1MsgPosition()
{
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_ = original_day1msg1_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_ = original_day1msg2_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_ = original_day1msg3_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_ = original_day1msg4_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_ = original_day1msg5_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_ = original_day1msg6_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_ = original_day1msg7_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_ = original_day1msg8_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_ = original_day1msg9_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_ = original_day1msg10_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_ = original_day1msg11_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_ = original_day1msg12_position_dup;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_ = original_day1msg13_position_dup;
}

void ResetDay1MsginDay2Position()
{
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_ = original_day1msg1_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_2_bg")->position_ = original_day1msg2_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_3_bg")->position_ = original_day1msg3_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_4_bg")->position_ = original_day1msg4_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_5_bg")->position_ = original_day1msg5_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_6_bg")->position_ = original_day1msg6_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_ = original_day1msg7_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_8_bg")->position_ = original_day1msg8_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_9_bg")->position_ = original_day1msg9_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_10_bg")->position_ = original_day1msg10_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_11_bg")->position_ = original_day1msg11_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_12_bg")->position_ = original_day1msg12_position_dup + shiftup_day1inday2;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_ = original_day1msg13_position_dup + shiftup_day1inday2;
}

void ResetDay1MsginDay3Position()
{
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_ = original_day1msg1_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_2_bg")->position_ = original_day1msg2_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_3_bg")->position_ = original_day1msg3_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_4_bg")->position_ = original_day1msg4_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_5_bg")->position_ = original_day1msg5_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_6_bg")->position_ = original_day1msg6_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_ = original_day1msg7_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_8_bg")->position_ = original_day1msg8_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_9_bg")->position_ = original_day1msg9_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_10_bg")->position_ = original_day1msg10_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_11_bg")->position_ = original_day1msg11_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_12_bg")->position_ = original_day1msg12_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
	Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_ = original_day1msg13_position_dup + shiftup_day1inday3 + shiftup_day1inday3;
}

void ResetDay2MsgPosition()
{
	Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_ = original_day2msg1_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_ = original_day2msg2_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_ = original_day2msg3_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_ = original_day2msg4_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_ = original_day2msg5_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_ = original_day2msg6_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_ = original_day2msg7_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_ = original_day2msg8_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_ = original_day2msg9_position;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_ = original_day2msg10_position;
}

void ResetDay2MsginDay3Position()
{
	Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_ = original_day2msg1_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_ = original_day2msg2_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_ = original_day2msg3_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_ = original_day2msg4_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_ = original_day2msg5_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_ = original_day2msg6_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_ = original_day2msg7_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_ = original_day2msg8_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_ = original_day2msg9_position + shiftup_day2;
	Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_ = original_day2msg10_position + shiftup_day2;
}

void ResetDay3MsgPosition()
{
	Scene().GetComponent<JZEngine::Transform>("Day3_msg1_bg")->position_ = original_day3msg1_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg2_bg")->position_ = original_day3msg2_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg3_bg")->position_ = original_day3msg3_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg4_bg")->position_ = original_day3msg4_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg5_bg")->position_ = original_day3msg5_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg6_bg")->position_ = original_day3msg6_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg7_bg")->position_ = original_day3msg7_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg8_bg")->position_ = original_day3msg8_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg9_bg")->position_ = original_day3msg9_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg10_bg")->position_ = original_day3msg10_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg11_bg")->position_ = original_day3msg11_position;
	Scene().GetComponent<JZEngine::Transform>("Day3_msg12_bg")->position_ = original_day3msg12_position;
}

void UpdatePhoneScreen( float dt )
{
	UNREFERENCED_PARAMETER( dt );
	FlagPhone( true );
	FlagPhoneHomeScreen( true );
	Scene().EntityFlagActive( "PhoneOptions", false );
	paused = true;

	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Theresapp" ) )
	{
		if ( e->on_click_ )
		{
			if (hawker_scene_day == DAY::ONE)
			{
				FlagPhoneHomeScreen(false);
				FlagTheresappScreen(true);
				FlagMsg1(true);
				FlagMsg2(true);
				FlagMsg3(true);
				FlagMsg4(true);
				FlagMsg5(true);
				FlagMsg6(true);
				FlagMsg7(true);
				FlagMsg8(true);
				FlagMsg9(true);
				FlagMsg10(true);
				FlagMsg11(true);
				FlagMsg12(true);
				FlagMsg13(true);

				ResetDay1MsgPosition();
			}
			else if (hawker_scene_day == DAY::TWO)
			{
				FlagPhoneHomeScreen(false);
				FlagTheresappScreen(true);
				FlagMsg1(true);
				FlagMsg2(true);
				FlagMsg3(true);
				FlagMsg4(true);
				FlagMsg5(true);
				FlagMsg6(true);
				FlagMsg7(true);
				FlagMsg8(true);
				FlagMsg9(true);
				FlagMsg10(true);
				FlagMsg11(true);
				FlagMsg12(true);
				FlagMsg13(true);

				FlagDay2Msgs(true);

				ResetDay1MsginDay2Position();
				ResetDay2MsgPosition();
			}
			else if (hawker_scene_day == DAY::THREE)
			{
				FlagPhoneHomeScreen(false);
				FlagTheresappScreen(true);
				FlagMsg1(true);
				FlagMsg2(true);
				FlagMsg3(true);
				FlagMsg4(true);
				FlagMsg5(true);
				FlagMsg6(true);
				FlagMsg7(true);
				FlagMsg8(true);
				FlagMsg9(true);
				FlagMsg10(true);
				FlagMsg11(true);
				FlagMsg12(true);
				FlagMsg13(true);

				FlagDay2Msgs(true);
				FlagDay3Msgs(true);

				ResetDay1MsginDay3Position();
				ResetDay2MsginDay3Position();
				ResetDay3MsgPosition();
			}
			
			current_app_state = HawkerAppState::Theresapp;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album" ) )
	{
		if ( e->on_click_ )
		{
			Scene().EntityFlagActive( "Phone_battery", false );
			Scene().EntityFlagActive( "Phone_time", false );
			FlagPhoneHomeScreen( false );
			FlagPhoneAlbumScreen( true );
			current_app_state = HawkerAppState::Album;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "How_to_Play_app" ) )
	{
		if ( e->on_click_ )
		{
			Scene().EntityFlagActive( "Phone_outercase", false );
			Scene().EntityFlagActive( "Phone_battery", false );
			Scene().EntityFlagActive( "Phone_time", false );
			FlagPhoneHomeScreen( false );
			FlagHowtoPlayScreen( true );
			current_app_state = HawkerAppState::HowtoPlay;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Main_Menu_app" ) )
	{
		if ( e->on_click_ )
		{
			FlagExitToMainMenu( true );
		}
	}
	if ( paused == true && JZEngine::InputHandler::IsKeyReleased( JZEngine::KEY::KEY_ESCAPE ) )
	{
		FlagPhone( false );
		FlagPhoneHomeScreen( false );
		Scene().EntityFlagActive( "PhoneOptions", true );
		paused = false;
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Resume" ) )
	{
		if ( paused == true && e->on_released_ )
		{
			FlagPhone( false );
			FlagPhoneHomeScreen( false );
			Scene().EntityFlagActive( "PhoneOptions", true );
			paused = false;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Restart" ) )
	{
		if ( e->on_click_ )
		{
			//Scene().ChangeScene( "HawkerScene" );
			FlagRestartConfirmation( true );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Options" ) )
	{
		if ( e->on_click_ )
		{
			FlagOptionsScreen( true );
			Scene().EntityFlagActive( "Credits", true );
			Scene().EntityFlagActive( "Quit", true );
			current_app_state = HawkerAppState::Options;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Exit" ) )
	{
		if ( e->on_click_ )
		{
			FlagQuitConfirmation( true );
		}
	}
}

void UpdateHawkerQuitMenu()
{
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Quit_yes_bb" ) )
	{
		if ( e->on_released_ )
		{
			Scene().CloseApplication();
		}
		if ( e->on_held_ )
		{
			ToggleButton( "Quit_yes", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "Quit_yes", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "Quit_yes", ButtonState::Normal );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Quit_no_bb" ) )
	{
		if ( e->on_released_ )
		{
			FlagQuitConfirmation( false );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "Quit_no", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "Quit_no", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "Quit_no", ButtonState::Normal );
		}
	}
}

void UpdateMainMenuExitConfirm( float dt )
{
	UNREFERENCED_PARAMETER( dt );
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "MainMenuExit_yes" ) )
	{
		if ( e->on_released_ )
		{
			Scene().ChangeScene( "MainMenu" );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "MainMenuExit_yes", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "MainMenuExit_yes", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "MainMenuExit_yes", ButtonState::Normal );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "MainMenuExit_no" ) )
	{
		if ( e->on_released_ )
		{
			FlagExitToMainMenu( false );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "MainMenuExit_no", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "MainMenuExit_no", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "MainMenuExit_no", ButtonState::Normal );
		}
	}
}


void UpdateRestartConfirm()
{
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Restart_panel_yes_bb" ) )
	{
		if ( e->on_released_ )
		{
			//Scene().ChangeScene( "MainMenu" );
			Scene().ChangeScene( "HawkerScene" );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "Restart_panel_yes", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "Restart_panel_yes", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "Restart_panel_yes", ButtonState::Normal );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Restart_panel_no_bb" ) )
	{
		if ( e->on_released_ )
		{
			//FlagExitToMainMenu( false );
			FlagRestartConfirmation( false );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "Restart_panel_no", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "Restart_panel_no", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "Restart_panel_no", ButtonState::Normal );
		}
	}
}

void UpdateVolumeIcon( bool flag )
{
	if ( flag )
	{
		bool master_volume = master_volume_phone > 0.0f;
		bool music_volume = music_volume_phone > 0.0f;
		bool sfx_volume = sfx_volume_phone > 0.0f;

		Scene().EntityFlagActive( "Option_master_speaker", master_volume );
		Scene().EntityFlagActive( "Option_master_speaker_off", !master_volume );

		Scene().EntityFlagActive( "Option_music_speaker", music_volume );
		Scene().EntityFlagActive( "Option_music_speaker_off", !music_volume );

		Scene().EntityFlagActive( "Option_sfx_speaker", sfx_volume );
		Scene().EntityFlagActive( "Option_sfx_speaker_off", !sfx_volume );
	}
}

void UpdateVolSlider()
{
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Option_master_bb" ) )
	{
		if ( e->on_held_ )
		{
			float ratio = ( JZEngine::Camera::mouse_world_position_.x - initial_bar_position_phone ) / 670.0f;
			ratio = std::clamp( ratio, 0.0f, 1.0f );
			if ( ratio < mute_threshold_phone )
			{
				ratio = 0.0f;
			}
			else if ( ratio > 1.0f - mute_threshold_phone )
			{
				ratio = 1.0f;
			}
			master_volume_phone = ratio;

			Scene().GetSoundSystem()->setMasterVolume( master_volume_phone );
			Scene().GetComponent<JZEngine::Transform>( "Option_master_brownbar" )->scale_.x = ratio * initial_bar_scale_phone;
			Scene().GetComponent<JZEngine::Transform>( "Option_master_pau" )->position_.x = initial_bar_position_phone + ratio * 670.0f;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Option_music_bb" ) )
	{
		if ( e->on_held_ )
		{
			float ratio = ( JZEngine::Camera::mouse_world_position_.x - initial_bar_position_phone ) / 670.0f;
			ratio = std::clamp( ratio, 0.0f, 1.0f );
			if ( ratio < mute_threshold_phone )
			{
				ratio = 0.0f;
			}
			else if ( ratio > 1.0f - mute_threshold_phone )
			{
				ratio = 1.0f;
			}
			music_volume_phone = ratio;
			Scene().GetSoundSystem()->setBGMChannelGroupVolume( music_volume_phone );
			Scene().GetComponent<JZEngine::Transform>( "Option_music_brownbar" )->scale_.x = ratio * initial_bar_scale_phone;
			Scene().GetComponent<JZEngine::Transform>( "Option_music_pau" )->position_.x = initial_bar_position_phone + ratio * 670.0f;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Option_sfx_bb" ) )
	{
		if ( e->on_held_ )
		{
			float ratio = ( JZEngine::Camera::mouse_world_position_.x - initial_bar_position_phone ) / 670.0f;
			ratio = std::clamp( ratio, 0.0f, 1.0f );
			if ( ratio < mute_threshold_phone )
			{
				ratio = 0.0f;
			}
			else if ( ratio > 1.0f - mute_threshold_phone )
			{
				ratio = 1.0f;
			}
			sfx_volume_phone = ratio;
			Scene().GetSoundSystem()->setEffectsChannelGroupVolume( sfx_volume_phone );
			Scene().GetComponent<JZEngine::Transform>( "Option_sfx_brownbar" )->scale_.x = ratio * initial_bar_scale_phone;
			Scene().GetComponent<JZEngine::Transform>( "Option_sfx_pau" )->position_.x = initial_bar_position_phone + ratio * 670.0f;
		}
	}
	UpdateVolumeIcon( true );
}

void UpdateOptionMenu( float dt )
{
	UNREFERENCED_PARAMETER( dt );
	UpdateVolSlider();
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Option_x" ) )
	{
		if ( e->on_released_ )
		{
			FlagOptionsScreen( false );
			Scene().EntityFlagActive( "Credits", false );
			Scene().EntityFlagActive( "Quit", false );
			current_app_state = HawkerAppState::MainScreen;
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Credits" ) )
	{
		if ( e->on_released_ )
		{
			FlagCreditsScreen( true );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "Credits", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "Credits", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "Credits", ButtonState::Normal );
		}

	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Credits_x" ) )
	{
		if ( e->on_released_ )
		{
			FlagCreditsScreen( false );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Quit" ) )
	{
		if ( e->on_released_ )
		{
			//ToggleOptions(false);
			FlagQuitGameScreen( true );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "Quit", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "Quit", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "Quit", ButtonState::Normal );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "QuitGame_yes" ) )
	{
		if ( e->on_released_ )
		{
			Scene().CloseApplication();
		}
		if ( e->on_held_ )
		{
			ToggleButton( "QuitGame_yes", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "QuitGame_yes", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "QuitGame_yes", ButtonState::Normal );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "QuitGame_no" ) )
	{
		if ( e->on_released_ )
		{
			FlagQuitGameScreen( false );
		}
		if ( e->on_held_ )
		{
			ToggleButton( "QuitGame_no", ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton( "QuitGame_no", ButtonState::Hover );
		}
		else
		{
			ToggleButton( "QuitGame_no", ButtonState::Normal );
		}
	}
}

void UpdateTheresapp( float dt )
{
	UNREFERENCED_PARAMETER( dt );

	if (hawker_scene_day == DAY::ONE)
	{
		FlagPhoneHomeScreen(false);
		FlagTheresappScreen(true);
		FlagMsg1(true);
		FlagMsg2(true);
		FlagMsg3(true);
		FlagMsg4(true);
		FlagMsg5(true);
		FlagMsg6(true);
		FlagMsg7(true);
		FlagMsg8(true);
		FlagMsg9(true);
		FlagMsg10(true);
		FlagMsg11(true);
		FlagMsg12(true);
		FlagMsg13(true);

		//Set control for scrolling down
		if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_.y > bottom_line ||
			Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_.y < top_line)
		{
			scroll_up = true;
		}
		else
		{
			scroll_up = false;
		}

		//Set control for scrolling up
		if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y > upper_bound)
		{
			scroll_down = true;
		}
		else
		{
			scroll_down = false;
		}
	}
	else if (hawker_scene_day == DAY::TWO)
	{
		FlagPhoneHomeScreen(false);
		FlagTheresappScreen(true);
		FlagMsg1(true);
		FlagMsg2(true);
		FlagMsg3(true);
		FlagMsg4(true);
		FlagMsg5(true);
		FlagMsg6(true);
		FlagMsg7(true);
		FlagMsg8(true);
		FlagMsg9(true);
		FlagMsg10(true);
		FlagMsg11(true);
		FlagMsg12(true);
		FlagMsg13(true);
		FlagDay2Msgs(true);


		//Set control for scrolling down
		if (Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_.y > bottom_line_day2 ||
			Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_.y < top_line)
		{
			scroll_up = true;
		}
		else
		{
			scroll_up = false;
		}

		//Set control for scrolling up
		if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y > upper_bound)
		{
			scroll_down = true;
		}
		else
		{
			scroll_down = false;
		}
	}
	else if (hawker_scene_day == DAY::THREE)
	{
		FlagPhoneHomeScreen(false);
		FlagTheresappScreen(true);
		FlagMsg1(true);
		FlagMsg2(true);
		FlagMsg3(true);
		FlagMsg4(true);
		FlagMsg5(true);
		FlagMsg6(true);
		FlagMsg7(true);
		FlagMsg8(true);
		FlagMsg9(true);
		FlagMsg10(true);
		FlagMsg11(true);
		FlagMsg12(true);
		FlagMsg13(true);
		FlagDay2Msgs(true);
		FlagDay3Msgs(true);

		//Set control for scrolling down
		if (Scene().GetComponent<JZEngine::Transform>("Day3_msg12_bg")->position_.y > bottom_line_day3 ||
			Scene().GetComponent<JZEngine::Transform>("Day3_msg7_bg")->position_.y < top_line_day3)
		{
			scroll_up = true;
		}
		else
		{
			scroll_up = false;
		}

		//Set control for scrolling up
		if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y > upper_bound)
		{
			scroll_down = true;
		}
		else
		{
			scroll_down = false;
		}
	}
	

	//Scrolling
	if ( scroll_up == true && JZEngine::InputHandler::mouse_scrolled_ == -1 )
	{
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_.y += scrolling_speed;

		Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_.y += scrolling_speed;

		Scene().GetComponent<JZEngine::Transform>("Day3_msg1_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg2_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg3_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg4_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg5_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg6_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg7_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg8_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg9_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg10_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg11_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg12_bg")->position_.y += scrolling_speed;
	}
	else if ( scroll_down == true && JZEngine::InputHandler::mouse_scrolled_ == 1 )
	{
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_.y -= scrolling_speed;

		Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_.y -= scrolling_speed;

		Scene().GetComponent<JZEngine::Transform>("Day3_msg1_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg2_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg3_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg4_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg5_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg6_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg7_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg8_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg9_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg10_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg11_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Day3_msg12_bg")->position_.y -= scrolling_speed;
	}

	//If the message is out of the phone it will disappear
	//Day1
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_.y < bottom_boundary )
	{
		FlagMsg1( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_.y < bottom_boundary )
	{
		FlagMsg2( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_.y < bottom_boundary )
	{
		FlagMsg3( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_.y < bottom_boundary )
	{
		FlagMsg4( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_.y < bottom_boundary )
	{
		FlagMsg5( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_.y < bottom_boundary )
	{
		FlagMsg6( false );
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_.y > top_boundary)
	{
		FlagMsg1(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_2_bg")->position_.y > top_boundary)
	{
		FlagMsg2(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_3_bg")->position_.y > top_boundary)
	{
		FlagMsg3(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_4_bg")->position_.y > top_boundary)
	{
		FlagMsg4(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_5_bg")->position_.y > top_boundary)
	{
		FlagMsg5(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_6_bg")->position_.y > top_boundary)
	{
		FlagMsg6(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_.y > top_boundary)
	{
		FlagMsg7(false);
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_.y > top_boundary )
	{
		FlagMsg8( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_.y > top_boundary )
	{
		FlagMsg9( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_.y > top_boundary )
	{
		FlagMsg10( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_.y > top_boundary )
	{
		FlagMsg11( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_.y > top_boundary )
	{
		FlagMsg12( false );
	}
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_.y > top_boundary )
	{
		FlagMsg13( false );
	}


	//Day2
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg10_bg", false);
		Scene().EntityFlagActive("Day2_msg10_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg9_bg", false);
		Scene().EntityFlagActive("Day2_msg9_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg8_bg", false);
		Scene().EntityFlagActive("Day2_msg8_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg7_bg", false);
		Scene().EntityFlagActive("Day2_msg7_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg6_bg", false);
		Scene().EntityFlagActive("Day2_msg6_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg5_bg", false);
		Scene().EntityFlagActive("Day2_msg5_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg4_bg", false);
		Scene().EntityFlagActive("Day2_msg4_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg3_bg", false);
		Scene().EntityFlagActive("Day2_msg3_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg2_bg", false);
		Scene().EntityFlagActive("Day2_msg2_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day2_msg1_bg", false);
		Scene().EntityFlagActive("Day2_msg1_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg10_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg10_bg", false);
		Scene().EntityFlagActive("Day2_msg10_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg9_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg9_bg", false);
		Scene().EntityFlagActive("Day2_msg9_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg8_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg8_bg", false);
		Scene().EntityFlagActive("Day2_msg8_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg7_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg7_bg", false);
		Scene().EntityFlagActive("Day2_msg7_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg6_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg6_bg", false);
		Scene().EntityFlagActive("Day2_msg6_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg5_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg5_bg", false);
		Scene().EntityFlagActive("Day2_msg5_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg4_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg4_bg", false);
		Scene().EntityFlagActive("Day2_msg4_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg3_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg3_bg", false);
		Scene().EntityFlagActive("Day2_msg3_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg2_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg2_bg", false);
		Scene().EntityFlagActive("Day2_msg2_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day2_msg1_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day2_msg1_bg", false);
		Scene().EntityFlagActive("Day2_msg1_emoji", false);
	}


	//Day3
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg12_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg12_bg", false);
		Scene().EntityFlagActive("Day3_msg12_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg11_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg11_bg", false);
		Scene().EntityFlagActive("Day3_msg11_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg10_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg10_bg", false);
		Scene().EntityFlagActive("Day3_msg10_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg9_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg9_bg", false);
		Scene().EntityFlagActive("Day3_msg9_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg8_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg8_bg", false);
		Scene().EntityFlagActive("Day3_msg8_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg7_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg7_bg", false);
		Scene().EntityFlagActive("Day3_msg7_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg6_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg6_bg", false);
		Scene().EntityFlagActive("Day3_msg6_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg5_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg5_bg", false);
		Scene().EntityFlagActive("Day3_msg5_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg4_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg4_bg", false);
		Scene().EntityFlagActive("Day3_msg4_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg3_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg3_bg", false);
		Scene().EntityFlagActive("Day3_msg3_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg2_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg2_bg", false);
		Scene().EntityFlagActive("Day3_msg2_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg1_bg")->position_.y < bottom_boundary)
	{
		Scene().EntityFlagActive("Day3_msg1_bg", false);
		Scene().EntityFlagActive("Day3_msg1_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg6_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day3_msg6_bg", false);
		Scene().EntityFlagActive("Day3_msg6_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg5_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day3_msg5_bg", false);
		Scene().EntityFlagActive("Day3_msg5_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg4_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day3_msg4_bg", false);
		Scene().EntityFlagActive("Day3_msg4_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg3_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day3_msg3_bg", false);
		Scene().EntityFlagActive("Day3_msg3_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg2_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day3_msg2_bg", false);
		Scene().EntityFlagActive("Day3_msg2_emoji", false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Day3_msg1_bg")->position_.y > top_boundary)
	{
		Scene().EntityFlagActive("Day3_msg1_bg", false);
		Scene().EntityFlagActive("Day3_msg1_emoji", false);
	}

	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Theresapp_back_arrow" ) )
	{
		if ( e->on_click_ )
		{
			if (hawker_scene_day == DAY::ONE)
			{
				FlagPhoneHomeScreen(true);
				FlagTheresappScreen(false);
				FlagMsg1(false);
				FlagMsg2(false);
				FlagMsg3(false);
				FlagMsg4(false);
				FlagMsg5(false);
				FlagMsg6(false);
				FlagMsg7(false);
				FlagMsg8(false);
				FlagMsg9(false);
				FlagMsg10(false);
				FlagMsg11(false);
				FlagMsg12(false);
				FlagMsg13(false);
			}
			else if (hawker_scene_day == DAY::TWO)
			{
				FlagPhoneHomeScreen(true);
				FlagTheresappScreen(false);
				FlagMsg1(false);
				FlagMsg2(false);
				FlagMsg3(false);
				FlagMsg4(false);
				FlagMsg5(false);
				FlagMsg6(false);
				FlagMsg7(false);
				FlagMsg8(false);
				FlagMsg9(false);
				FlagMsg10(false);
				FlagMsg11(false);
				FlagMsg12(false);
				FlagMsg13(false);

				FlagDay2Msgs(false);
			}
			else if (hawker_scene_day == DAY::THREE)
			{
				FlagPhoneHomeScreen(true);
				FlagTheresappScreen(false);
				FlagMsg1(false);
				FlagMsg2(false);
				FlagMsg3(false);
				FlagMsg4(false);
				FlagMsg5(false);
				FlagMsg6(false);
				FlagMsg7(false);
				FlagMsg8(false);
				FlagMsg9(false);
				FlagMsg10(false);
				FlagMsg11(false);
				FlagMsg12(false);
				FlagMsg13(false);

				FlagDay2Msgs(false);
				FlagDay3Msgs(false);
			}

			current_app_state = HawkerAppState::MainScreen;
		}
	}
}

void UpdateAlbum( float dt )
{
	UNREFERENCED_PARAMETER( dt );
	FlagPhoneHomeScreen( false );
	FlagPhoneAlbumScreen( true );

	if ( !PhotoSelected )
	{
		if ( hawker_scene_day == DAY::TWO || hawker_scene_day == DAY::THREE )
		{
			// Render assests for 1960
			FlagPhoneAlbumScreenPhoto1960( true );
			// Check for mouse event Photo1960
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_photo_1960s" ) )
			{
				if ( e->on_released_ )
				{
					Photo1960 = true;
					PhotoSelected = true;
				}
			}
		}
		if ( hawker_scene_day == DAY::THREE )
		{
			// Render assests for 1980
			FlagPhoneAlbumScreenPhoto1980( true );
			// Check for mouse event Photo1980
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_photo_1980s" ) )
			{
				if ( e->on_released_ )
				{
					Photo1980 = true;
					PhotoSelected = true;
				}
			}
			// Render assests for 2021
			FlagPhoneAlbumScreenPhoto2021( true );
			// Check for mouse event Photo2021
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_photo_2021s" ) )
			{
				if ( e->on_released_ )
				{
					Photo2021 = true;
					PhotoSelected = true;
				}
			}
		}
		// Check for mouse event for '<' arrow 
		if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_back_arrow" ) )
		{
			if ( e->on_click_ )
			{
				Scene().EntityFlagActive( "Phone_battery", true );
				Scene().EntityFlagActive( "Phone_time", true );
				FlagPhoneHomeScreen( true );
				FlagPhoneAlbumScreen( false );

				FlagPhoneAlbumScreenPhoto1960( false );
				FlagPhoneAlbumScreenPhoto1980( false );
				FlagPhoneAlbumScreenPhoto2021( false );

				current_app_state = HawkerAppState::MainScreen;

				// reset album 
				Photo1960 = false; Photo1980 = false; Photo2021 = false; PhotoSelected = false;
			}
		}
	}
	else
	{
		if ( Photo1960 )
		{
			FlagAlbumPhoto1960( true );
			Scene().EntityFlagActive( "Album_black_layer_3", true );
			// Hover Over #1
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_1960_button1" ) )
			{
				if ( e->on_hover_ )
				{
					ToggleButton( "Album_1960_button1", ButtonState::Hover );
					Scene().EntityFlagActive( "Album_1960_hovertext1_bg", true );
					Scene().EntityFlagActive( "Album_1960_hovertext1", true );
				}
				else
				{
					ToggleButton( "Album_1960_button1", ButtonState::Normal );
					Scene().EntityFlagActive( "Album_1960_hovertext1_bg", false );
					Scene().EntityFlagActive( "Album_1960_hovertext1", false );
				}
			}
			// Hover Over #2
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_1960_button2" ) )
			{
				if ( e->on_hover_ )
				{
					ToggleButton( "Album_1960_button2", ButtonState::Hover );
					Scene().EntityFlagActive( "Album_1960_hovertext2_bg", true );
					Scene().EntityFlagActive( "Album_1960_hovertext2", true );
				}
				else
				{
					ToggleButton( "Album_1960_button2", ButtonState::Normal );
					Scene().EntityFlagActive( "Album_1960_hovertext2_bg", false );
					Scene().EntityFlagActive( "Album_1960_hovertext2", false );
				}
			}
			// Quit button for Photo 1960
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_1960_big_photo_quit" ) )
			{
				if ( e->on_released_ )
				{
					FlagAlbumPhoto1960( false );
					Scene().EntityFlagActive( "Album_black_layer_3", false );
					Photo1960 = false;
					PhotoSelected = false;
				}
			}
			Photo1980 = false;
			Photo2021 = false;
		}
		if ( Photo1980 )
		{
			FlagAlbumPhoto1980( true );
			Scene().EntityFlagActive( "Album_black_layer_3", true );
			// Hover Over #1
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_1980_button1" ) )
			{
				if ( e->on_hover_ )
				{
					ToggleButton( "Album_1980_button1", ButtonState::Hover );
					Scene().EntityFlagActive( "Album_1980_hovertext1_bg", true );
					Scene().EntityFlagActive( "Album_1980_hovertext1", true );
				}
				else
				{
					ToggleButton( "Album_1980_button1", ButtonState::Normal );
					Scene().EntityFlagActive( "Album_1980_hovertext1_bg", false );
					Scene().EntityFlagActive( "Album_1980_hovertext1", false );
				}
			}
			// Hover Over #2
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_1980_button2" ) )
			{
				if ( e->on_hover_ )
				{
					ToggleButton( "Album_1980_button2", ButtonState::Hover );
					Scene().EntityFlagActive( "Album_1980_hovertext2_bg", true );
					Scene().EntityFlagActive( "Album_1980_hovertext2", true );
				}
				else
				{
					ToggleButton( "Album_1980_button2", ButtonState::Normal );
					Scene().EntityFlagActive( "Album_1980_hovertext2_bg", false );
					Scene().EntityFlagActive( "Album_1980_hovertext2", false );
				}
			}
			// Quit button for Photo 1980
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_1980_big_photo_quit" ) )
			{
				if ( e->on_released_ )
				{
					FlagAlbumPhoto1980( false );
					Scene().EntityFlagActive( "Album_black_layer_3", false );
					Photo1980 = false;
					PhotoSelected = false;
				}
			}
			Photo1960 = false;
			Photo2021 = false;
		}
		if ( Photo2021 )
		{
			FlagAlbumPhoto2021( true );
			Scene().EntityFlagActive( "Album_black_layer_3", true );
			// Hover Over #1
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_2021_button1" ) )
			{
				if ( e->on_hover_ )
				{
					ToggleButton( "Album_2021_button1", ButtonState::Hover );
					Scene().EntityFlagActive( "Album_2021_hovertext1_bg", true );
					Scene().EntityFlagActive( "Album_2021_hovertext1", true );
				}
				else
				{
					ToggleButton( "Album_2021_button1", ButtonState::Normal );
					Scene().EntityFlagActive( "Album_2021_hovertext1_bg", false );
					Scene().EntityFlagActive( "Album_2021_hovertext1", false );
				}
			}
			// Hover Over #2
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_2021_button2" ) )
			{
				if ( e->on_hover_ )
				{
					ToggleButton( "Album_2021_button2", ButtonState::Hover );
					Scene().EntityFlagActive( "Album_2021_hovertext2_bg", true );
					Scene().EntityFlagActive( "Album_2021_hovertext2", true );
				}
				else
				{
					ToggleButton( "Album_2021_button2", ButtonState::Normal );
					Scene().EntityFlagActive( "Album_2021_hovertext2_bg", false );
					Scene().EntityFlagActive( "Album_2021_hovertext2", false );
				}
			}
			// Quit button for Photo 2021
			if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Album_2021_big_photo_quit" ) )
			{
				if ( e->on_released_ )
				{
					FlagAlbumPhoto2021( false );
					Scene().EntityFlagActive( "Album_black_layer_3", false );
					Photo2021 = false;
					PhotoSelected = false;
				}
			}
			Photo1960 = false;
			Photo1980 = false;
		}
		if ( !Photo1960 && !Photo1980 && !Photo2021 )
		{
			FlagAlbumPhoto1960( false );
			FlagAlbumPhoto1980( false );
			FlagAlbumPhoto2021( false );
		}
	}
}

void UpdateHowtoPlay( float dt )
{
	UNREFERENCED_PARAMETER( dt );
	Scene().EntityFlagActive( "Phone_outercase", false );
	Scene().EntityFlagActive( "Phone_battery", false );
	Scene().EntityFlagActive( "Phone_time", false );
	FlagPhoneHomeScreen( false );
	FlagHowtoPlayScreen( true );

	unsigned int max{ 4 };
	unsigned int min{ 1 };
	bool first{ false }, last{ false };

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Arrow_left_how_to_play"))
	{
		if (e->on_released_)
		{
			if (Count > min)
			{
				--Count;
			}

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
			if (Count < max)
			{
				++Count;
			}

			if (Count == 4)
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

	if (Count == 1)
	{
		htp_state = htpState::Photo1;
		first = true;
	}
	if (Count == 2)
	{
		htp_state = htpState::Photo2;
		first = false;
	}
	if (Count == 3)
	{
		htp_state = htpState::Photo3;
		first = false;
		last = false;
	}
	if (Count == 4)
	{
		htp_state = htpState::Photo4;
		first = false;
		last = true;
	}

	if (htp_state == htpState::Photo1)
	{
		Scene().EntityFlagActive("How_to_play_photo1", true);
		Scene().EntityFlagActive("How_to_play_photo2", false);
		Scene().EntityFlagActive("How_to_play_photo3", false);
		Scene().EntityFlagActive("How_to_play_photo4", false);
	}
	if (htp_state == htpState::Photo2)
	{
		Scene().EntityFlagActive("How_to_play_photo1", false);
		Scene().EntityFlagActive("How_to_play_photo2", true);
		Scene().EntityFlagActive("How_to_play_photo3", false);
		Scene().EntityFlagActive("How_to_play_photo4", false);
	}
	if (htp_state == htpState::Photo3)
	{
		Scene().EntityFlagActive("How_to_play_photo1", false);
		Scene().EntityFlagActive("How_to_play_photo2", false);
		Scene().EntityFlagActive("How_to_play_photo3", true);
		Scene().EntityFlagActive("How_to_play_photo4", false);
	}
	if (htp_state == htpState::Photo4)
	{
		Scene().EntityFlagActive("How_to_play_photo1", false);
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

	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "How_to_Play_x" ) )
	{
		if ( e->on_click_ )
		{
			Scene().EntityFlagActive( "Phone_outercase", true );
			Scene().EntityFlagActive( "Phone_battery", true );
			Scene().EntityFlagActive( "Phone_time", true );
			FlagPhoneHomeScreen( true );
			FlagHowtoPlayScreen( false );

			current_app_state = HawkerAppState::MainScreen;
		}
	}
}

void UpdateHomeScreen( float dt )
{
	switch ( current_app_state )
	{
	case HawkerAppState::MainScreen:
		UpdatePhoneScreen( dt );
		break;
	case HawkerAppState::Theresapp:
		UpdateTheresapp( dt );
		break;
	case HawkerAppState::Album:
		UpdateAlbum( dt );
		break;
	case HawkerAppState::HowtoPlay:
		UpdateHowtoPlay( dt );
		break;
	case HawkerAppState::Options:
		UpdateOptionMenu( dt );
		break;
	}

	if ( quit_confirmation )
	{
		UpdateHawkerQuitMenu();
	}
	if ( main_menu_confirmation )
	{
		UpdateMainMenuExitConfirm( dt );
	}
	if ( restart_confirmation )
	{
		UpdateRestartConfirm();
	}
}