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

HawkerAppState current_app_state = HawkerAppState::MainScreen;

float hp_text_leading{ 3.0f };
float scrolling_speed{ 40.0f };
float top_boundary{ 267.0f };
float bottom_boundary{ -348.0f };
float top_line{ 220.0f };
float bottom_line{ -340.0f };
float upper_bound{ 270.0f };
bool scroll_up{ false };
bool scroll_down{ false };
bool paused{ false };
bool quit_confirmation{ false };
bool main_menu_confirmation{ false };
bool restart_confirmation{ false };
float original_wallet_amt { 100.0f };

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
JZEngine::Vec2f original_msg1_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg2_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg3_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg4_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg5_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg6_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg7_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg8_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg9_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg10_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg11_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg12_position{ 0.0,0.0 };
JZEngine::Vec2f original_msg13_position{ 0.0,0.0 };

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
}

void FlagAlbumPhoto2021( bool flag )
{
	Scene().EntityFlagActive( "Album_2021_big_photo", flag );
	if ( !flag )
	{
		Scene().GetComponent<JZEngine::MouseEvent>( "Album_2021_big_photo_quit" )->on_released_ = false;
	}
	Scene().EntityFlagActive( "Album_2021_big_photo_quit", flag );
}

void FlagHowtoPlayScreen( bool flag )
{
	Scene().EntityFlagActive( "How_to_Play_photo", flag );
	Scene().EntityFlagActive( "How_to_Play_text", flag );
	Scene().EntityFlagActive( "How_to_Play_x", flag );
}

void FlagOptionsScreen(bool flag)
{
	Scene().EntityFlagActive("Option_background", flag);
	Scene().EntityFlagActive("Option_soundline", flag);
	Scene().EntityFlagActive("Option_master", flag);
	Scene().EntityFlagActive("Option_music", flag);
	Scene().EntityFlagActive("Option_sfx", flag);
	Scene().EntityFlagActive("Option_master_speaker", flag);
	Scene().EntityFlagActive("Option_music_speaker", flag);
	Scene().EntityFlagActive("Option_sfx_speaker", flag);

	Scene().EntityFlagActive("Option_master_blackbar", flag);
	Scene().EntityFlagActive("Option_master_brownbar", flag);
	Scene().EntityFlagActive("Option_master_pau", flag);
	Scene().EntityFlagActive("Option_master_blackbar_border", flag);

	Scene().EntityFlagActive("Option_music_blackbar", flag);
	Scene().EntityFlagActive("Option_music_brownbar", flag);
	Scene().EntityFlagActive("Option_music_pau", flag);
	Scene().EntityFlagActive("Option_music_blackbar_border", flag);

	Scene().EntityFlagActive("Option_sfx_blackbar", flag);
	Scene().EntityFlagActive("Option_sfx_brownbar", flag);
	Scene().EntityFlagActive("Option_sfx_pau", flag);
	Scene().EntityFlagActive("Option_sfx_blackbar_border", flag);

	Scene().EntityFlagActive("Option_master_speaker_off", flag);
	Scene().EntityFlagActive("Option_music_speaker_off", flag);
	Scene().EntityFlagActive("Option_sfx_speaker_off", flag);

	Scene().EntityFlagActive("Option_x", flag);
}

void FlagCreditsScreen(bool flag)
{
	Scene().EntityFlagActive("Credits_background", flag);
	Scene().EntityFlagActive("Credits_x", flag);
	if (!flag)
	{
		Scene().GetComponent<JZEngine::MouseEvent>("Credits_x")->on_released_ = false;
	}
}

void FlagQuitGameScreen(bool flag)
{
	Scene().EntityFlagActive("QuitGame_bg", flag);
	Scene().EntityFlagActive("QuitGame_yes", flag);
	Scene().EntityFlagActive("QuitGame_no", flag);
	if (!flag)
	{
		Scene().GetComponent<JZEngine::MouseEvent>("QuitGame_no")->on_released_ = false;
	}
}

void FlagMsg1( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_1_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_1_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_1_text", flag );
}

void FlagMsg2( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_2_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_2_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_2_text", flag );
}

void FlagMsg3( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_3_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_3_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_3_text", flag );
}

void FlagMsg4( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_4_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_4_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_4_text", flag );
}

void FlagMsg5( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_5_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_5_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_5_text", flag );
}

void FlagMsg6( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_6_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_6_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_6_text", flag );
}

void FlagMsg7( bool flag )
{
	Scene().EntityFlagActive( "Last_page_msg_7_bg", flag );
	Scene().EntityFlagActive( "Last_page_msg_7_emoji", flag );
	Scene().EntityFlagActive( "Last_page_msg_7_text", flag );
}

void FlagMsg8( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_8_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_8_emoji", flag );
	Scene().EntityFlagActive( "First_page_msg_8_text", flag );
}

void FlagMsg9( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_9_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_9_emoji", flag );
	Scene().EntityFlagActive( "First_page_msg_9_text", flag );
}

void FlagMsg10( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_10_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_10_emoji", flag );
	Scene().EntityFlagActive( "First_page_msg_10_text", flag );
}

void FlagMsg11( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_11_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_11_emoji", flag );
	Scene().EntityFlagActive( "First_page_msg_11_text", flag );
}

void FlagMsg12( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_12_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_12_emoji", flag );
	Scene().EntityFlagActive( "First_page_msg_12_text", flag );
}

void FlagMsg13( bool flag )
{
	Scene().EntityFlagActive( "First_page_msg_13_bg", flag );
	Scene().EntityFlagActive( "First_page_msg_13_emoji", flag );
	Scene().EntityFlagActive( "First_page_msg_13_text", flag );
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
	FlagOptionsScreen(false);
	FlagCreditsScreen(false);
	FlagQuitGameScreen(false);
	Scene().EntityFlagActive("Credits", false);
	Scene().EntityFlagActive("Quit", false);
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

	Scene().EntityFlagActive( "Phone_black_bg", false );
	Scene().GetComponent<JZEngine::NonInstanceShader>( "Phone_black_bg" )->tint.w = 0.0f;

	//Get the original position of all messages
	original_msg1_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_;
	original_msg2_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_;
	original_msg3_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_;
	original_msg4_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_;
	original_msg5_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_;
	original_msg6_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_;
	original_msg7_position = Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_;
	original_msg8_position = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_;
	original_msg9_position = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_;
	original_msg10_position = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_;
	original_msg11_position = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_;
	original_msg12_position = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_;
	original_msg13_position = Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_;

	Scene().EntityFlagActive( "Album_black_layer_3", false );
	Scene().EntityFlagActive( "Album_1960_hovertext1_bg", false );
	Scene().EntityFlagActive( "Album_1960_hovertext1", false );
	Scene().EntityFlagActive( "Album_1960_hovertext2_bg", false );
	Scene().EntityFlagActive( "Album_1960_hovertext2", false );

	//Text section for messages
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_1_text" )->text =
		JZEngine::String( "   Okay okayyy. Let me\nsleep for an hour first." );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_1_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_1_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_2_text" )->text =
		JZEngine::String( "I will text you if you need\nguidance!" );
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_2_text" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Last_page_msg_3_text" )->text =
		JZEngine::String( "Well, it’s your school\nholiday. Help your dad\nout..." );
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
	Scene().GetComponent<JZEngine::TextData>( "First_page_msg_13_text" )->text = JZEngine::String( "Baozi, are you still up?" );

	//Text section for Album app
	Scene().GetComponent<JZEngine::TextData>( "Album_text" )->text = JZEngine::String( "My Albums" );
	Scene().GetComponent<JZEngine::TextData>( "text_2021s" )->text = JZEngine::String( "2021s" );
	Scene().GetComponent<JZEngine::TextData>( "text_2021s" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "text_1980s" )->text = JZEngine::String( "1980s" );
	Scene().GetComponent<JZEngine::TextData>( "text_1980s" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "text_1960s" )->text = JZEngine::String( "1960s" );
	Scene().GetComponent<JZEngine::TextData>( "text_1960s" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );

	//Text section for Album app photo hover
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext1" )->text = JZEngine::String
	( "Diners sit on the wooden tools\naround the stall facing a\nhawker owner who would take\n"
	  "their orders and serve hot food\nfrom the pot at street hawkers." );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext1" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext1" )->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext2" )->text = JZEngine::String
	( "During the era, the hawker\nowners does not have pipeline\nacross to water. Their utensils\n"
	  "not clean cause a lot of\ncontamination by fliesand rats." );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext2" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );
	Scene().GetComponent<JZEngine::TextData>( "Album_1960_hovertext2" )->leading_y_ = hp_text_leading;

	//Text section for how to play
	Scene().GetComponent<JZEngine::TextData>( "How_to_Play_text" )->text = JZEngine::String( "HOW TO PLAY" );
	Scene().GetComponent<JZEngine::TextData>( "How_to_Play_text" )->color_ = JZEngine::Vec3f( 255.0f, 255.0f, 255.0f );

}

void ResetAllMsgPosition()
{
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_ = original_msg1_position;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_2_bg" )->position_ = original_msg2_position;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_3_bg" )->position_ = original_msg3_position;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_4_bg" )->position_ = original_msg4_position;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_5_bg" )->position_ = original_msg5_position;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_6_bg" )->position_ = original_msg6_position;
	Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_ = original_msg7_position;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_8_bg" )->position_ = original_msg8_position;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_9_bg" )->position_ = original_msg9_position;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_10_bg" )->position_ = original_msg10_position;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_11_bg" )->position_ = original_msg11_position;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_12_bg" )->position_ = original_msg12_position;
	Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_ = original_msg13_position;
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
			FlagPhoneHomeScreen( false );
			FlagTheresappScreen( true );
			FlagMsg1( true );
			FlagMsg2( true );
			FlagMsg3( true );
			FlagMsg4( true );
			FlagMsg5( true );
			FlagMsg6( true );
			FlagMsg7( true );
			FlagMsg8( true );
			FlagMsg9( true );
			FlagMsg10( true );
			FlagMsg11( true );
			FlagMsg12( true );
			FlagMsg13( true );

			ResetAllMsgPosition();
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
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Options"))
	{
		if (e->on_click_)
		{
			FlagOptionsScreen(true);
			Scene().EntityFlagActive("Credits", true);
			Scene().EntityFlagActive("Quit", true);
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

void UpdateVolumeIcon(bool flag)
{
	if (flag)
	{
		bool master_volume = master_volume_phone > 0.0f;
		bool music_volume = music_volume_phone > 0.0f;
		bool sfx_volume = sfx_volume_phone > 0.0f;

		Scene().EntityFlagActive("Option_master_speaker", master_volume);
		Scene().EntityFlagActive("Option_master_speaker_off", !master_volume);

		Scene().EntityFlagActive("Option_music_speaker", music_volume);
		Scene().EntityFlagActive("Option_music_speaker_off", !music_volume);

		Scene().EntityFlagActive("Option_sfx_speaker", sfx_volume);
		Scene().EntityFlagActive("Option_sfx_speaker_off", !sfx_volume);
	}
}

void UpdateVolSlider()
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_master_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_phone) / 670.0f;
			ratio = std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold_phone)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold_phone)
			{
				ratio = 1.0f;
			}
			master_volume_phone = ratio;

			Scene().GetSoundSystem()->setMasterVolume(master_volume_phone);
			Scene().GetComponent<JZEngine::Transform>("Option_master_brownbar")->scale_.x = ratio * initial_bar_scale_phone;
			Scene().GetComponent<JZEngine::Transform>("Option_master_pau")->position_.x = initial_bar_position_phone + ratio * 670.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_music_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_phone) / 670.0f;
			ratio = std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold_phone)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold_phone)
			{
				ratio = 1.0f;
			}
			music_volume_phone = ratio;
			Scene().GetSoundSystem()->setBGMChannelGroupVolume(music_volume_phone);
			Scene().GetComponent<JZEngine::Transform>("Option_music_brownbar")->scale_.x = ratio * initial_bar_scale_phone;
			Scene().GetComponent<JZEngine::Transform>("Option_music_pau")->position_.x = initial_bar_position_phone + ratio * 670.0f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_sfx_bb"))
	{
		if (e->on_held_)
		{
			float ratio = (JZEngine::Camera::mouse_world_position_.x - initial_bar_position_phone) / 670.0f;
			ratio = std::clamp(ratio, 0.0f, 1.0f);
			if (ratio < mute_threshold_phone)
			{
				ratio = 0.0f;
			}
			else if (ratio > 1.0f - mute_threshold_phone)
			{
				ratio = 1.0f;
			}
			sfx_volume_phone = ratio;
			Scene().GetSoundSystem()->setEffectsChannelGroupVolume(sfx_volume_phone);
			Scene().GetComponent<JZEngine::Transform>("Option_sfx_brownbar")->scale_.x = ratio * initial_bar_scale_phone;
			Scene().GetComponent<JZEngine::Transform>("Option_sfx_pau")->position_.x = initial_bar_position_phone + ratio * 670.0f;
		}
	}
	UpdateVolumeIcon(true);
}

void UpdateOptionMenu(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	UpdateVolSlider();
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Option_x"))
	{
		if (e->on_released_)
		{
			FlagOptionsScreen(false);
			Scene().EntityFlagActive("Credits", false);
			Scene().EntityFlagActive("Quit", false);
			current_app_state = HawkerAppState::MainScreen;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Credits"))
	{
		if (e->on_released_)
		{
			FlagCreditsScreen(true);
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
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Credits_x"))
	{
		if (e->on_released_)
		{
			FlagCreditsScreen(false);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Quit"))
	{
		if (e->on_released_)
		{
			//ToggleOptions(false);
			FlagQuitGameScreen(true);
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
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("QuitGame_yes"))
	{
		if (e->on_released_)
		{
			Scene().CloseApplication();
		}
		if (e->on_held_)
		{
			ToggleButton("QuitGame_yes", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("QuitGame_yes", ButtonState::Hover);
		}
		else
		{
			ToggleButton("QuitGame_yes", ButtonState::Normal);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("QuitGame_no"))
	{
		if (e->on_released_)
		{
			FlagQuitGameScreen(false);
		}
		if (e->on_held_)
		{
			ToggleButton("QuitGame_no", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("QuitGame_no", ButtonState::Hover);
		}
		else
		{
			ToggleButton("QuitGame_no", ButtonState::Normal);
		}
	}
}

void UpdateTheresapp( float dt )
{
	UNREFERENCED_PARAMETER( dt );
	FlagPhoneHomeScreen( false );
	FlagTheresappScreen( true );
	FlagMsg1( true );
	FlagMsg2( true );
	FlagMsg3( true );
	FlagMsg4( true );
	FlagMsg5( true );
	FlagMsg6( true );
	FlagMsg7( true );
	FlagMsg8( true );
	FlagMsg9( true );
	FlagMsg10( true );
	FlagMsg11( true );
	FlagMsg12( true );
	FlagMsg13( true );

	//Set control for scrolling down
	if ( Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_1_bg" )->position_.y > bottom_line ||
		 Scene().GetComponent<JZEngine::Transform>( "Last_page_msg_7_bg" )->position_.y < top_line )
	{
		scroll_up = true;
	}
	else
	{
		scroll_up = false;
	}

	//Set control for scrolling up
	if ( Scene().GetComponent<JZEngine::Transform>( "First_page_msg_13_bg" )->position_.y > upper_bound )
	{
		scroll_down = true;
	}
	else
	{
		scroll_down = false;
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
	}

	//If the message is out of the phone it will disappear
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

	if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( "Theresapp_back_arrow" ) )
	{
		if ( e->on_click_ )
		{
			FlagPhoneHomeScreen( true );
			FlagTheresappScreen( false );
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
		UpdateOptionMenu(dt);
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