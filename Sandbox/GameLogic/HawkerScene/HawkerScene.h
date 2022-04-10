/*	__FILE HEADER__
*	File:		HawkerScene.h
	Primary:	Zachary Tay
	Date:		19/06/21
	Brief:		Hawker scene logic.
*/

#pragma once
#include <JZEngine.h>
#include "HawkerQueue.h"
#include "HawkerApp.h"
#include <string>
#include <sstream>
#include <unordered_map>
#include <string>

#include "../ButtonLogic.h"
#include "../CutScene/CutScene.h"

/*
	GUIDED TUTORIAL - START
*/
std::unordered_map<std::string , bool> guided_circles {
	{"gtc_customer", false},
	{"gtc_platetray",false},
	{"gtc_tongsfood", false},
	{"gtc_platecustomer", false},
	{"gtc_scizzors", false},
	{"gtc_springsoy", false}
};


void HideGuidedCircles ()
{
	for ( auto& gc : guided_circles )
	{
		Scene ().GetComponent<JZEngine::NonInstanceShader> ( gc.first )->tint.w = 0;
		Scene ().EntityFlagActive ( gc.first , false );
	}
}

bool click_customer_notification { true };

void InitGuidedCircles ()
{
	HideGuidedCircles ();
	click_customer_notification = true;
}

void ToggleGuidedCircle ( std::string const& name , bool flag)
{
	assert ( guided_circles.find ( name ) != guided_circles.end () );
	guided_circles[ name ] = flag;
	if ( flag )
	{
		Scene ().EntityFlagActive ( name , flag );
	}
}

void UpdateGuidedCircle (float dt)
{
	for ( auto& gc : guided_circles )
	{
		if ( gc.second )
		{
			float& alpha = Scene ().GetComponent<JZEngine::NonInstanceShader> ( gc.first )->tint.w;
			if ( alpha < 1.0f )
			{
				alpha += dt;
			}
		}
		else
		{
			float& alpha = Scene ().GetComponent<JZEngine::NonInstanceShader> ( gc.first )->tint.w;
			if ( alpha > 0.0f )
			{
				alpha -= dt;
			}
			else
			{
				Scene ().EntityFlagActive ( gc.first , false );
			}
		}
	}
}

/*!
 * DAY RELATED - START
*/

void InitDay () 
{
	// side tray
	Scene ().EntityFlagActive ( "SideTray" , false );
	Scene ().EntityFlagActive ( "CharSiewBao" , false );
	Scene ().EntityFlagActive ( "bb_CharSiewBao" , false );
	Scene ().EntityFlagActive ( "DouShaBao" , false );
	Scene ().EntityFlagActive ( "bb_DouShaBao" , false );
	Scene ().EntityFlagActive ( "CofeeBao" , false );
	Scene ().EntityFlagActive ( "bb_CofeeBao" , false );
	Scene ().EntityFlagActive ( "PlainCCF" , false );
	Scene ().EntityFlagActive ( "bb_PlainCCF" , false );
	Scene ().EntityFlagActive ( "PrawnCCF" , false );
	Scene ().EntityFlagActive ( "bb_PrawnCCF" , false );
	
	// steamer
	Scene ().EntityFlagActive ( "RoundSteamer" , false );
	Scene ().EntityFlagActive ( "SiewMai" , false );
	Scene ().EntityFlagActive ( "bb_SiewMai" , false );
	Scene ().EntityFlagActive ( "HarGow" , false );
	Scene ().EntityFlagActive ( "bb_HarGow" , false );
	Scene ().EntityFlagActive ( "ChickenFeet" , false );
	Scene ().EntityFlagActive ( "bb_ChickenFeet" , false );

	// init day related stuff
	switch ( hawker_scene_day )
	{
	case ( DAY::ONE ):

	
		break;
	case ( DAY::TWO ):
		Scene ().EntityFlagActive ( "RoundSteamer" , true );
		Scene ().EntityFlagActive ( "SiewMai" , true );
		Scene ().EntityFlagActive ( "bb_SiewMai" , true );
		Scene ().EntityFlagActive ( "HarGow" , true );
		Scene ().EntityFlagActive ( "bb_HarGow" , true );
		Scene ().EntityFlagActive ( "ChickenFeet" , true );
		Scene ().EntityFlagActive ( "bb_ChickenFeet" , true );
		Scene ().EntityFlagActive ( "SideTray" , true );
		Scene ().EntityFlagActive ( "CharSiewBao" , true );
		Scene ().EntityFlagActive ( "bb_CharSiewBao" , true );
		Scene ().EntityFlagActive ( "DouShaBao" , true );
		Scene ().EntityFlagActive ( "bb_DouShaBao" , true );
		Scene ().EntityFlagActive ( "CofeeBao" , true );
		Scene ().EntityFlagActive ( "bb_CofeeBao" , true );
		break;
	case ( DAY::THREE ):
		// day 2
		Scene ().EntityFlagActive ( "RoundSteamer" , true );
		Scene ().EntityFlagActive ( "SiewMai" , true );
		Scene ().EntityFlagActive ( "bb_SiewMai" , true );
		Scene ().EntityFlagActive ( "HarGow" , true );
		Scene ().EntityFlagActive ( "bb_HarGow" , true );
		Scene ().EntityFlagActive ( "ChickenFeet" , true );
		Scene ().EntityFlagActive ( "bb_ChickenFeet" , true );
		Scene ().EntityFlagActive ( "SideTray" , true );
		Scene ().EntityFlagActive ( "CharSiewBao" , true );
		Scene ().EntityFlagActive ( "bb_CharSiewBao" , true );
		Scene ().EntityFlagActive ( "DouShaBao" , true );
		Scene ().EntityFlagActive ( "bb_DouShaBao" , true );
		Scene ().EntityFlagActive ( "CofeeBao" , true );
		Scene ().EntityFlagActive ( "bb_CofeeBao" , true );

		Scene ().EntityFlagActive ( "PlainCCF" , true );
		Scene ().EntityFlagActive ( "bb_PlainCCF" , true );
		Scene ().EntityFlagActive ( "PrawnCCF" , true );
		Scene ().EntityFlagActive ( "bb_PrawnCCF" , true );
		break;
	}
}

/*!
 * DAY RELATED - END
*/

enum class HawkerSceneState
{
	Main,
	Win,
	App,
	Shop,
	Goal,
	Lose
};
HawkerSceneState current_hawker_scene_state = HawkerSceneState::Main;

/*!
 * **********************************************************************
 * @brief CURSOR CODE - START
*/
enum class CursorState
{
	Nothing,
	EmptyTongs,
	Scizzors,
	Plate,
	TongsWanton,
	TongsSeaweedChicken,
	TongsSpringroll,
	TongsCarrotCake,
	TongsChickenFeet,
	TongsSteamDumpling,
	TongsSiewMai,
	TongsCharSiewBao,
	TongsDouShaBao,
	TongsCoffeeBao,
	TongsPlainCCF,
	TongsPrawnCCF,
	SpringOnion,
	SoySauce
};

std::string cursor_object_names[] = {
	"Nothing",
	"EmptyTongs",
	"ScizzorsCursor",
	"PlateCursor",
	"TongsDumpling",
	"TongsSeaweedChicken",
	"TongsSpringroll",
	"TongsCarrotCake",
	"TongsChickenFeet",
	"TongsSteamDumpling",
	"TongsSiewMai",
	"TongsCharSiewBao",
	"TongsDouShaBao",
	"TongsCoffeeBao",
	"TongsPlainCCF",
	"TongsPrawnCCF",
	"SpringOnionCursor",
	"SoySauceCursor"
};

CursorState cursor_state = CursorState::Nothing;


enum class Confirmstate
{
	Exit,
	Restart,
	None
};
Confirmstate confirm_state = Confirmstate::None;


void FlagAllCursorsFalse()
{
	Scene().EntityFlagActive("EmptyTongs", false);
	Scene().EntityFlagActive("TongsCarrotCake", false);
	Scene().EntityFlagActive("TongsDumpling", false);
	Scene().EntityFlagActive("TongsSeaweedChicken", false);
	Scene().EntityFlagActive("TongsSpringroll", false);

	// day 2 tongs
	Scene ().EntityFlagActive ( "TongsChickenFeet" , false );
	Scene ().EntityFlagActive ( "TongsSteamDumpling" , false );
	Scene ().EntityFlagActive ( "TongsSiewMai" , false );
	Scene ().EntityFlagActive ( "TongsCharSiewBao" , false );
	Scene ().EntityFlagActive ( "TongsDouShaBao" , false );
	Scene ().EntityFlagActive ( "TongsCoffeeBao" , false );

	// day 3 tongs
	Scene ().EntityFlagActive ( "TongsPlainCCF" , false );
	Scene ().EntityFlagActive ( "TongsPrawnCCF" , false );

	Scene().EntityFlagActive("ScizzorsCursor", false);
	Scene().EntityFlagActive("PlateCursor", false);

	Scene ().EntityFlagActive ( "SpringOnionCursor" , false );
	Scene ().EntityFlagActive ( "SoySauceCursor" , false );

	cursor_state = CursorState::Nothing;

	// set plate and tongs to non shadow
	Scene ().GetComponent<JZEngine::Texture> ( "Plate" )->texture_id_ = Scene ().GetTexture ( "Plate_Equipment_Hawker" );
	Scene ().GetComponent<JZEngine::Texture> ( "Tongs" )->texture_id_ = Scene ().GetTexture ( "Tongs_Equipment_hawker" );
}

void FlagCursorState(CursorState state)
{
	FlagAllCursorsFalse();
	cursor_state = state;
	Scene().EntityFlagActive(cursor_object_names[static_cast<int>(cursor_state)], true);


	if ( state == CursorState::Plate )
	{
		Scene ().GetComponent<JZEngine::Texture> ( "Plate" )->texture_id_ = Scene ().GetTexture ( "Plate(Shaded)_Equipment_hawker" );
	}
	if ( state == CursorState::EmptyTongs || 
		state == CursorState::TongsCarrotCake ||
		state == CursorState::TongsSeaweedChicken ||
		state == CursorState::TongsSpringroll ||
		state == CursorState::TongsWanton ||
		state == CursorState::TongsChickenFeet ||
		state == CursorState::TongsSteamDumpling || 
		state == CursorState::TongsSiewMai ||
		state == CursorState::TongsCharSiewBao ||
		state == CursorState::TongsDouShaBao ||
		state == CursorState::TongsCoffeeBao ||
		state == CursorState::TongsPlainCCF ||
		state == CursorState::TongsPrawnCCF )
	{
		Scene ().GetComponent<JZEngine::Texture> ( "Tongs" )->texture_id_ = Scene ().GetTexture ( "Tongs(Shaded)_Equipment_hawker" );
	}
}

bool CheckCursorState(CursorState state)
{
	return state == cursor_state;
}

void ResetCursors();

void ShowNotification ( int i );
void ProcessDay2Item (CursorState state , const char* bb, const char* foodObject, unsigned int& count, const char* tex1, const char* tex2)
{
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( bb ) )
	{
		if ( e->on_click_ )
		{
			ShowNotification ( 3 );
			if ( CheckCursorState ( CursorState::EmptyTongs ) )
			{
				if ( count > 1 )
				{
					JZEngine::Log::Info ( "Main" , "{} Selected" , foodObject );
					FlagCursorState ( state );
					--count;
					std::stringstream ss;
					ss << tex1 << count << tex2;
					Scene ().GetComponent<JZEngine::Texture> ( foodObject )->texture_id_ = Scene ().GetTexture ( ss.str () );
				}
				else if ( count == 1 )
				{
					JZEngine::Log::Info ( "Main" , "{} Selected" , foodObject );
					FlagCursorState ( state );
					--count;
					Scene ().EntityFlagActive ( foodObject , false );
				}
			}
			else if ( CheckCursorState ( state ) )
			{
				if ( count > 0 )
				{
					JZEngine::Log::Info ( "Main" , "{} Returned" , foodObject );
					FlagCursorState ( CursorState::EmptyTongs );
					++count;
					std::stringstream ss;
					ss << tex1 << count << tex2;
					Scene ().GetComponent<JZEngine::Texture> ( foodObject )->texture_id_ = Scene ().GetTexture ( ss.str () );
				}
				else
				{
					JZEngine::Log::Info ( "Main" , "{} Returned" , foodObject );
					FlagCursorState ( CursorState::EmptyTongs );
					++count;
					Scene ().EntityFlagActive ( foodObject , true );
				}
			}
		}
	}
}

/*!
 * @brief CURSOR CODE - END
 * **********************************************************************
*/

/*!
 * **********************************************************************
*  @brief SKY - START
*/

float night_controller_value { 1.0f };
float max_night_sky_tint { 1.0f };
float day_time { 5.0f };
bool day_begin { false };

void InitSky ()
{
	night_controller_value = 1.0f;
	max_night_sky_tint = 1.0f;
	day_time = 5.0f;
	day_begin = false;

	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Clouds" )->tint = { 1.0f,1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "NightSky" )->tint.w = 0.0f;
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "NightHue" )->tint.w = 0.0f;
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "EveningHue" )->tint.w = 0.0f;
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Moon" )->tint.w = 0.0f;
}

void BringNightSky (float dt)
{
	float& night_sky_alpha = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "NightSky" )->tint.w;
	float& cloud_red = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Clouds" )->tint.x;
	float& cloud_green = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Clouds" )->tint.y;
	float& cloud_blue = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Clouds" )->tint.z;
	float& night_hue = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "NightHue" )->tint.w;
	float& evening_hue = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "EveningHue" )->tint.w;
	float& moon_alpha = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Moon" )->tint.w;
	if ( night_controller_value > 0.0f )
	{
		float delta_sky = dt * (1.0f/30.0f);
		night_controller_value -= delta_sky;
		night_sky_alpha += delta_sky * 0.6f;
		cloud_red -= delta_sky * 1.8f;
		cloud_blue += delta_sky * 1.7f;
		cloud_green -= delta_sky * 1.5f;
		moon_alpha += delta_sky * 0.6f;
		if ( night_controller_value > 0.75f )
		{
			evening_hue += delta_sky * 1.1f;
			night_hue += delta_sky * 0.05f;
		}
		else
		{
			evening_hue -= delta_sky * 0.8f;
			night_hue += delta_sky * 0.20f;
		}
	}
}

/*!
*  @brief SKY - END
 * **********************************************************************
*/

/*!
 * **********************************************************************
 * @brief BEGIN GOAL - START
*/

void FlagGoalActive ( bool flag )
{
	Scene ().EntityFlagActive ( "Black_goal" , flag );
	Scene ().EntityFlagActive ( "Goal_one" , flag );
	Scene ().EntityFlagActive ( "Goal_two" , flag );
	Scene ().EntityFlagActive ( "Goal_three" , flag );
}

unsigned int goal_phase { 0 };
bool end_goal { false };

void InitGoal ()
{
	goal_phase = 0;
	end_goal = false;
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Black_goal" )->tint.w = 0.0f;
	Scene ().EntityFlagActive ( "Goal_one" , true );
	Scene ().EntityFlagActive ( "Goal_two" , false );
	Scene ().EntityFlagActive ( "Goal_three" , false );
	Scene ().GetComponent<JZEngine::Transform> ( "Goal_one" )->position_.x = -2048.0f;
	Scene ().GetComponent<JZEngine::Transform> ( "Goal_three" )->position_.x = 0.0f;
}

void UpdateGoal (float dt)
{
	float& bg_alpha = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Black_goal" )->tint.w;
	float& goal_x = Scene ().GetComponent<JZEngine::Transform> ( "Goal_one" )->position_.x;
	float& goal3_x = Scene ().GetComponent<JZEngine::Transform> ( "Goal_three" )->position_.x;
	switch ( goal_phase )
	{
	case ( 0 ):
		if ( bg_alpha < 1.0f )
		{
			bg_alpha += dt;
		}
		else
		{
			++goal_phase;
		}
		break;
	case ( 1 ):
		if ( goal_x < 0.0f )
		{
			goal_x += 2048.0f * dt;
		}
		else if ( JZEngine::InputHandler::IsMouseReleased ( JZEngine::MOUSE::MOUSE_BUTTON_1 ) )
		{
			Scene ().EntityFlagActive ( "Goal_one" , false );
			Scene ().EntityFlagActive ( "Goal_two" , true );
			++goal_phase;
		}
		break;
	case ( 2 ):
		if ( JZEngine::InputHandler::IsMouseReleased ( JZEngine::MOUSE::MOUSE_BUTTON_1 ) )
		{
			Scene ().EntityFlagActive ( "Goal_two" , false );
			Scene ().EntityFlagActive ( "Goal_three" , true );
			++goal_phase;
		}
		break;
	case ( 3 ):
		if ( JZEngine::InputHandler::IsMouseReleased ( JZEngine::MOUSE::MOUSE_BUTTON_1 ) && !end_goal )
		{
			end_goal = true;
		}
		if ( end_goal )
		{
			if ( goal3_x < 2048.0f * 2.0f )
			{
				goal3_x += 2048.0f * dt;
			}
			else if ( bg_alpha > 0.0f )
			{
				bg_alpha -= dt;
			}
			else
			{
				FlagGoalActive ( false );
				current_hawker_scene_state = HawkerSceneState::Shop;
			}
		}
		break;
	}
}

/*!
 * @brief BEGIN SHOP - END
 * **********************************************************************
*/

/*!
 * **********************************************************************
	SHOP TRANSITION - START
*/

bool phone_transition_play { false };
bool phone_icon_open { false };
float phone_icon_value { 0.0f };
float transition_speed { 4.0f };
float phone_transition_sx { 8.5f } , phone_transition_sy { 8.3f };
float phone_icon_x { -854.0f } , phone_icon_y { 470.0f };

void StartPhoneTransition ( bool open )
{
	phone_transition_play = true;
	Scene ().EntityFlagActive ( "PhoneTransition" , true );
	Scene ().EntityFlagActive ( "Phone_black_bg" , true );
	phone_icon_open = open;
}

void UpdatePhoneTransition ( float dt )
{
	if ( phone_transition_play )
	{
		if ( phone_icon_open )
		{
			if ( phone_icon_value < 1.0f )
			{
				phone_icon_value += dt * transition_speed;
			}
			else
			{
				// done opening
				phone_transition_play = false;
				Scene ().EntityFlagActive ( "PhoneTransition" , false );
				current_hawker_scene_state = HawkerSceneState::App;
			}
		}
		else
		{
			if ( phone_icon_value > 0.1f )
			{
				phone_icon_value -= dt * transition_speed;
			}
			else
			{
				// done closing
				phone_transition_play = false;
				Scene ().EntityFlagActive ( "PhoneTransition" , false );
				current_hawker_scene_state = HawkerSceneState::Main;
				Scene ().EntityFlagActive ( "Phone_black_bg" , false );

				/*FlagPhone ( false );
				FlagPhoneHomeScreen ( false );
				Scene ().EntityFlagActive ( "PhoneOptions" , true );*/
			}
		}

		JZEngine::Vec2f& scale = Scene ().GetComponent<JZEngine::Transform> ( "PhoneTransition" )->scale_;
		scale.x = phone_transition_sx * phone_icon_value;
		scale.y = phone_transition_sy * phone_icon_value;

		JZEngine::Vec2f& position = Scene ().GetComponent<JZEngine::Transform> ( "PhoneTransition" )->position_;
		position.x = phone_icon_x * ( 1 - phone_icon_value );
		position.y = phone_icon_y * ( 1 - phone_icon_value );

		Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Phone_black_bg" )->tint.w = phone_icon_value;
	}
}

/*!
	SHOP TRANSITION - END
 * **********************************************************************
*/


/*!
 * **********************************************************************
 * @brief BEGIN SHOP - START
*/

void FlagShopActive ( bool flag )
{
	if ( flag )
	{
		Scene ().EntityFlagActive ( "BeginBlack" , flag );
		Scene ().EntityFlagActive ( "BeginShop_Exit" , flag );
		Scene ().EntityFlagActive ( "BeginShop_Next" , flag );
		
		
		Scene ().EntityFlagActive ( "shop_exit" , flag );
		Scene ().EntityFlagActive ( "shop_next" , flag );

		Scene ().EntityFlagActive ( "Total_amt" , flag );
		Scene ().EntityFlagActive ( "Wallet_amt" , flag );

		if ( hawker_scene_day == DAY::ONE )
		{
			Scene ().EntityFlagActive ( "BeginShop" , flag );
			Scene ().EntityFlagActive ( "Shop_a_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop_s_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop_a_seaweedchickenl" , flag );
			Scene ().EntityFlagActive ( "Shop_s_seaweedchickenl" , flag );
			Scene ().EntityFlagActive ( "Shop_a_dumpling" , flag );
			Scene ().EntityFlagActive ( "Shop_s_dumpling" , flag );
			Scene ().EntityFlagActive ( "Shop_a_carrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop_s_carrotcake" , flag );

			Scene ().EntityFlagActive ( "Springroll_amt" , flag );
			Scene ().EntityFlagActive ( "Seaweedchicken_amt" , flag );
			Scene ().EntityFlagActive ( "Dumpling_amt" , flag );
			Scene ().EntityFlagActive ( "Carrotcake_amt" , flag );
			Scene().EntityFlagActive("ScrollDay1_mouse", flag);
			Scene().EntityFlagActive("ScrollDay1", flag);

		}
		else if ( hawker_scene_day == DAY::TWO )
		{
			Scene ().EntityFlagActive ( "BeginShop2" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_seaweedchicken" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_frieddumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_friedcarrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_charsiewbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_redbeanbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_coffeebun" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_chickendumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_prawndumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_chickenfeet" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_seaweedchicken" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_frieddumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_friedcarrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_charsiewbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_redbeanbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_coffeebun" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_chickendumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_prawndumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_chickenfeet" , flag );

			Scene ().EntityFlagActive ( "Shop2_amt_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_seaweedchicken" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_frieddumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_friedcarrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_charsiewbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_redbeanbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_coffeebun" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_chickendumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_prawndumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_chickenfeet" , flag );
			Scene().EntityFlagActive("ScrollDay2_mouse", flag);
			Scene().EntityFlagActive("ScrollDay2", flag);
		}
		else if ( hawker_scene_day == DAY::THREE )
		{
			Scene ().EntityFlagActive ( "BeginShop3" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_seaweedchicken" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_frieddumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_friedcarrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_charsiewbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_redbeanbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_coffeebun" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_chickendumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_prawndumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_a_chickenfeet" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_seaweedchicken" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_frieddumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_friedcarrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_charsiewbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_redbeanbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_coffeebun" , flag );
			Scene ().EntityFlagActive ( "Shop2_s_chickendumpling" , flag );

			Scene ().EntityFlagActive ( "Shop2_amt_springroll" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_seaweedchicken" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_frieddumpling" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_friedcarrotcake" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_charsiewbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_redbeanbun" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_coffeebun" , flag );
			Scene ().EntityFlagActive ( "Shop2_amt_chickendumpling" , flag );

			Scene ().EntityFlagActive ( "Shop3_a_plainccf" , flag );
			Scene ().EntityFlagActive ( "Shop3_a_prawnccf" , flag );
			Scene ().EntityFlagActive ( "Shop3_a_hargao" , flag );
			Scene ().EntityFlagActive ( "Shop3_a_chickenfeet" , flag );
			Scene ().EntityFlagActive ( "Shop3_s_plainccf" , flag );
			Scene ().EntityFlagActive ( "Shop3_s_prawnccf" , flag );
			Scene ().EntityFlagActive ( "Shop3_s_hargao" , flag );
			Scene ().EntityFlagActive ( "Shop3_s_chickenfeet" , flag );

			Scene ().EntityFlagActive ( "Shop3_amt_plainccf" , flag );
			Scene ().EntityFlagActive ( "Shop3_amt_prawnccf" , flag );
			Scene ().EntityFlagActive ( "Shop3_amt_hargao" , flag );
			Scene ().EntityFlagActive ( "Shop3_amt_chickenfeet" , flag );
			Scene().EntityFlagActive("ScrollDay3_mouse", flag);
			Scene().EntityFlagActive("ScrollDay3", flag);
		}
	}
	else
	{
		// day 1
		Scene ().EntityFlagActive ( "BeginShop" , flag );
		Scene ().EntityFlagActive ( "BeginBlack" , flag );
		Scene ().EntityFlagActive ( "Shop_a_springroll" , flag );
		Scene ().EntityFlagActive ( "Shop_s_springroll" , flag );
		Scene ().EntityFlagActive ( "Shop_a_seaweedchickenl" , flag );
		Scene ().EntityFlagActive ( "Shop_s_seaweedchickenl" , flag );
		Scene ().EntityFlagActive ( "Shop_a_dumpling" , flag );
		Scene ().EntityFlagActive ( "Shop_s_dumpling" , flag );
		Scene ().EntityFlagActive ( "Shop_a_carrotcake" , flag );
		Scene ().EntityFlagActive ( "Shop_s_carrotcake" , flag );
		Scene ().EntityFlagActive ( "BeginShop_Exit" , flag );
		Scene ().EntityFlagActive ( "BeginShop_Next" , flag );

		Scene ().EntityFlagActive ( "Springroll_amt" , flag );
		Scene ().EntityFlagActive ( "Seaweedchicken_amt" , flag );
		Scene ().EntityFlagActive ( "Dumpling_amt" , flag );
		Scene ().EntityFlagActive ( "Carrotcake_amt" , flag );
		Scene ().EntityFlagActive ( "Total_amt" , flag );
		Scene ().EntityFlagActive ( "Wallet_amt" , flag );
		Scene().EntityFlagActive("ScrollDay1_mouse", flag);
		Scene().EntityFlagActive("ScrollDay1", flag);

		Scene ().EntityFlagActive ( "shop_exit" , flag );
		Scene ().EntityFlagActive ( "shop_next" , flag );

		// day 2
		Scene ().EntityFlagActive ( "BeginShop2" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_springroll" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_seaweedchicken" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_frieddumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_friedcarrotcake" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_charsiewbun" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_redbeanbun" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_coffeebun" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_chickendumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_prawndumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_a_chickenfeet" , flag );
		Scene ().EntityFlagActive ( "Shop2_s_springroll" , flag );
		Scene ().EntityFlagActive ( "Shop2_s_seaweedchicken" , flag );
		Scene ().EntityFlagActive ( "Shop2_s_frieddumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_s_friedcarrotcake" , flag );
		Scene ().EntityFlagActive ( "Shop2_s_charsiewbun"		, flag );
		Scene ().EntityFlagActive ( "Shop2_s_redbeanbun"		, flag );
		Scene ().EntityFlagActive ( "Shop2_s_coffeebun"			, flag );
		Scene ().EntityFlagActive ( "Shop2_s_chickendumpling"	, flag );
		Scene ().EntityFlagActive ( "Shop2_s_prawndumpling"		, flag );
		Scene ().EntityFlagActive ( "Shop2_s_chickenfeet"		, flag );

		Scene ().EntityFlagActive ( "Shop2_amt_springroll" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_seaweedchicken" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_frieddumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_friedcarrotcake" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_charsiewbun" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_redbeanbun" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_coffeebun" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_chickendumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_prawndumpling" , flag );
		Scene ().EntityFlagActive ( "Shop2_amt_chickenfeet" , flag );
		Scene().EntityFlagActive("ScrollDay2_mouse", flag);
		Scene().EntityFlagActive("ScrollDay2", flag);

		// day 3
		Scene ().EntityFlagActive ( "BeginShop3" , flag );
		Scene ().EntityFlagActive ( "Shop3_a_plainccf" , flag );
		Scene ().EntityFlagActive ( "Shop3_a_prawnccf" , flag );
		Scene ().EntityFlagActive ( "Shop3_a_hargao" , flag );
		Scene ().EntityFlagActive ( "Shop3_a_chickenfeet" , flag );
		Scene ().EntityFlagActive ( "Shop3_s_plainccf" , flag );
		Scene ().EntityFlagActive ( "Shop3_s_prawnccf" , flag );
		Scene ().EntityFlagActive ( "Shop3_s_hargao" , flag );
		Scene ().EntityFlagActive ( "Shop3_s_chickenfeet" , flag );

		Scene ().EntityFlagActive ( "Shop3_amt_plainccf" , flag );
		Scene ().EntityFlagActive ( "Shop3_amt_prawnccf" , flag );
		Scene ().EntityFlagActive ( "Shop3_amt_hargao" , flag );
		Scene ().EntityFlagActive ( "Shop3_amt_chickenfeet" , flag );

		Scene ().EntityFlagActive ( "no_money" , flag );
		Scene ().GetComponent<JZEngine::Transform> ( "no_money" )->scale_ = { 0.01f,0.01f };
		
		Scene().EntityFlagActive("ScrollDay3_mouse", flag);
		Scene().EntityFlagActive("ScrollDay3", flag);
	}
}

void ProcessShopItem (const char* addEvent, const char* subEvent, const char* name, unsigned int& count, unsigned int const& maxCount, unsigned int const& minCount = 1)
{
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( addEvent ) )
	{
		if ( e->on_released_ )
		{
			if ( count < maxCount )
				++count;
			else
			{
				count = minCount;
			}
			std::stringstream ss;
			ss << count;
			Scene ().GetComponent<JZEngine::TextData> ( name )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( name )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( subEvent ) )
	{
		if ( e->on_released_ )
		{
			if ( count > minCount )
				--count;
			else
			{
				count = maxCount;
			}
			std::stringstream ss;
			ss << count;
			Scene ().GetComponent<JZEngine::TextData> ( name )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( name )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
}

void SetUIntTextAmt ( char const* text , unsigned int const& i )
{
	std::stringstream ss;
	ss << i;
	Scene ().GetComponent<JZEngine::TextData> ( text )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( text )->text = JZEngine::String ( ss.str ().c_str () );
}

void SetUIntTexture ( char const* name , char const* pre , char const* post , unsigned int i )
{
	std::stringstream ss;
	ss << pre << i << post;
	Scene ().GetComponent<JZEngine::Texture> ( name )->texture_id_ = Scene ().GetTexture ( ss.str () );
}

unsigned int springroll_count { 5 };
unsigned int carrotcake_count { 5 };
unsigned int wanton_count { 5 };
unsigned int seaweedchicken_count { 5 };

unsigned int init_springroll_count { 0 };
unsigned int init_carrotcake_count { 0 };
unsigned int init_wanton_count { 0 };
unsigned int init_seaweedchicken_count { 0 };

// day 2 foods
unsigned int chickenfeet_count { 3 };
unsigned int hargao_count { 3 };
unsigned int siewmai_count { 3 };
unsigned int charsiewbao_count { 3 };
unsigned int doushabao_count { 3 };
unsigned int coffeebao_count { 3 };

unsigned int init_chickenfeet_count { 0 };
unsigned int init_hargao_count { 0 };
unsigned int init_siewmai_count { 0 };
unsigned int init_charsiewbao_count { 0 };
unsigned int init_doushabao_count { 0 };
unsigned int init_coffeebao_count { 0 };

// day 3 foods
unsigned int plainccf_count { 5 };
unsigned int prawnccf_count { 5 };

unsigned int init_plainccf_count { 0 };
unsigned int init_prawnccf_count { 0 };
//day1
unsigned int summary_sr_count { 0 };
unsigned int summary_sc_count { 0 };
unsigned int summary_fd_count { 0 };
unsigned int summary_cc_count { 0 };
//day2
unsigned int summary_csb_count{ 0 };
unsigned int summary_rbb_count{ 0 };
unsigned int summary_cb_count{ 0 };
unsigned int summary_pd_count{ 0 };
unsigned int summary_cf_count{ 0 };
unsigned int summary_cd_count{ 0 };
//day3
unsigned int summary_pr_count{ 0 };
unsigned int summary_rnr_count{ 0 };


unsigned int min_count { 1 };
unsigned int max_count { 9 };

// price of food
float springroll_cost { 0.40f };
float seaweedchicken_cost { 0.20f };
float frieddumpling_cost { 0.30f };
float friedcarrotcake_cost { 0.50f };
float chickendumpling_cost { 0.50f };
float prawndumpling_cost { 0.60f };
float chickenfeet_cost { 0.60f };
float charsiewbun_cost { 0.30f };
float redbeanbun_cost { 0.20f };
float coffeebun_cost { 0.20f };
float ricenoodleroll_cost { 0.30f };
float prawnroll_cost { 0.60f };

float total_amt { 0.0f };
float wallet_amt { 12.50f };

bool no_money { false };
float no_money_display_time { 2.0f };
float no_money_display_timer { 0.0f };

void UpdateShop (float dt)
{
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "BeginShop_Next" ) )
	{
		if ( total_amt <= wallet_amt )
		{
			if ( e->on_released_ )
			{
				std::stringstream springroll_name;
				springroll_name << "DryFoodSpringRoll(" << springroll_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "SpringRoll" )->texture_id_ = Scene ().GetTexture ( springroll_name.str () );

				std::stringstream wanton_name;
				wanton_name << "DryFoodFriedDumplings(" << wanton_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "Dumpling" )->texture_id_ = Scene ().GetTexture ( wanton_name.str () );

				std::stringstream seaweedchicken_name;
				seaweedchicken_name << "DryFoodSeaweedChicken(" << seaweedchicken_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "SeaweedChick" )->texture_id_ = Scene ().GetTexture ( seaweedchicken_name.str () );

				std::stringstream carrotcake_name;
				carrotcake_name << "DryFoodCarrotCake(" << carrotcake_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "CarrotCake" )->texture_id_ = Scene ().GetTexture ( carrotcake_name.str () );

				SetUIntTexture ( "CharSiewBao" , "CharSiewBao(" , ")_Equipment_hawker" , charsiewbao_count );
				SetUIntTexture ( "DouShaBao" , "DouBao(" , ")_Equipment_hawker" , doushabao_count );
				SetUIntTexture ( "CofeeBao" , "CoffeeBao(" , ")_Equipment_hawker" , coffeebao_count );
				SetUIntTexture ( "ChickenFeet" , "RoundSteamerFeet" , "_Equipment_hawker" , chickenfeet_count );
				SetUIntTexture ( "HarGow" , "RoundSteamerDumpling" , "_Equipment_hawker" , hargao_count );
				SetUIntTexture ( "SiewMai" , "RoundSteamerSiuMai" , "_Equipment_hawker" , siewmai_count );
				SetUIntTexture ( "PlainCCF" , "PlainCCF(" , ")_Equipment_hawker" , plainccf_count );
				SetUIntTexture ( "PrawnCCF" , "PrawnCCF(" , ")_Equipment_hawker" , prawnccf_count );

				FlagShopActive ( false );
				current_hawker_scene_state = HawkerSceneState::Main;

				init_springroll_count = springroll_count;
				init_carrotcake_count = carrotcake_count;
				init_wanton_count = wanton_count;
				init_seaweedchicken_count = seaweedchicken_count;

				wallet_amt -= total_amt;

				day_begin = true;
			}
		}
		else
		{
			// say cant purchase
			if ( e->on_released_ )
			{
				Scene ().EntityFlagActive ( "no_money" , true );
				no_money = true;
			}
		}
		if ( e->on_held_ )
		{
			ToggleButton ( "shop_next" , ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton ( "shop_next" , ButtonState::Hover );
		}
		else
		{
			ToggleButton ( "shop_next" , ButtonState::Normal );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "BeginShop_Exit" ) )
	{
		if ( e->on_released_ )
		{
			Scene ().ChangeScene ( "MainMenu" );
		}
		if ( e->on_held_ )
		{
			ToggleButton ( "shop_exit" , ButtonState::Clicked );
		}
		else if ( e->on_hover_ )
		{
			ToggleButton ( "shop_exit" , ButtonState::Hover );
		}
		else
		{
			ToggleButton ( "shop_exit" , ButtonState::Normal );
		}
	}
	if ( no_money )
	{
		if ( no_money_display_timer < no_money_display_time )
		{
			no_money_display_timer += dt;
		}
		else
		{
			no_money = false;
			no_money_display_timer = 0.0f;
		}

		JZEngine::Vec2f& scale = Scene ().GetComponent<JZEngine::Transform> ( "no_money" )->scale_;
		if ( scale.x < 1.0f )
		{
			scale.x += dt * 3.0f;
			scale.y = scale.x;
		}
	}
	else
	{
		JZEngine::Vec2f& scale = Scene ().GetComponent<JZEngine::Transform> ( "no_money" )->scale_;
		if ( scale.x > 0.01f )
		{
			scale.x -= dt * 3.0f;
			scale.y = scale.x;	
		}
		else
		{
			Scene ().EntityFlagActive ( "no_money" , false );
		}
	}

	// day 1 shop
	// spring roll
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_a_springroll" ) )
	{
		if ( e->on_released_ )
		{
			if ( springroll_count < max_count )
				++springroll_count;
			else
			{
				springroll_count = min_count;
			}
			std::stringstream ss;
			ss << springroll_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Springroll_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Springroll_amt" )->text = JZEngine::String ( ss.str ().c_str() );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_s_springroll" ) )
	{
		if ( e->on_released_ )
		{
			if ( springroll_count > min_count )
				--springroll_count;
			else
			{
				springroll_count = max_count;
			}
			std::stringstream ss;
			ss << springroll_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Springroll_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Springroll_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	// seaweed chicken
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_a_seaweedchickenl" ) )
	{
		if ( e->on_released_ )
		{
			if ( seaweedchicken_count < max_count )
				++seaweedchicken_count;
			else
			{
				seaweedchicken_count = min_count;
			}
			std::stringstream ss;
			ss << seaweedchicken_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Seaweedchicken_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Seaweedchicken_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_s_seaweedchickenl" ) )
	{
		if ( e->on_released_ )
		{
			if ( seaweedchicken_count > min_count )
				--seaweedchicken_count;
			else
			{
				seaweedchicken_count = max_count;
			}
			std::stringstream ss;
			ss << seaweedchicken_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Seaweedchicken_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Seaweedchicken_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	// dumpling
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_a_dumpling" ) )
	{
		if ( e->on_released_ )
		{
			if ( wanton_count < max_count )
				++wanton_count;
			else
			{
				wanton_count = min_count;
			}
			std::stringstream ss;
			ss << wanton_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Dumpling_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Dumpling_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_s_dumpling" ) )
	{
		if ( e->on_released_ )
		{
			if ( wanton_count > min_count )
				--wanton_count;
			else
			{
				wanton_count = max_count;
			}
			std::stringstream ss;
			ss << wanton_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Dumpling_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Dumpling_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	// carrotcake
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_a_carrotcake" ) )
	{
		if ( e->on_released_ )
		{
			if ( carrotcake_count < max_count )
				++carrotcake_count;
			else
			{
				carrotcake_count = min_count;
			}
			std::stringstream ss;
			ss << carrotcake_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_s_carrotcake" ) )
	{
		if ( e->on_released_ )
		{
			if ( carrotcake_count > min_count )
				--carrotcake_count;
			else
			{
				carrotcake_count = max_count;
			}
			std::stringstream ss;
			ss << carrotcake_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("ScrollDay1_mouse"))
	{
		JZEngine::Animation2D* scroll = Scene().GetComponent<JZEngine::Animation2D>("ScrollDay1");
		if (e->on_hover_)
		{
			scroll->pause_ = false;
			scroll->reverse_ = false;
			if (scroll->frame_ == 9)
				scroll->pause_ = true;
		}

		else
		{
			if (scroll->frame_ >0)
			{
				scroll->reverse_ = true;
				scroll->pause_ = false;
			}
			else
			{
				scroll->frame_ = 0;
				scroll->pause_ = true;
			}
		}

	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("ScrollDay2_mouse"))
	{
		JZEngine::Animation2D* scroll = Scene().GetComponent<JZEngine::Animation2D>("ScrollDay2");
		if (e->on_hover_)
		{
			scroll->pause_ = false;
			scroll->reverse_ = false;
			if (scroll->frame_ == 9)
				scroll->pause_ = true;
		}
		else
		{
			if (scroll->frame_ > 0)
			{
				scroll->reverse_ = true;
				scroll->pause_ = false;
			}
			else
			{
				scroll->frame_ = 0;
				scroll->pause_ = true;
			}
		}
	}
	
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("ScrollDay3_mouse"))
	{
		JZEngine::Animation2D* scroll = Scene().GetComponent<JZEngine::Animation2D>("ScrollDay3");
		if (e->on_hover_)
		{
			scroll->pause_ = false;
			scroll->reverse_ = false;
			if (scroll->frame_ == 9)
				scroll->pause_ = true;
		}
		else
		{
			if (scroll->frame_ > 0)
			{
				scroll->reverse_ = true;
				scroll->pause_ = false;
			}
			else
			{
				scroll->frame_ = 0;
				scroll->pause_ = true;
			}
		}
	}
	
	// day 2 shop
	ProcessShopItem ( "Shop2_a_springroll" , "Shop2_s_springroll" , "Shop2_amt_springroll" , springroll_count , max_count , min_count );
	ProcessShopItem ( "Shop2_a_seaweedchicken" , "Shop2_s_seaweedchicken" , "Shop2_amt_seaweedchicken" , seaweedchicken_count , max_count , min_count );
	ProcessShopItem ( "Shop2_a_frieddumpling" , "Shop2_s_frieddumpling" , "Shop2_amt_frieddumpling" , wanton_count , max_count , min_count );
	ProcessShopItem ( "Shop2_a_friedcarrotcake" , "Shop2_s_friedcarrotcake" , "Shop2_amt_friedcarrotcake" , carrotcake_count , max_count , min_count );
	ProcessShopItem ( "Shop2_a_charsiewbun" , "Shop2_s_charsiewbun" , "Shop2_amt_charsiewbun" , charsiewbao_count , 3 , min_count );
	ProcessShopItem ( "Shop2_a_redbeanbun" , "Shop2_s_redbeanbun" , "Shop2_amt_redbeanbun" , doushabao_count , 3 , min_count );
	ProcessShopItem ( "Shop2_a_coffeebun" , "Shop2_s_coffeebun" , "Shop2_amt_coffeebun" , coffeebao_count , 3 , min_count );
	ProcessShopItem ( "Shop2_a_chickendumpling" , "Shop2_s_chickendumpling" , "Shop2_amt_chickendumpling" , siewmai_count , 3 , min_count );
	ProcessShopItem ( "Shop2_a_prawndumpling" , "Shop2_s_prawndumpling" , "Shop2_amt_prawndumpling" , hargao_count , 3 , min_count );
	ProcessShopItem ( "Shop2_a_chickenfeet" , "Shop2_s_chickenfeet" , "Shop2_amt_chickenfeet" , chickenfeet_count , 3 , min_count );

	// day 3 shop
	ProcessShopItem ( "Shop3_a_hargao" , "Shop3_s_hargao" , "Shop3_amt_hargao" , hargao_count , 3 , min_count );
	ProcessShopItem ( "Shop3_a_chickenfeet" , "Shop3_s_chickenfeet" , "Shop3_amt_chickenfeet" , chickenfeet_count , 3 , min_count );
	ProcessShopItem ( "Shop3_a_plainccf" , "Shop3_s_plainccf" , "Shop3_amt_plainccf" , plainccf_count , max_count , min_count );
	ProcessShopItem ( "Shop3_a_prawnccf" , "Shop3_s_prawnccf" , "Shop3_amt_prawnccf" , prawnccf_count , max_count , min_count );

	total_amt = springroll_cost * springroll_count + seaweedchicken_cost * seaweedchicken_count + frieddumpling_cost * wanton_count + friedcarrotcake_cost * carrotcake_count;

	if ( hawker_scene_day == DAY::TWO || hawker_scene_day == DAY::THREE )
	{
		total_amt += chickendumpling_cost * siewmai_count + prawndumpling_cost * hargao_count + chickenfeet_cost * chickenfeet_count;
	}
	if ( hawker_scene_day == DAY::THREE )
	{
		total_amt += charsiewbun_cost * charsiewbao_count + redbeanbun_cost * doushabao_count + coffeebun_cost * coffeebao_count +
			ricenoodleroll_cost * plainccf_count + prawnroll_cost * prawnccf_count;
	}

	std::stringstream ss;
	ss << "$" << std::setprecision (2) << std::fixed << total_amt;
	Scene ().GetComponent<JZEngine::TextData> ( "Total_amt" )->color_ = { 0.0f,0.0f,0.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Total_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	ss.str ( "" );
	ss << "$" << std::setprecision ( 2 ) << std::fixed << wallet_amt;
	Scene ().GetComponent<JZEngine::TextData> ( "Wallet_amt" )->color_ = { 0.0f,0.0f,0.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Wallet_amt" )->text = JZEngine::String ( ss.str ().c_str () );
}

/*!
 * @brief BEGIN SHOP - END
 * **********************************************************************
*/

/*!
 * **********************************************************************
 * @brief TRAY CODE - START
*/
bool plate_on_tray{ false };
bool plate_on_hand{ false };
JZEngine::Vec2f original_plate_position_{ 0.0f,0.0f };

std::string plate_food_object_names[] = {
	"tray_wanton",
	"tray_seaweedchicken",
	"tray_springroll",
	"tray_carrotcake",
	"tray_chickenfeet",
	"tray_hargao",
	"tray_siewmai",
	"tray_charsiewbao",
	"tray_doushabao",
	"tray_coffeebao",
	"tray_plainccf",
	"tray_prawnccf",
	"Nothing"
};

//TrayPlateState tray_plate_state = TrayPlateState::Nothing;
CustomerOrder current_order = CustomerOrder::Nothing;

void FlagAllTrayItemsFalse()
{
	Scene().EntityFlagActive("tray_plate", false);
	plate_on_tray = false;
	Scene().EntityFlagActive("tray_wanton", false);
	Scene().EntityFlagActive("tray_seaweedchicken", false);
	Scene().EntityFlagActive("tray_springroll", false);
	Scene().EntityFlagActive("tray_carrotcake", false);
	Scene ().EntityFlagActive ( "tray_chickenfeet" , false );
	Scene ().EntityFlagActive ( "tray_hargao" , false );
	Scene ().EntityFlagActive ( "tray_siewmai" , false );
	Scene ().EntityFlagActive ( "tray_charsiewbao" , false );
	Scene ().EntityFlagActive ( "tray_doushabao" , false );
	Scene ().EntityFlagActive ( "tray_coffeebao" , false );
	Scene ().EntityFlagActive ( "tray_plainccf" , false );
	Scene ().EntityFlagActive ( "tray_prawnccf" , false );
	current_order = CustomerOrder::Nothing;

	// reset all cut foods
	Scene ().GetComponent<JZEngine::Texture> ( "tray_charsiewbao" )->texture_id_ = Scene ().GetTexture ( "CharSiewBao_Food_Hawker" );
	Scene ().GetComponent<JZEngine::Texture> ( "tray_doushabao" )->texture_id_ = Scene ().GetTexture ( "DouShaBao_Food_Hawker" );
	Scene ().GetComponent<JZEngine::Texture> ( "tray_coffeebao" )->texture_id_ = Scene ().GetTexture ( "CoffeeBao_Food_Hawker" );
	Scene ().GetComponent<JZEngine::Texture> ( "tray_plainccf" )->texture_id_ = Scene ().GetTexture ( "PlainCCF_Food_Hawker" );
	Scene ().GetComponent<JZEngine::Texture> ( "tray_prawnccf" )->texture_id_ = Scene ().GetTexture ( "PrawnCCF_Food_Hawker" );
}

void FlagPlateState(bool flag)
{
	Scene().EntityFlagActive("tray_plate", flag);
	plate_on_tray = true;
}

void SetPlateFood(CustomerOrder state)
{
	// if no plate on the tray, cannot put food
	if (!plate_on_tray)
	{
		return;
	}
	current_order = state;
	Scene().EntityFlagActive(plate_food_object_names[static_cast<int>(current_order)], true);
}

/*!
 * @brief TRAY CODE - END
 * **********************************************************************
*/

/*!
 * **********************************************************************
 * @brief UI - START
*/

float display_time_{ 4.0f };
float timer_{ display_time_ };
float display_up_{ false };
float greenbar_original_scale_y{ 4.25f };

void UnDisplayOrder()
{
	// flag board
	Scene().EntityFlagActive("OrderBoard", false);
	Scene().EntityFlagActive("EmptyBar", false);
	Scene().EntityFlagActive("GreenBar", false);
	Scene().EntityFlagActive("RedBar", false);
	// flag off on all foods
	Scene().EntityFlagActive("OrderWanton", false);
	Scene().EntityFlagActive("OrderSeaweed", false);
	Scene().EntityFlagActive("OrderSpringroll", false);
	Scene().EntityFlagActive("OrderCarrotcake", false);
	// day 2 foods
	Scene ().EntityFlagActive ( "OrderChickenfeet" , false );
	Scene ().EntityFlagActive ( "OrderHargao" , false );
	Scene ().EntityFlagActive ( "OrderSiewmai" , false );
	Scene ().EntityFlagActive ( "OrderCharsiewbao" , false );
	Scene ().EntityFlagActive ( "OrderDoushabao" , false );
	Scene ().EntityFlagActive ( "OrderCoffeebao" , false );
	// day 3 foods
	Scene ().EntityFlagActive ( "OrderPlainccf" , false );
	Scene ().EntityFlagActive ( "OrderPrawnccf" , false );

	Scene ().EntityFlagActive ( "OrderSuccess" , false );
	// reset flags
	display_up_ = false;
	timer_ = display_time_;
	display_up_ = false;
	Scene().GetComponent<JZEngine::Transform>("GreenBar")->scale_.y = greenbar_original_scale_y;
}

bool order_board_animated_once = false;
bool order_success = false;
void DisplayOrder(CustomerOrder order)
{
	UnDisplayOrder();
	order_board_animated_once = false;
	// flag board
	Scene().EntityFlagActive("OrderBoard", true);
	Scene().EntityFlagActive("EmptyBar", true);
	Scene().EntityFlagActive("GreenBar", true);
	Scene().EntityFlagActive("RedBar", true);
	display_up_ = true;
	order_success = false;
	switch (order)
	{
	case CustomerOrder::Wanton:
		Scene().EntityFlagActive("OrderWanton", true);
		break;
	case CustomerOrder::SeaweedChicken:
		Scene().EntityFlagActive("OrderSeaweed", true);
		break;
	case CustomerOrder::SpringRoll:
		Scene().EntityFlagActive("OrderSpringroll", true);
		break;
	case CustomerOrder::CarrotCake:
		Scene().EntityFlagActive("OrderCarrotcake", true);
		break;
	case CustomerOrder::ChickenFeet:
		Scene ().EntityFlagActive ( "OrderChickenfeet" , true );
		break;
	case CustomerOrder::HarGao:
		Scene ().EntityFlagActive ( "OrderHargao" , true );
		break;
	case CustomerOrder::SiewMai:
		Scene ().EntityFlagActive ( "OrderSiewmai" , true );
		break;
	case CustomerOrder::CharSiewBao:
		Scene ().EntityFlagActive ( "OrderCharsiewbao" , true );
		break;
	case CustomerOrder::DouShaBao:
		Scene ().EntityFlagActive ( "OrderDoushabao" , true );
		break;
	case CustomerOrder::CoffeeBao:
		Scene ().EntityFlagActive ( "OrderCoffeebao" , true );
		break;
	case CustomerOrder::PlainCCF:
		Scene ().EntityFlagActive ( "OrderPlainccf" , true );
		break;
	case CustomerOrder::PrawnCCF:
		Scene ().EntityFlagActive ( "OrderPrawnccf" , true );
		break;
	}
}

void DisplayTick ()
{
	UnDisplayOrder ();
	order_board_animated_once = false;
	// flag board
	Scene ().EntityFlagActive ( "OrderBoard" , true );
	Scene ().EntityFlagActive ( "EmptyBar" , true );
	Scene ().EntityFlagActive ( "GreenBar" , true );
	Scene ().EntityFlagActive ( "RedBar" , true );
	display_up_ = true;
	Scene ().EntityFlagActive ( "OrderSuccess" , true );
}

void DisplayUpdate(float dt)
{
	if (display_up_ && timer_ > 0.0f)
	{
		timer_ -= dt;
		Scene().GetComponent<JZEngine::Transform>("GreenBar")->scale_.y = timer_ / display_time_ * greenbar_original_scale_y;
	}
	else
	{
		UnDisplayOrder();
	}
}

float target_coins{ 10.0f };
float current_coins{ 0.0f };
//float coin_increment{ 100 };
float total_time{ 60.0f };
float current_time{ 0.0f };
bool win{ false };
bool lose{ false };
float initial_progress_scale{ 7.537f };
float current_coin_scale { 0.0f };

void UpdateCoinProgressBar()
{
	float currentcoins = current_coins;
	if (currentcoins > target_coins)
		currentcoins = target_coins;

	current_coin_scale
		= static_cast<float>(currentcoins) / static_cast<float>(target_coins) * initial_progress_scale;


}

bool won_bar_ { false };
float won_bar_counter_ { 0.0f };
bool coin_last_update { false };
bool win_shortcut { false };

void ShowWonBar ();
void AnimateCoinProgreeBar (float dt)
{
	float& x = Scene ().GetComponent<JZEngine::Transform> ( "ui_coin_progress" )->scale_.x;
	if ( x < current_coin_scale)
	{
		x += dt;
	}
	if ( coin_last_update && x > initial_progress_scale || win_shortcut )
	{
		if ( won_bar_ == false )
		{
			Scene ().PlaySound ( "cheer" , false );
		}
		won_bar_ = true;
		ShowWonBar ();
	}
}

bool coin_bar_animation_play = false;
bool coin_bar_played_once = false;
bool coin_sparkles_animation_play = false;
int coin_sparkles_play_count = 0;
bool coin_animation_play = false;
bool coin_played_once = false;
bool coin_suck = false;
JZEngine::Vec2f og_coin_position {};
float og_coin_distance_from_bar {};
void UpdateCoinProgressBarAnimation ()
{
	if ( coin_bar_animation_play )
	{
		Scene ().GetComponent<JZEngine::Animation2D> ( "CoinBar" )->animation_speed_ = 0.1f;
		if (  Scene ().GetComponent<JZEngine::Animation2D> ( "CoinBar" )->frame_ == 0 )
		{
			if ( coin_bar_played_once )
			{
				coin_bar_animation_play = false;
				coin_bar_played_once = false;
			}
			else
			{
				coin_bar_played_once = true;
			}
		}
	}
	else
	{
		Scene ().GetComponent<JZEngine::Animation2D> ( "CoinBar" )->animation_speed_ = 1000.0f;
	}
}

void UpdateCoinSparklesAnimation ()
{
	if ( coin_sparkles_animation_play )
	{
		Scene ().GetComponent<JZEngine::Animation2D> ( "CoinSparkles" )->animation_speed_ = 0.1f;
		if ( Scene ().GetComponent<JZEngine::Animation2D> ( "CoinSparkles" )->frame_ == 0 )
		{
			if ( coin_sparkles_play_count > 4 )
			{
				Scene ().EntityFlagActive ( "CoinSparkles" , false );
				coin_sparkles_animation_play = false;
				coin_sparkles_play_count = 0;
			}
			else
			{
				++coin_sparkles_play_count;
			}
		}
	}
	else
	{
		Scene ().GetComponent<JZEngine::Animation2D> ( "CoinSparkles" )->animation_speed_ = 1000.0f;
	}
}

void UpdateOrderBoardAnimation ()
{
	JZEngine::Animation2D* anim = Scene ().GetComponent<JZEngine::Animation2D> ( "OrderBoard" );
	if ( anim )
	{
		if ( order_board_animated_once )
		{
			anim->animation_speed_ = 1000.0f;
		}
		else
		{
			anim->animation_speed_ = 0.15f;
			if ( anim->frame_ == anim->max_frames_ - 1 )
			{
				order_board_animated_once = true;
				anim->frame_ = 0;
			}
		}
	}
}

template <typename...T>
void SetCoinText ( T...text )
{
	std::stringstream ss;
	( ( ss << text ) , ... );
	Scene ().GetComponent<JZEngine::TextData> ( "ui_coin_text" )->text = JZEngine::String ( ss.str ().c_str () );
}

void UpdateCoinAnimation (float dt)
{
	if ( coin_animation_play )
	{
		Scene ().GetComponent<JZEngine::Animation2D> ( "CoinOnTable" )->animation_speed_ = 0.03f;
		if ( Scene ().GetComponent<JZEngine::Animation2D> ( "CoinOnTable" )->frame_ == Scene ().GetComponent<JZEngine::Animation2D> ( "CoinOnTable" )->max_frames_ - 1 )
		{
			if ( coin_played_once )
			{
				coin_animation_play = false;
				coin_played_once = false;
				coin_suck = true;
			}
			else
			{
				coin_played_once = true;
			}
		}
	}
	else
	{
		Scene ().GetComponent<JZEngine::Animation2D> ( "CoinOnTable" )->animation_speed_ = 1000.0f;
	}
	if ( coin_suck )
	{
		JZEngine::Vec2f dir = Scene ().GetComponent<JZEngine::Transform> ( "CoinBar" )->position_ - Scene ().GetComponent<JZEngine::Transform> ( "CoinOnTable" )->position_;
		float length = dir.Len ();
		if ( length > 50.0f )
		{
			Scene ().GetComponent<JZEngine::Transform> ( "CoinOnTable" )->position_ += 2000.0f * dir.Normalize () * dt;
			Scene ().GetComponent<JZEngine::NonInstanceShader> ( "CoinOnTable" )->tint.w = length / og_coin_distance_from_bar * 2.0f;
		}
		else
		{
			coin_suck = false;

			SetCoinText ( "$" , std::setprecision(2), std::fixed, current_coins );
			UpdateCoinProgressBar ();
			coin_bar_animation_play = true;
			coin_sparkles_animation_play = true;
			Scene ().EntityFlagActive ( "CoinSparkles" , true );

			Scene ().GetComponent<JZEngine::Transform> ( "CoinOnTable" )->position_ = og_coin_position;
			Scene ().GetComponent<JZEngine::Animation2D> ( "CoinOnTable" )->frame_ = 0;
			Scene ().GetComponent<JZEngine::NonInstanceShader> ( "CoinOnTable" )->tint.w = 1.0f;
			Scene ().EntityFlagActive ( "CoinOnTable" , false );
		}
	}
}

void UpdateGoalProgressBar(float dt)
{
	current_time += dt;
	Scene().GetComponent<JZEngine::Transform>("ui_goal_progress")->scale_.x
		= current_time / total_time * initial_progress_scale;

	if (current_time > total_time)
	{
		Scene().ChangeScene("MainMenu");
	}
}

template <typename...T>
void SetGoalText(T...text)
{
	std::stringstream ss;
	((ss << text), ...);
	Scene().GetComponent<JZEngine::TextData>("ui_goal_text")->text = JZEngine::String(ss.str().c_str());
}

bool notification_display_ { false };
int notification_current_ { -1 };
float notification_time_ { 30.0f };
float notification_time_counter_ { 0.0f };
constexpr int notification_count_ { 8 };
std::string notification[ notification_count_ ] =
{
	"Baozi! Click the customer for orders.",
	"Grab a plate and put it on the tray!",
	"Baozi! Use a tong to grab the food.",
	"Put it on the plate and serve it!",
	"For wrong orders, throw it in the bin.",
	"Don't take too long! They will get angry.",
	"Some foods need to be cut before serving!",
	"Add Spring Onions and Soy Sauce to the food!"
};
bool notification_shown[ notification_count_ ] { false };

void TurnOffNotification ()
{
	Scene ().EntityFlagActive ( "NotificationText" , false );
	Scene ().EntityFlagActive ( "NotificationBar" , false );
	Scene ().GetComponent<JZEngine::AnimatedTransformComponent> ( "PhoneOptions" )->active_flag = false;
	notification_display_ = false;
	notification_time_counter_ = 0.0f;
}

int current_notification { 0 };
void ShowNotification (int i)
{
	if ( i < notification_count_ )
	{
		if ( i <= current_notification )
		{
			if ( !notification_shown[ i ] )
			{
				TurnOffNotification ();
				notification_shown[ i ] = true;
				Scene ().GetComponent<JZEngine::TextData> ( "NotificationText" )->text = JZEngine::String ( notification[ i ].c_str () );
				Scene ().EntityFlagActive ( "NotificationText" , true );
				Scene ().EntityFlagActive ( "NotificationBar" , true );
				Scene ().GetComponent<JZEngine::AnimatedTransformComponent> ( "PhoneOptions" )->active_flag = true;
				notification_display_ = true;

				if ( hawker_scene_day == DAY::ONE )
				{
					switch ( i )
					{
					case ( 0 ):
						ToggleGuidedCircle ( "gtc_customer" , true );
						break;
					case ( 1 ):
						ToggleGuidedCircle ( "gtc_customer" , false );
						ToggleGuidedCircle ( "gtc_platetray" , true );
						break;
					case ( 2 ):
						ToggleGuidedCircle ( "gtc_platetray" , false );
						ToggleGuidedCircle ( "gtc_tongsfood" , true );
						break;
					case ( 3 ):
						ToggleGuidedCircle ( "gtc_tongsfood" , false );
						ToggleGuidedCircle ( "gtc_platecustomer" , true );
						break;
					case ( 4 ):
						ToggleGuidedCircle ( "gtc_platecustomer" , false );
						break;
					}
				}
				if ( hawker_scene_day == DAY::TWO )
				{
					switch ( i )
					{

					case ( 6 ):
					{
						ToggleGuidedCircle ( "gtc_scizzors" , true );
						break;
					}

					}
				}
				if ( hawker_scene_day == DAY::THREE )
				{
					switch ( i )
					{

					case ( 7 ):
					{
						ToggleGuidedCircle ( "gtc_springsoy" , true );
						break;
					}

					}
				}
				++current_notification;
			}
		}
	}
}

void UpdateNotification ( float dt )
{
	if ( notification_display_ )
	{
		if ( notification_time_counter_ < notification_time_ )
		{
			notification_time_counter_ += dt;
		}
		else
		{
			notification_time_counter_ = 0.0f;
			TurnOffNotification ();
		}
	}
}

void HideWonBar ()
{
	Scene ().EntityFlagActive ( "WinBar" , false );
	Scene ().EntityFlagActive ( "WinBarBG" , false );
	Scene ().EntityFlagActive ( "WinFireworks1" , false );
	Scene ().EntityFlagActive ( "WinFireworks2" , false );
	Scene().EntityFlagActive("WinFireworks3", false);
	Scene().EntityFlagActive("WinFireworks4", false);
	Scene ().EntityFlagActive ( "WinBlackCover" , false );
}

void ShowWonBar ()
{
	Scene ().EntityFlagActive ( "WinBar" , true );
	Scene ().EntityFlagActive ( "WinBarBG" , true );
	Scene ().EntityFlagActive ( "WinFireworks1" , true );
	Scene ().EntityFlagActive ( "WinFireworks2" , true );
	Scene().EntityFlagActive("WinFireworks3", true);
	Scene().EntityFlagActive("WinFireworks4", true);
	Scene ().EntityFlagActive ( "WinBlackCover" , true );
}

float lose_bar_fall_speed { 4096 };
float lose_offset { 1024 };
void FlagLoseBar (bool flag)
{
	Scene ().EntityFlagActive ( "LoseAnimation" , flag );
	Scene ().EntityFlagActive ( "LoseAnimationTears" , flag );
}

void InitLoseBar ()
{
	lose_offset = 1024;
	Scene ().GetComponent<JZEngine::Transform> ( "LoseAnimation" )->position_.y = lose_offset;
	Scene ().GetComponent<JZEngine::Transform> ( "LoseAnimationTears" )->position_.y = lose_offset;
	FlagLoseBar ( false );
}

void ToggleSummary ( bool flag );
void SummaryInit ();
void UpdateLoseBar (float dt)
{
	bool reach { true };
	JZEngine::Transform* lose_animation = Scene ().GetComponent<JZEngine::Transform> ( "LoseAnimation" );
	JZEngine::Transform* lose_animation_tears = Scene ().GetComponent<JZEngine::Transform> ( "LoseAnimationTears" );
	if ( lose_offset > 0 )
	{
		reach = false;
		lose_offset -= lose_bar_fall_speed * dt;
		lose_animation->position_.y -= lose_bar_fall_speed * dt;
		lose_animation_tears->position_.y -= lose_bar_fall_speed * dt;
	}
	JZEngine::Animation2D* lose_animation_anim = Scene ().GetComponent<JZEngine::Animation2D> ( "LoseAnimation" );
	if ( lose_animation_anim->frame_ == lose_animation_anim->max_frames_ - 1 )
	{
		lose_animation_anim->pause_ = true;
	}
	else
	{
		reach = false;
	}
	JZEngine::Animation2D* lose_animation_tears_anim = Scene ().GetComponent<JZEngine::Animation2D> ( "LoseAnimationTears" );
	if ( lose_animation_tears_anim->frame_ == lose_animation_tears_anim->max_frames_ - 1 )
	{
		lose_animation_tears_anim->pause_ = true;
	}
	else
	{
		reach = false;
	}

	if ( reach )
	{
		ToggleSummary ( true );
		SummaryInit ();
		current_hawker_scene_state = HawkerSceneState::Win;
		FlagLoseBar ( false );
	}
}

/*!
 * @brief UI - END
 * **********************************************************************
*/

/*!
 * **********************************************************************
 * @brief WIN - START
*/

void ToggleWin(bool toggle)
{
	Scene().EntityFlagActive("Win_background", toggle);
	Scene().EntityFlagActive("Win_restart", toggle);
	Scene().EntityFlagActive("Win_exit", toggle);
	Scene().EntityFlagActive("Win_title", toggle);
	Scene().EntityFlagActive("Win_words", toggle);
	Scene().EntityFlagActive("Win_words2", toggle);
}

void ToggleSummary ( bool toggle )
{
	Scene ().EntityFlagActive ( "Win_restart_bb" , toggle );
	Scene ().EntityFlagActive ( "Win_exit_bb" , toggle );
	Scene ().EntityFlagActive ( "Summary_screen" , toggle );
	Scene ().EntityFlagActive ( "sum_sr_amt" , toggle );
	Scene ().EntityFlagActive ( "sum_sc_amt" , toggle );
	Scene ().EntityFlagActive ( "sum_fd_amt" , toggle );
	Scene ().EntityFlagActive ( "sum_cc_amt" , toggle );
	Scene ().EntityFlagActive ( "sum_total_amt" , toggle );

	
	Scene().EntityFlagActive("Summary_Next", toggle);
	Scene().EntityFlagActive("Summary_Restart", toggle);
	Scene().EntityFlagActive("Summary_Exit", toggle);
	if (hawker_scene_day == DAY::TWO)
	{
		Scene().EntityFlagActive("sum_csb_amt", toggle);
		Scene().EntityFlagActive("sum_rbb_amt", toggle);
		Scene().EntityFlagActive("sum_cb_amt", toggle);
		Scene().EntityFlagActive("sum_pd_amt", toggle);
		Scene().EntityFlagActive("sum_cf_amt", toggle);
		Scene().EntityFlagActive("sum_cd_amt", toggle);
	}
	if (hawker_scene_day == DAY::THREE)
	{
		Scene().EntityFlagActive("sum_csb_amt", toggle);
		Scene().EntityFlagActive("sum_rbb_amt", toggle);
		Scene().EntityFlagActive("sum_cb_amt", toggle);
		Scene().EntityFlagActive("sum_pd_amt", toggle);
		Scene().EntityFlagActive("sum_cf_amt", toggle);
		Scene().EntityFlagActive("sum_cd_amt", toggle);

		Scene().EntityFlagActive("sum_pr_amt", toggle);
		Scene().EntityFlagActive("sum_rnr_amt", toggle);
		
	}
	
}
void ToggleConfirm(bool toggle, Confirmstate confirm_state = Confirmstate::None)
{
	if(confirm_state ==Confirmstate::Restart)
		Scene().EntityFlagActive("Summary_Restart_Confirm", toggle);
	else if(confirm_state == Confirmstate::Exit)
		Scene().EntityFlagActive("Summary_Exit_Confirm", toggle);
	else
	{
		Scene().EntityFlagActive("Summary_Restart_Confirm", toggle);
		Scene().EntityFlagActive("Summary_Exit_Confirm", toggle);
	}

	Scene().EntityFlagActive("Summary_Yes", toggle);
	Scene().EntityFlagActive("Summary_No", toggle);

}

bool summary_ready { false };
float summary_counter { 0.0f };
void SummaryInit ()
{
	summary_ready = false;
	confirm_state = Confirmstate::None;
	Scene ().EntityFlagActive ( "BeginBlack" , true );
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "BeginBlack" )->tint.w = 0.0f;
	Scene ().GetComponent<JZEngine::Transform> ( "Summary_screen" )->position_.y = 2048.0f;
	Scene().GetComponent<JZEngine::Transform>("Summary_Restart")->position_.y = 1612.f;
	Scene().GetComponent<JZEngine::Transform>("Summary_Next")->position_.y = 1612.f;
	Scene().GetComponent<JZEngine::Transform>("Summary_Exit")->position_.y = 1612.f;

	ToggleConfirm(false);

	summary_sr_count = 0;
	summary_sc_count = 0;
	summary_fd_count = 0;
	summary_cc_count = 0;
	summary_csb_count = 0;
	summary_rbb_count = 0;
	summary_cb_count = 0;
	summary_pd_count = 0;
	summary_cf_count = 0;
	summary_cd_count = 0;
	summary_pr_count = 0;;
	summary_rnr_count = 0;

	summary_counter = 0.0f;

	std::stringstream ss;
	ss << "";
	if (hawker_scene_day == DAY::ONE)
	{
		Scene().GetComponent<JZEngine::TextData>("sum_sr_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_sr_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_sr_amt")->position_ = { -215,169.f };

		Scene().GetComponent<JZEngine::TextData>("sum_sc_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_sc_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_sc_amt")->position_ = { 227.f,169.f };

		Scene().GetComponent<JZEngine::TextData>("sum_fd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_fd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_fd_amt")->position_ = { -215.f,-4.0f };

		Scene().GetComponent<JZEngine::TextData>("sum_cc_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cc_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cc_amt")->position_ = { 227.0f,-4.0f };

		Scene().GetComponent<JZEngine::Texture>("Summary_screen")->texture_id_ = Scene().GetTexture("SummaryBackgroundDay1_WIN_UI_hawker");

		Scene().GetComponent<JZEngine::TextData>("sum_total_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_total_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_total_amt")->position_ = { -48.0f,-188.f };
	}
	if (hawker_scene_day == DAY::TWO)
	{
		Scene().GetComponent<JZEngine::TextData>("sum_sr_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_sr_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_sr_amt")->position_ = { -450.5f,175.f };

		Scene().GetComponent<JZEngine::TextData>("sum_sc_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_sc_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_sc_amt")->position_ = { -139.6f,175.f };

		Scene().GetComponent<JZEngine::TextData>("sum_fd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_fd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_fd_amt")->position_ = { 180.f,175.f };

		Scene().GetComponent<JZEngine::TextData>("sum_cc_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cc_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cc_amt")->position_ = { 500.f,175.f };

		Scene().GetComponent<JZEngine::TextData>("sum_csb_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_csb_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_csb_amt")->position_ = { -289.1f,61.f };



		Scene().GetComponent<JZEngine::TextData>("sum_rbb_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_rbb_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_rbb_amt")->position_ = { 21.1f,61.f };

		Scene().GetComponent<JZEngine::TextData>("sum_cb_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cb_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cb_amt")->position_ = { 335.f,61.f };

		Scene().GetComponent<JZEngine::TextData>("sum_pd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_pd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_pd_amt")->position_ = { -293.1f,-51.f };



		Scene().GetComponent<JZEngine::TextData>("sum_cf_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cf_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cf_amt")->position_ = { 25.f,-51.f };

		Scene().GetComponent<JZEngine::TextData>("sum_cd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cd_amt")->position_ = { 340.1f,-51.f };


		Scene().GetComponent<JZEngine::Texture>("Summary_screen")->texture_id_ = Scene().GetTexture("SummaryBackgroundDay2_LOSE_UI_hawker");
	
		Scene().GetComponent<JZEngine::TextData>("sum_total_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_total_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_total_amt")->position_ = { -30.f,-185.f };
	}
	if (hawker_scene_day == DAY::THREE)
	{
		Scene().GetComponent<JZEngine::TextData>("sum_sr_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_sr_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_sr_amt")->position_ = { -450.5f,161.f };

		Scene().GetComponent<JZEngine::TextData>("sum_sc_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_sc_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_sc_amt")->position_ = { -139.6f,161.f };

		Scene().GetComponent<JZEngine::TextData>("sum_fd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_fd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_fd_amt")->position_ = { -178.9f,161.f };

		Scene().GetComponent<JZEngine::TextData>("sum_cc_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cc_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cc_amt")->position_ = { 500.f,161.f };


		Scene().GetComponent<JZEngine::TextData>("sum_csb_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_csb_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_csb_amt")->position_ = { -450.5f,48.f };


		Scene().GetComponent<JZEngine::TextData>("sum_rbb_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_rbb_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_csb_amt")->position_ = { -135.5f,48.f };

		Scene().GetComponent<JZEngine::TextData>("sum_cb_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cb_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cb_amt")->position_ = {180.f,48.f };

		Scene().GetComponent<JZEngine::TextData>("sum_cd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cd_amt")->position_ = { 500.f,48.f };




		Scene().GetComponent<JZEngine::TextData>("sum_pd_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_pd_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_pd_amt")->position_ = { 180.f,-64.4f };

		Scene().GetComponent<JZEngine::TextData>("sum_cf_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_cf_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_cf_amt")->position_ = { 500.f,-64.4f };


		Scene().GetComponent<JZEngine::TextData>("sum_pr_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_pr_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_pr_amt")->position_ = { -135.f,-64.4f };

		Scene().GetComponent<JZEngine::TextData>("sum_rnr_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_rnr_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_rnr_amt")->position_ = { -447.f,-64.4f };

		if(win)
			Scene().GetComponent<JZEngine::Texture>("Summary_screen")->texture_id_ = Scene().GetTexture("SummaryBackgroundDay3_WIN_UI_hawker");
		else
			Scene().GetComponent<JZEngine::Texture>("Summary_screen")->texture_id_ = Scene().GetTexture("SummaryBackgroundDay3_LOSE_UI_hawker");
	

		Scene().GetComponent<JZEngine::TextData>("sum_total_amt")->color_ = { 1.0f,1.0f,1.0f };
		Scene().GetComponent<JZEngine::TextData>("sum_total_amt")->text = JZEngine::String(ss.str().c_str());
		Scene().GetComponent<JZEngine::Transform>("sum_total_amt")->position_ = { -30.f,-200.f };
	}



}

float springroll_price { 2.70f };
float seaweedchicken_price { 1.20f };
float frieddumplings_price { 2.10f };
float friedcarrotcake_price { 3.00f };
float chickendumplings_price { 2.50f };
float prawndumplings_price { 2.70f };
float chickenfeet_price { 3.50f };
float charsiewbun_price { 0.60f };
float redbeanbun_price { 0.50f };
float coffeebun_price { 0.50f };
float ricenoodleroll_price { 1.20f };
float prawnroll_price { 1.50f };

float summary_wallet_amt { 0.0f };

void UpdateWinScreen(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	
	if (win)
	{
		Scene().EntityFlagActive("Summary_Restart", false);
		if (hawker_scene_day == DAY::THREE)
		{
			Scene().EntityFlagActive("Summary_Exit", false);
			Scene().GetComponent<JZEngine::Transform>("Summary_Next")->position_.x = 0.0f;
		}
		
	}
	else//lose
	{
		Scene().EntityFlagActive("Summary_Next", false);
	}



	float& exitbutton_y = Scene().GetComponent<JZEngine::Transform>("Summary_Exit")->position_.y;
	float& rsbutton_y = Scene().GetComponent<JZEngine::Transform>("Summary_Restart")->position_.y;
	float& sumbutton_y = Scene().GetComponent<JZEngine::Transform>("Summary_Next")->position_.y;


	float& black_alpha = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "BeginBlack" )->tint.w;
	float& summary_y = Scene ().GetComponent<JZEngine::Transform> ( "Summary_screen" )->position_.y;
	bool ready { true };
	if ( black_alpha < 1.0f )
	{
		black_alpha += dt;
		ready = false;
	}
	if ( summary_y > 0.0f )
	{
		exitbutton_y -= 1024.0f * dt;
		rsbutton_y -= 1024.0f * dt;
		sumbutton_y -= 1024.0f * dt;

		summary_y -= 1024.0f * dt;
		ready = false;
	}
	else
	{
		summary_y = 0.0f;
		exitbutton_y = -436.0f;
		rsbutton_y = -436.0f;
	}

	if ( ready )
	{
		bool update { false };
		if ( summary_counter < 0.5f )
		{
			summary_counter += dt;
		}
		else
		{
			summary_counter = 0.0f;
			update = true;
		}

		if ( update )
		{
			bool done_updating { true };
			// add display numbers 
			//day1
			if ( summary_sc_count < init_seaweedchicken_count - seaweedchicken_count )
			{
				++summary_sc_count;
				done_updating = false;
			}
			if ( summary_sr_count < init_springroll_count - springroll_count )
			{
				++summary_sr_count;
				done_updating = false;
			}
			if ( summary_fd_count < init_wanton_count - wanton_count )
			{
				++summary_fd_count;
				done_updating = false;
			}
			if ( summary_cc_count < init_carrotcake_count - carrotcake_count )
			{
				++summary_cc_count;
				done_updating = false;
			}

			//Add back in after getting the day2 3 food counter working
			// 
			//day2
			/*
			if (Cutscene::day == Days::Two || Cutscene::day == Days::Three)
			{
				if (summary_csb_count < init_charsiewbao_count - charsiewbao_count)
				{
					++summary_csb_count;
					done_updating = false;
				}
				if (summary_rbb_count < init_doushabao_count - doushabao_count)
				{
					++summary_rbb_count;
					done_updating = false;
				}
				if (summary_cb_count < init_coffeebao_count - coffeebao_count)
				{
					++summary_cb_count;
					done_updating = false;
				}
				if (summary_pd_count < init_hargao_count - hargao_count)
				{
					++summary_pd_count;
					done_updating = false;
				}
				if (summary_cf_count < init_chickenfeet_count - chickenfeet_count)
				{
					++summary_cf_count;
					done_updating = false;
				}
				if (summary_cd_count < init_siewmai_count - siewmai_count)
				{
					++summary_cd_count;
					done_updating = false;
				}
			}
			if (Cutscene::day == Days::Three)
			{
				if (summary_pr_count < init_prawnccf_count - prawnccf_count)
				{
					++summary_pr_count;
					done_updating = false;
				}
				if (summary_rnr_count < init_plainccf_count - plainccf_count)
				{
					++summary_rnr_count;
					done_updating = false;
				}
			}
			*/
			std::stringstream ss;
			ss << summary_sr_count;
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sr_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sr_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			ss.str ("");
			ss << summary_sc_count;
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sc_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sc_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			ss.str ( "" );
			ss << summary_fd_count;
			Scene ().GetComponent<JZEngine::TextData> ( "sum_fd_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_fd_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			ss.str ( "" );
			ss << summary_cc_count;
			Scene ().GetComponent<JZEngine::TextData> ( "sum_cc_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_cc_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			
			if (Cutscene::day == Days::Two || Cutscene::day == Days::Three)
			{
				ss.str("");
				ss << summary_csb_count;
				Scene().GetComponent<JZEngine::TextData>("sum_csb_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_csb_amt")->text = JZEngine::String(ss.str().c_str());
				ss.str("");
				ss << summary_rbb_count;
				Scene().GetComponent<JZEngine::TextData>("sum_rbb_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_rbb_amt")->text = JZEngine::String(ss.str().c_str());
				ss.str("");
				ss << summary_cb_count;
				Scene().GetComponent<JZEngine::TextData>("sum_cb_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_cb_amt")->text = JZEngine::String(ss.str().c_str());
				ss.str("");
				ss << summary_pd_count;
				Scene().GetComponent<JZEngine::TextData>("sum_pd_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_pd_amt")->text = JZEngine::String(ss.str().c_str());
				ss.str("");
				ss << summary_cf_count;
				Scene().GetComponent<JZEngine::TextData>("sum_cf_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_cf_amt")->text = JZEngine::String(ss.str().c_str());
				ss.str("");
				ss << summary_cd_count;
				Scene().GetComponent<JZEngine::TextData>("sum_cd_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_cd_amt")->text = JZEngine::String(ss.str().c_str());


			}
			if (Cutscene::day == Days::Three)
			{
				ss.str("");
				ss << summary_pr_count;
				Scene().GetComponent<JZEngine::TextData>("sum_pr_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_pr_amt")->text = JZEngine::String(ss.str().c_str());
				ss.str("");
				ss << summary_rnr_count;
				Scene().GetComponent<JZEngine::TextData>("sum_rnr_amt")->color_ = { 1.0f,1.0f,1.0f };
				Scene().GetComponent<JZEngine::TextData>("sum_rnr_amt")->text = JZEngine::String(ss.str().c_str());
			}



			float summary_price_amt = springroll_price * summary_sr_count + seaweedchicken_price * summary_sc_count + frieddumplings_price * summary_fd_count + friedcarrotcake_price * summary_cc_count;
			if (Cutscene::day == Days::Two || Cutscene::day == Days::Three)
			{
				summary_price_amt += charsiewbun_price * summary_csb_count + chickendumplings_price * summary_cd_count + prawndumplings_price * summary_pd_count + chickenfeet_price * summary_cf_count
					+ redbeanbun_price * summary_rbb_count + coffeebun_price * summary_cb_count;
			}
			if (Cutscene::day == Days::Three)
			{
				summary_price_amt += prawnroll_cost * summary_pr_count + ricenoodleroll_cost * summary_rnr_count;
			}
			summary_wallet_amt = wallet_amt + summary_price_amt;
			ss.str ( "" );
			ss << "$" << std::setprecision(2) << std::fixed << summary_wallet_amt;
			Scene ().GetComponent<JZEngine::TextData> ( "sum_total_amt" )->color_ = { 0.0f,0.0f,0.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_total_amt" )->text = JZEngine::String ( ss.str ().c_str () );

			if ( done_updating )
			{
				summary_ready = true;
			}
		}
	}



	if ( summary_ready && confirm_state == Confirmstate::None)
	{
		ToggleConfirm(false);
		if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Summary_Exit" ) )
		{
			AutoToggleButton(e, "Summary_Exit");
			if ( e->on_released_ )
			{
				//Scene ().ChangeScene ( "MainMenu" );
				confirm_state = Confirmstate::Exit;
				ToggleConfirm(true, confirm_state);
				
			}
			


		}
		if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Summary_Restart"))
		{
			AutoToggleButton(e, "Summary_Restart");
			if (e->on_released_)
			{
				confirm_state = Confirmstate::Restart;
				ToggleConfirm(true, confirm_state);
			}
			
			
		}
		//next
		if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Summary_Next"))
		{
			AutoToggleButton(e, "Summary_Next");
			if (e->on_released_)
			{
				wallet_amt = summary_wallet_amt;
				if (hawker_scene_day == DAY::ONE)
				{
					hawker_scene_day = DAY::TWO;
					Cutscene::day = Days::Two;
					Scene().ChangeScene("CutScene");
				}
				else if (hawker_scene_day == DAY::TWO)
				{
					hawker_scene_day = DAY::THREE;
					Cutscene::day = Days::Three;
					Scene().ChangeScene("CutScene");
				}
				else if (hawker_scene_day == DAY::THREE)
				{
					Scene().ChangeScene("MainMenu");
				}
			}
			
			
		}
	}


	if (confirm_state == Confirmstate::Exit)
	{
		if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Summary_Yes"))
		{
			AutoToggleButton(e, "Summary_Yes");
			if (e->on_released_)
			{
				confirm_state = Confirmstate::None;
				Scene().ChangeScene("MainMenu");

			}
			


		}
		if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Summary_No"))
		{
			AutoToggleButton(e, "Summary_No");
			if (e->on_released_)
			{
				
				confirm_state = Confirmstate::None;
				
			}
			


		}
	}


	if (confirm_state == Confirmstate::Restart)
	{
		if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Summary_Yes"))
		{
			AutoToggleButton(e, "Summary_Yes");
			if (e->on_released_)
			{		
				
				Scene().ChangeScene("CutScene");
			}
			

		}
		if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Summary_No"))
		{
			AutoToggleButton(e, "Summary_No");
			if (e->on_released_)
			{
				confirm_state = Confirmstate::None;
			}
			

		}

	}


}

/*!
 * @brief WIN - END
 * **********************************************************************
*/

bool first_time_cut { true };
bool food_cut { false };
bool food_soy { false };
bool food_spring { false };

bool first_time_garnish { true };

void UpdateMainScene(float dt)
{
	UpdateHawkerQueue(dt);
	//UpdateGoalProgressBar(dt);
	UpdateCoinAnimation ( dt );
	AnimateCoinProgreeBar ( dt );
	UpdateCoinProgressBarAnimation ();
	UpdateCoinSparklesAnimation ();
	UpdateOrderBoardAnimation ();
	UpdateNotification ( dt );

	if ( JZEngine::InputHandler::IsKeyPressed ( JZEngine::KEY::KEY_LEFT_CONTROL ) && JZEngine::InputHandler::IsKeyPressed ( JZEngine::KEY::KEY_W ) )
	{
		if ( won_bar_ == false )
		{
			Scene ().PlaySound ( "cheer" , false );
		}
		won_bar_ = true;
		ShowWonBar ();
	}

	if (JZEngine::InputHandler::IsMouseTriggered(JZEngine::MOUSE::MOUSE_BUTTON_1))
		Scene().PlaySound("click", false);

	if ( took_too_long_ )
	{
		took_too_long_ = false;
		ShowNotification ( 5 );
	}

	if ( order_success )
	{
		JZEngine::Animation2D* order_success_anim = Scene ().GetComponent<JZEngine::Animation2D> ( "OrderSuccess" );
		if ( order_success_anim->frame_ == order_success_anim->max_frames_ - 1 )
		{
			order_success_anim->frame_ = 0;
			order_success = false;
			UnDisplayOrder ();
		}
	}

	// process click inputs
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_springroll"))
	{
		if (e->on_click_)
		{
			ShowNotification ( 3 );
			if (CheckCursorState(CursorState::EmptyTongs))
			{
				JZEngine::Log::Info("Main", "SpringRoll Selected");
				if ( springroll_count > 0 )
				{
					FlagCursorState ( CursorState::TongsSpringroll );
					--springroll_count;
					std::stringstream springroll_name;
					springroll_name << "DryFoodSpringRoll(" << springroll_count << ")_Equipment_hawker";
					Scene ().GetComponent<JZEngine::Texture> ( "SpringRoll" )->texture_id_ = Scene ().GetTexture ( springroll_name.str () );
				}
			}
			else if (CheckCursorState(CursorState::TongsSpringroll))
			{
				JZEngine::Log::Info("Main", "SpringRoll Returned");
				FlagCursorState(CursorState::EmptyTongs);
				++springroll_count;
				std::stringstream springroll_name;
				springroll_name << "DryFoodSpringRoll(" << springroll_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "SpringRoll" )->texture_id_ = Scene ().GetTexture ( springroll_name.str () );
			}
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_wanton"))
	{
		if (e->on_click_)
		{
			ShowNotification ( 3 );
			if (CheckCursorState(CursorState::EmptyTongs))
			{
				JZEngine::Log::Info("Main", "Wanton Selected");
				if ( wanton_count > 0 )
				{
					FlagCursorState ( CursorState::TongsWanton );
					--wanton_count;
					std::stringstream wanton_name;
					wanton_name << "DryFoodFriedDumplings(" << wanton_count << ")_Equipment_hawker";
					Scene ().GetComponent<JZEngine::Texture> ( "Dumpling" )->texture_id_ = Scene ().GetTexture ( wanton_name.str () );
				}
			}
			else if (CheckCursorState(CursorState::TongsWanton))
			{
				JZEngine::Log::Info("Main", "Wanton Returned");
				FlagCursorState(CursorState::EmptyTongs);
				++wanton_count;
				std::stringstream wanton_name;
				wanton_name << "DryFoodFriedDumplings(" << wanton_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "Dumpling" )->texture_id_ = Scene ().GetTexture ( wanton_name.str () );
			}
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_seaweedchicken"))
	{
		if (e->on_click_)
		{
			ShowNotification ( 3 );
			if (CheckCursorState(CursorState::EmptyTongs))
			{
				JZEngine::Log::Info("Main", "SeaweedChicken Selected");
				if ( seaweedchicken_count > 0 )
				{
					FlagCursorState(CursorState::TongsSeaweedChicken);
					--seaweedchicken_count;
					std::stringstream seaweedchicken_name;
					seaweedchicken_name << "DryFoodSeaweedChicken(" << seaweedchicken_count << ")_Equipment_hawker";
					Scene ().GetComponent<JZEngine::Texture> ( "SeaweedChick" )->texture_id_ = Scene ().GetTexture ( seaweedchicken_name.str () );
				}
			}
			else if (CheckCursorState(CursorState::TongsSeaweedChicken))
			{
				JZEngine::Log::Info("Main", "SeaweedChicken Returned");
				FlagCursorState(CursorState::EmptyTongs);
				++seaweedchicken_count;
				std::stringstream seaweedchicken_name;
				seaweedchicken_name << "DryFoodSeaweedChicken(" << seaweedchicken_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "SeaweedChick" )->texture_id_ = Scene ().GetTexture ( seaweedchicken_name.str () );
			}
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_carrotcake"))
	{
		if (e->on_click_)
		{
			ShowNotification ( 3 );
			if (CheckCursorState(CursorState::EmptyTongs))
			{
				JZEngine::Log::Info("Main", "CarrotCake Selected");
				if ( carrotcake_count > 0 )
				{
					FlagCursorState ( CursorState::TongsCarrotCake );
					--carrotcake_count;
					std::stringstream carrotcake_name;
					carrotcake_name << "DryFoodCarrotCake(" << carrotcake_count << ")_Equipment_hawker";
					Scene ().GetComponent<JZEngine::Texture> ( "CarrotCake" )->texture_id_ = Scene ().GetTexture ( carrotcake_name.str () );
				}
			}
			else if (CheckCursorState(CursorState::TongsCarrotCake))
			{
				JZEngine::Log::Info("Main", "CarrotCake Returned");
				FlagCursorState(CursorState::EmptyTongs);
				++carrotcake_count;
				std::stringstream carrotcake_name;
				carrotcake_name << "DryFoodCarrotCake(" << carrotcake_count << ")_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "CarrotCake" )->texture_id_ = Scene ().GetTexture ( carrotcake_name.str () );
			}
		}
	}

	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "bb_springonion" ) )
	{
		if ( e->on_click_ && hawker_scene_day == DAY::THREE && !plate_on_hand )
		{
			FlagCursorState ( CursorState::SpringOnion );
		}
	}

	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "bb_soysauce" ) )
	{
		if ( e->on_click_ && hawker_scene_day == DAY::THREE && !plate_on_hand )
		{
			FlagCursorState ( CursorState::SoySauce );
		}
	}

	// day 2 foods
	ProcessDay2Item ( CursorState::TongsChickenFeet , "bb_ChickenFeet" , "ChickenFeet" , chickenfeet_count , "RoundSteamerFeet" , "_Equipment_hawker" );
	ProcessDay2Item ( CursorState::TongsSteamDumpling , "bb_HarGow" , "HarGow" , hargao_count , "RoundSteamerDumpling" , "_Equipment_hawker" );
	ProcessDay2Item ( CursorState::TongsSiewMai , "bb_SiewMai" , "SiewMai" , siewmai_count , "RoundSteamerSiuMai" , "_Equipment_hawker" );
	ProcessDay2Item ( CursorState::TongsCharSiewBao , "bb_CharSiewBao" , "CharSiewBao" , charsiewbao_count , "CharSiewBao(" , ")_Equipment_hawker" );
	ProcessDay2Item ( CursorState::TongsDouShaBao , "bb_DouShaBao" , "DouShaBao" , doushabao_count , "DouBao(" , ")_Equipment_hawker" );
	ProcessDay2Item ( CursorState::TongsCoffeeBao , "bb_CofeeBao" , "CofeeBao" , coffeebao_count , "CoffeeBao(" , ")_Equipment_hawker" );

	// day 3 foods
	ProcessDay2Item ( CursorState::TongsPlainCCF , "bb_PlainCCF" , "PlainCCF" ,  plainccf_count , "PlainCCF(" , ")_Equipment_hawker" );
	ProcessDay2Item ( CursorState::TongsPrawnCCF , "bb_PrawnCCF" , "PrawnCCF" , prawnccf_count , "PrawnCCF(" , ")_Equipment_hawker" );
	/*if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "bb_ChickenFeet" ) )
	{
		if ( e->on_click_ )
		{
			if ( CheckCursorState ( CursorState::EmptyTongs ) )
			{
				JZEngine::Log::Info ( "Main" , "Chicken Feet Selected" );
				if ( carrotcake_count > 0 )
				{
					FlagCursorState ( CursorState::TongsChickenFeet );
					--chickenfeet_count;
					std::stringstream chickenfeet_name;
					chickenfeet_name << "RoundSteamerFeet" << chickenfeet_count << "_Equipment_hawker";
					Scene ().GetComponent<JZEngine::Texture> ( "ChickenFeet" )->texture_id_ = Scene ().GetTexture ( chickenfeet_name.str () );
				}
			}
			else if ( CheckCursorState ( CursorState::TongsChickenFeet ) )
			{
				JZEngine::Log::Info ( "Main" , "Chicken Feet Returned" );
				FlagCursorState ( CursorState::EmptyTongs );
				++chickenfeet_count;
				std::stringstream chickenfeet_name;
				chickenfeet_name << "RoundSteamerFeet" << chickenfeet_count << "_Equipment_hawker";
				Scene ().GetComponent<JZEngine::Texture> ( "ChickenFeet" )->texture_id_ = Scene ().GetTexture ( chickenfeet_name.str () );
			}
		}
	}*/

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_plate"))
	{
		if (e->on_click_ && !plate_on_hand)
		{
			JZEngine::Log::Info("Main", "Plate Selected");
			FlagCursorState(CursorState::Plate);
		}

		if (e->on_hover_)
		{

			Scene().GetComponent<JZEngine::Transform>("Plate")->scale_.x = 0.77f;
			Scene().GetComponent<JZEngine::Transform>("Plate")->scale_.y = 0.77f;
		}
		else
		{
			Scene().GetComponent<JZEngine::Transform>("Plate")->scale_.x = 0.65f;
			Scene().GetComponent<JZEngine::Transform>("Plate")->scale_.y = 0.65f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tongs"))
	{
		if (e->on_click_ && !plate_on_hand)
		{
			JZEngine::Log::Info("Main", "Tongs Selected");
			FlagCursorState(CursorState::EmptyTongs);
		}
		if (e->on_hover_)
		{

			Scene().GetComponent<JZEngine::Transform>("Tongs")->scale_.x = 0.7f;
			Scene().GetComponent<JZEngine::Transform>("Tongs")->scale_.y = 0.7f;
		}
		else
		{
			Scene().GetComponent<JZEngine::Transform>("Tongs")->scale_.x = 0.59f;
			Scene().GetComponent<JZEngine::Transform>("Tongs")->scale_.y = 0.59f;
		}

	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_scizzors"))
	{
		if (e->on_click_ && !plate_on_hand)
		{
			JZEngine::Log::Info("Main", "Scizzors Selected");
			FlagCursorState(CursorState::Scizzors);
		}
		if ( e->on_hover_ )
		{

			Scene ().GetComponent<JZEngine::Transform> ( "Scizzors" )->scale_.x = 0.7f;
			Scene ().GetComponent<JZEngine::Transform> ( "Scizzors" )->scale_.y = 0.7f;
		}
		else
		{
			Scene ().GetComponent<JZEngine::Transform> ( "Scizzors" )->scale_.x = 0.59f;
			Scene ().GetComponent<JZEngine::Transform> ( "Scizzors" )->scale_.y = 0.59f;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_trashbin"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Trashbin Selected");
			ResetCursors();
			if (CheckCursorState(CursorState::EmptyTongs))
			{
				Scene().EntityFlagActive("EmptyTongs", true);
			}
			if (CheckCursorState(CursorState::Scizzors))
			{
				Scene().EntityFlagActive("ScizzorsCursor", true);
			}
			if (plate_on_hand)
			{
				plate_on_hand = false;
				// make invisible all tray items
				FlagAllTrayItemsFalse();
				// place plate back on tray
				Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_ = original_plate_position_;

				food_cut = false;
				food_soy = false;
				food_spring = false;
			}
		}
		if (e->on_hover_)
		{
			Scene().GetComponent<JZEngine::Transform>("Trashbin")->scale_.x = 0.804f;
			Scene().GetComponent<JZEngine::Transform>("Trashbin")->scale_.y = 0.804f;
		}
		else
		{
			Scene().GetComponent<JZEngine::Transform>("Trashbin")->scale_.x = 0.718f;
			Scene().GetComponent<JZEngine::Transform>("Trashbin")->scale_.y = 0.718f;
		}


	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tray"))
	{
		// if tray was clicked and plate has nothing on it
		if (e->on_click_)
		{
			ShowNotification ( 2 );
			if (plate_on_tray && current_order == CustomerOrder::Nothing)
			{
				switch (cursor_state)
				{
				case CursorState::TongsCarrotCake:
					SetPlateFood(CustomerOrder::CarrotCake);
					FlagAllCursorsFalse();
					break;
				case CursorState::TongsSeaweedChicken:
					SetPlateFood(CustomerOrder::SeaweedChicken);
					FlagAllCursorsFalse();
					break;
				case CursorState::TongsSpringroll:
					SetPlateFood(CustomerOrder::SpringRoll);
					FlagAllCursorsFalse();
					break;
				case CursorState::TongsWanton:
					SetPlateFood(CustomerOrder::Wanton);
					FlagAllCursorsFalse();
					break;
				case CursorState::TongsChickenFeet:
					SetPlateFood ( CustomerOrder::ChickenFeet );
					FlagAllCursorsFalse ();
					break;
				case CursorState::TongsSteamDumpling:
					SetPlateFood ( CustomerOrder::HarGao );
					FlagAllCursorsFalse ();
					break;
				case CursorState::TongsSiewMai:
					SetPlateFood ( CustomerOrder::SiewMai );
					FlagAllCursorsFalse ();
					break;
				case CursorState::TongsCharSiewBao:
					SetPlateFood ( CustomerOrder::CharSiewBao );
					FlagAllCursorsFalse ();
					if ( first_time_cut )
					{
						ShowNotification ( 6 );
					}
					break;
				case CursorState::TongsDouShaBao:
					SetPlateFood ( CustomerOrder::DouShaBao );
					FlagAllCursorsFalse ();
					if ( first_time_cut )
					{
						ShowNotification ( 6 );
					}
					break;
				case CursorState::TongsCoffeeBao:
					SetPlateFood ( CustomerOrder::CoffeeBao );
					FlagAllCursorsFalse ();
					if ( first_time_cut )
					{
						ShowNotification ( 6 );
					}
					break;
				case CursorState::TongsPlainCCF:
					SetPlateFood ( CustomerOrder::PlainCCF );
					FlagAllCursorsFalse ();
					break;
				case CursorState::TongsPrawnCCF:
					SetPlateFood ( CustomerOrder::PrawnCCF );
					FlagAllCursorsFalse ();
					break;
				}
			}
			else if (plate_on_tray && current_order != CustomerOrder::Nothing)
			{
				// cut mechanic
				if ( CheckCursorState ( CursorState::Scizzors ) )
				{
					switch ( current_order )
					{
					case ( CustomerOrder::CharSiewBao ):
						Scene ().GetComponent<JZEngine::Texture> ( "tray_charsiewbao" )->texture_id_ = Scene ().GetTexture ( "CharSiewBaoCUT01_Food_Hawker" );
						food_cut = true;
						if ( first_time_cut )
						{
							ToggleGuidedCircle ( "gtc_scizzors" , false );
							first_time_cut = false;
						}
						break;
					case ( CustomerOrder::DouShaBao ):
						Scene ().GetComponent<JZEngine::Texture> ( "tray_doushabao" )->texture_id_ = Scene ().GetTexture ( "DouShaBaoCUT01_Food_Hawker" );
						food_cut = true;
						if ( first_time_cut )
						{
							ToggleGuidedCircle ( "gtc_scizzors" , false );
							first_time_cut = false;
						}
						break;
					case ( CustomerOrder::CoffeeBao ):
						Scene ().GetComponent<JZEngine::Texture> ( "tray_coffeebao" )->texture_id_ = Scene ().GetTexture ( "CoffeeBaoCUT01_Food_Hawker" );
						food_cut = true;
						if ( first_time_cut )
						{
							ToggleGuidedCircle ( "gtc_scizzors" , false );
							first_time_cut = false;
						}
						break;
					case (	CustomerOrder::PlainCCF ):
						if ( !food_cut )
						{
							Scene ().GetComponent<JZEngine::Texture> ( "tray_plainccf" )->texture_id_ = Scene ().GetTexture ( "PlainCCF_CUT_Food_Hawker" );
							food_cut = true;
							if ( first_time_garnish )
							{
								ShowNotification ( 7 );
							}
						}
						break;
					case ( CustomerOrder::PrawnCCF ):
						if ( !food_cut )
						{
							Scene ().GetComponent<JZEngine::Texture> ( "tray_prawnccf" )->texture_id_ = Scene ().GetTexture ( "PrawnCCF_CUT_Food_Hawker" );
							food_cut = true;
							if ( first_time_garnish )
							{
								ShowNotification ( 7 );
							}
						}
						break;
					}
					FlagAllCursorsFalse ();
				}
				else if ( CheckCursorState ( CursorState::SpringOnion ) )
				{
					if ( food_cut )
					{
						switch ( current_order )
						{
						case ( CustomerOrder::PlainCCF ):
							food_spring = true;
							if ( food_soy )
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_plainccf" )->texture_id_ = Scene ().GetTexture ( "PlainCCF_CUT_ONION_SAUCE_Food_Hawker" );
								if ( first_time_garnish )
								{
									ToggleGuidedCircle ( "gtc_springsoy" , false );
									first_time_garnish = false;
								}
							}
							else
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_plainccf" )->texture_id_ = Scene ().GetTexture ( "PlainCCF_CUT_ONION_Food_Hawker" );
							}
							break;
						case ( CustomerOrder::PrawnCCF ):
							food_spring = true;
							if ( food_soy )
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_prawnccf" )->texture_id_ = Scene ().GetTexture ( "PrawnCCF_CUT_ONION_SAUCE_Food_Hawker" );
								if ( first_time_garnish )
								{
									ToggleGuidedCircle ( "gtc_springsoy" , false );
									first_time_garnish = false;
								}
							}
							else
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_prawnccf" )->texture_id_ = Scene ().GetTexture ( "PrawnCCF_CUT_ONION_Food_Hawker" );
							}
							break;
						}
					}
					FlagAllCursorsFalse ();
				}
				else if ( CheckCursorState ( CursorState::SoySauce ) )
				{
					if ( food_cut )
					{
						switch ( current_order )
						{
						case ( CustomerOrder::PlainCCF ):
							food_soy = true;
							if ( food_spring )
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_plainccf" )->texture_id_ = Scene ().GetTexture ( "PlainCCF_CUT_ONION_SAUCE_Food_Hawker" );
							}
							else
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_plainccf" )->texture_id_ = Scene ().GetTexture ( "PlainCCF_CUT_SAUCE_Food_Hawker" );
							}
							break;
						case ( CustomerOrder::PrawnCCF ):
							food_soy = true;
							if ( food_spring )
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_prawnccf" )->texture_id_ = Scene ().GetTexture ( "PrawnCCF_CUT_ONION_SAUCE_Food_Hawker" );
							}
							else
							{
								Scene ().GetComponent<JZEngine::Texture> ( "tray_prawnccf" )->texture_id_ = Scene ().GetTexture ( "PrawnCCF_CUT_SAUCE_Food_Hawker" );
							}
							break;
						}
					}
					FlagAllCursorsFalse ();
				}
				else
				{
					plate_on_hand = true;
					FlagAllCursorsFalse ();
				}
			}
			else if (!plate_on_tray && CheckCursorState(CursorState::Plate))
			{
				FlagPlateState(true);
				FlagAllCursorsFalse();
			}
		}
	}

	if (plate_on_hand)
	{
		Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_ = JZEngine::Camera::mouse_world_position_;
	}

	//if clicked on phone, change the state to App
	if (JZEngine::InputHandler::IsKeyReleased(JZEngine::KEY::KEY_ESCAPE))
	{
		current_hawker_scene_state = HawkerSceneState::App;
		Scene().EntityFlagActive("PhoneOptions", false);
		paused = true;
	}

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("PhoneOptions"))
	{
		if (e->on_released_)
		{
			//current_hawker_scene_state = HawkerSceneState::App;
			//SetPhoneIcon ( true );
			StartPhoneTransition ( true );
			Scene().EntityFlagActive("PhoneOptions", false);
			paused = true;
			e->on_released_ = false;
		}
		if (e->on_hover_)
		{

			Scene().GetComponent<JZEngine::Transform>("PhoneOptions")->scale_.x = 0.285f;
			Scene().GetComponent<JZEngine::Transform>("PhoneOptions")->scale_.y = 0.285f;
		}
		else
		{
			Scene().GetComponent<JZEngine::Transform>("PhoneOptions")->scale_.x = 0.254f;
			Scene().GetComponent<JZEngine::Transform>("PhoneOptions")->scale_.y = 0.254f;
		}
	}

	// give customer food
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_customer"))
	{
		if (e->on_click_)
		{
			ShowNotification ( 1 );
			//ShowNotification ( 1 );
			if (!plate_on_hand)
			{
				DisplayOrder(GetNextCustomerOrder(wanton_count, seaweedchicken_count, carrotcake_count, springroll_count,
					charsiewbao_count, doushabao_count, coffeebao_count, siewmai_count, hargao_count, chickenfeet_count,
					plainccf_count, prawnccf_count));
			}
			bool instant_win = false;
			if ( JZEngine::InputHandler::IsKeyPressed ( JZEngine::KEY::KEY_LEFT_CONTROL ) )
			{
				instant_win = true;
			}
			if (InteractWithQueue(plate_on_hand || instant_win, current_order, instant_win, food_cut, food_spring, food_soy))
			{
				if (plate_on_hand || instant_win)
				{
					switch ( current_order )
					{
					case ( CustomerOrder::CarrotCake ):
						current_coins += 3.0f;
						break;
					case ( CustomerOrder::SeaweedChicken ):
						current_coins += 1.2f;
						break;
					case ( CustomerOrder::SpringRoll ):
						current_coins += 2.7f;
						break;
					case ( CustomerOrder::Wanton ):
						current_coins += 2.1f;
						break;
					case ( CustomerOrder::ChickenFeet ):
						current_coins += 3.50f;
						break;
					case ( CustomerOrder::HarGao ):
						current_coins += 2.7f;
						break;
					case ( CustomerOrder::SiewMai ):
						current_coins += 2.5f;
						break;
					case ( CustomerOrder::CharSiewBao ):
						current_coins += 0.6f;
						break;
					case ( CustomerOrder::DouShaBao ):
						current_coins += 0.5f;
						break;
					case ( CustomerOrder::CoffeeBao ):
						current_coins += 0.5f;
						break;
					}
					plate_on_hand = false;
					// make invisible all tray items
					FlagAllTrayItemsFalse();
					// place plate back on tray
					Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_ = original_plate_position_;
					// turn off order ui
					UnDisplayOrder();
					// if successfully served customer increment coins
					//current_coins += coin_increment;
					/*UpdateCoinProgressBar();
					coin_bar_animation_play = true;
					coin_sparkles_animation_play = true;*/
					coin_animation_play = true;
					order_success = true;
					DisplayTick ();
					//Scene ().EntityFlagActive ( "CoinSparkles" , true );
					Scene ().EntityFlagActive ( "CoinOnTable" , true );
					//if (current_coins >= target_coins)
					//{
					//	//coin_last_update = true;
					//}
					ToggleGuidedCircle ( "gtc_platecustomer" , false );
					TurnOffNotification ();
					//JZEngine::Log::Info ( "Main" , "test" );
					
				}
			}
			else
			{
				if ( plate_on_hand && current_order != CustomerOrder::Nothing )
				{
					ShowNotification ( 4 );
				}
			}

			food_cut = false;
			food_soy = false;
			food_spring = false;
		}
	}

	if ( won_bar_ )
	{
		if ( won_bar_counter_ < 1.0f )
		{
			won_bar_counter_ += dt;
		}
		else
		{
			HideWonBar ();
			win = true;
			JZEngine::Log::Info ( "Main" , "You have won the game!" );
			//Scene().ChangeScene("MainMenu");
			//ToggleWin ( true );
			ToggleSummary ( true );
			SummaryInit ();
			current_hawker_scene_state = HawkerSceneState::Win;
		}
	}

	// process order ui
	DisplayUpdate(dt);
}

void HawkerSceneInit()
{

	Scene().SetCameraDimensions(1977, 1112);
	// initialize scene
	current_hawker_scene_state = HawkerSceneState::Goal;
	//esc_again = false;

	JZEngine::Animation2D* scroll = Scene().GetComponent<JZEngine::Animation2D>("ScrollDay1");
	scroll->pause_ = true;
	scroll->frame_ = 0;

	scroll = Scene().GetComponent<JZEngine::Animation2D>("ScrollDay2");
	scroll->pause_ = true;
	scroll->frame_ = 0;

	scroll = Scene().GetComponent<JZEngine::Animation2D>("ScrollDay3");
	scroll->pause_ = true;
	scroll->frame_ = 0;


	Scene ().EntityFlagActive ( "CoinSparkles" , false );
	og_coin_position = Scene ().GetComponent<JZEngine::Transform> ( "CoinOnTable" )->position_;
	og_coin_distance_from_bar = (Scene ().GetComponent<JZEngine::Transform> ( "CoinBar" )->position_ 
		- Scene ().GetComponent<JZEngine::Transform> ( "CoinOnTable" )->position_).Len();
	Scene ().EntityFlagActive ( "CoinOnTable" , false );

	/*notification_display_ = false;
	notification_time_counter_ = 0.0f;*/
	for ( int i = 0; i < notification_count_; ++i )
	{
		notification_shown[ i ] = false;
	}

	ToggleWin(false);
	ToggleSummary ( false );
	ToggleConfirm(false);
	InitHawkerQueue();
	InitPhoneScreen();
	cursor_state = CursorState::Nothing;
	plate_on_tray = false;
	plate_on_hand = false;
	original_plate_position_ = { 0.0f, 0.0f };
	current_order = CustomerOrder::Nothing;
	display_time_ = 4.0f;
	timer_ = display_time_;
	display_up_ = false;
	greenbar_original_scale_y = Scene().GetComponent<JZEngine::Transform>("GreenBar")->scale_.y;

	if ( hawker_scene_day == DAY::ONE )
	{
		target_coins = 28.0f;
	}
	else if ( hawker_scene_day == DAY::TWO )
	{
		target_coins = 35.0f;
	}
	else if ( hawker_scene_day == DAY::THREE )
	{
		target_coins = 46.0f;
	}
	current_coins = 0;
	current_coin_scale = 0.0f;
	total_time = 60.0f;
	current_time = 0.0f;
	//current_angry_customers = 0;
	win = false;
	lose = false;

	HideWonBar ();
	//FlagLoseBar ( false );
	won_bar_ = false;
	won_bar_counter_ = 0.0f;
	win_shortcut = false;

	// set scale of coin bar and angry customer bar to 0
	//initial_progress_scale = 7.537f;

	coin_bar_animation_play = false;
	coin_bar_played_once = false;
	coin_sparkles_animation_play = false;
	coin_sparkles_play_count = 0;
	coin_animation_play = false;
	coin_played_once = false;
	coin_suck = false;
	coin_last_update = false;

	Scene().GetComponent<JZEngine::Transform>("ui_coin_progress")->scale_.x = 1.0f;
	Scene().GetComponent<JZEngine::Transform>("ui_goal_progress")->scale_.x = 1.0f;

	// initialize cursors
	ResetCursors();

	// inititalize tray items
	original_plate_position_ = Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_;
	FlagAllTrayItemsFalse();

	// turn off order ui
	UnDisplayOrder();

	SetCoinText("$", current_coins);
	SetGoalText("$", target_coins);

	/*Scene().GetComponent<JZEngine::TextData>("Win_words")->text = JZEngine::String("I knew you had it in you Baozi,");
	Scene().GetComponent<JZEngine::TextData>("Win_words2")->text = JZEngine::String("    continue to the next level?    ");*/

	Scene ().GetComponent<JZEngine::TextData> ( "Win_words" )->text = JZEngine::String ( " " );
	Scene ().GetComponent<JZEngine::TextData> ( "Win_words2" )->text = JZEngine::String ( " " );

	JZEngine::Log::Info("Main", "Hawker Scene Initialized.");

	InitGuidedCircles ();
	if ( hawker_scene_day == DAY::ONE )
	{
		current_notification = 0;
	}
	else if ( hawker_scene_day == DAY::TWO )
	{
		current_notification = 6;
	}
	else if ( hawker_scene_day == DAY::THREE )
	{
		current_notification = 7;
	}
	first_time_cut = true;
	//ShowNotification ( 0 );

	// temporarily remove upgrades
	Scene ().EntityFlagActive ( "RoundSteamer" , false );
	Scene ().EntityFlagActive ( "SideTray" , false );

	customers_in_queue_ = 0;

	// set food count
	springroll_count = 5;
	carrotcake_count = 5;
	wanton_count = 5;
	seaweedchicken_count = 5;
	chickenfeet_count = 3;
	hargao_count = 3;
	siewmai_count = 3;
	charsiewbao_count = 3;
	doushabao_count = 3;
	coffeebao_count = 3;
	plainccf_count = 5;
	prawnccf_count = 5;

	// shop init
	FlagShopActive ( true );

	std::stringstream ss;
	ss << springroll_count;
	Scene ().GetComponent<JZEngine::TextData> ( "Springroll_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Springroll_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	ss.str ( "" );
	ss << seaweedchicken_count;
	Scene ().GetComponent<JZEngine::TextData> ( "Seaweedchicken_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Seaweedchicken_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	ss.str ( "" );
	ss << wanton_count;
	Scene ().GetComponent<JZEngine::TextData> ( "Dumpling_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Dumpling_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	ss.str ( "" );
	ss << carrotcake_count;
	Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	SetUIntTextAmt ( "Shop2_amt_springroll" , springroll_count );
	SetUIntTextAmt ( "Shop2_amt_seaweedchicken" , seaweedchicken_count );
	SetUIntTextAmt ( "Shop2_amt_frieddumpling" , wanton_count );
	SetUIntTextAmt ( "Shop2_amt_friedcarrotcake" , carrotcake_count );
	SetUIntTextAmt ( "Shop2_amt_charsiewbun" , charsiewbao_count );
	SetUIntTextAmt ( "Shop2_amt_redbeanbun" , doushabao_count );
	SetUIntTextAmt ( "Shop2_amt_coffeebun" , coffeebao_count );
	SetUIntTextAmt ( "Shop2_amt_chickendumpling" , siewmai_count );
	SetUIntTextAmt ( "Shop2_amt_prawndumpling" , hargao_count );
	SetUIntTextAmt ( "Shop2_amt_chickenfeet" , chickenfeet_count );

	// day 3
	SetUIntTextAmt ( "Shop3_amt_hargao" , hargao_count );
	SetUIntTextAmt ( "Shop3_amt_chickenfeet" , chickenfeet_count );
	SetUIntTextAmt ( "Shop3_amt_plainccf" , plainccf_count );
	SetUIntTextAmt ( "Shop3_amt_prawnccf" , prawnccf_count );

	// initialize goal
	FlagGoalActive ( true );
	InitGoal ();

	// initialize phone transition
	phone_transition_play = false;
	phone_icon_open = false;
	phone_icon_value = 0.0f;
	transition_speed = 4.0f;
	Scene ().EntityFlagActive ( "PhoneTransition" , false );

	InitLoseBar ();

	InitSky ();

	InitDay ();

	// to reset shop for the day
	FlagShopActive ( false );
	FlagShopActive ( true );

	Scene ().GetComponent<JZEngine::Transform> ( "Plate" )->position_.x = -159.0f;
	Scene ().GetComponent<JZEngine::Transform> ( "bb_plate" )->position_.x = -159.0f;
	Scene ().GetComponent<JZEngine::Transform> ( "Tongs" )->position_.x = 200.0f;
	Scene ().GetComponent<JZEngine::Transform> ( "bb_tongs" )->position_.x = 200.0f;

	Scene().EntityFlagActive("SpringOnion", false);
	Scene().EntityFlagActive("SoySauce", false);


	if ( hawker_scene_day == DAY::ONE )
	{
		Scene ().EntityFlagActive ( "Scizzors" , false );
		Scene ().EntityFlagActive ( "bb_scizzors" , false );

		Scene ().GetComponent<JZEngine::Texture> ( "Goal_one" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay01_UI_hawker_01" );
		Scene ().GetComponent<JZEngine::Texture> ( "Goal_two" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay01_UI_hawker_02" );
		Scene ().GetComponent<JZEngine::Texture> ( "Goal_three" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay01_UI_hawker_03" );

		wallet_amt = 12.50f;

		num_springroll = 5;
		num_seaweedchicken = 7;
		num_dumpling = 5;
		num_carrotcake = 6;
	}
	else if (hawker_scene_day == DAY::TWO)
	{
		Scene ().GetComponent<JZEngine::Transform> ( "Plate" )->position_.x -= 200.0f;
		Scene ().GetComponent<JZEngine::Transform> ( "bb_plate" )->position_.x -= 200.0f;
		Scene ().GetComponent<JZEngine::Transform> ( "Tongs" )->position_.x += 200.0f;
		Scene ().GetComponent<JZEngine::Transform> ( "bb_tongs" )->position_.x += 200.0f;

		Scene ().GetComponent<JZEngine::Texture> ( "Goal_one" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay02_UI_hawker_01" );
		Scene ().GetComponent<JZEngine::Texture> ( "Goal_two" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay02_UI_hawker_02" );
		Scene ().GetComponent<JZEngine::Texture> ( "Goal_three" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay02_UI_hawker_03" );

		num_springroll = 5;
		num_seaweedchicken = 5;
		num_dumpling = 4;
		num_carrotcake = 4;
		num_chickenfeet = 1;
		num_siewmai = 1;
		num_hargao = 1;
		num_charsiewbao = 2;
		num_doushabao = 2;
		num_coffeebao = 2;
	}
	else if (hawker_scene_day == DAY::THREE)
	{
		//temp
		wallet_amt = 100.0f;

		Scene ().GetComponent<JZEngine::Transform> ( "Plate" )->position_.x -= 200.0f;
		Scene ().GetComponent<JZEngine::Transform> ( "bb_plate" )->position_.x -= 200.0f;
		Scene ().GetComponent<JZEngine::Transform> ( "Tongs" )->position_.x += 200.0f;
		Scene ().GetComponent<JZEngine::Transform> ( "bb_tongs" )->position_.x += 200.0f;

		Scene().EntityFlagActive("SpringOnion", true);
		Scene().EntityFlagActive("SoySauce", true);

		Scene ().GetComponent<JZEngine::Texture> ( "Goal_one" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay03_UI_hawker_01" );
		Scene ().GetComponent<JZEngine::Texture> ( "Goal_two" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay03_UI_hawker_02" );
		Scene ().GetComponent<JZEngine::Texture> ( "Goal_three" )->texture_id_ = Scene ().GetTexture ( "TutorialDadDay03_UI_hawker_03" );

		num_springroll = 3;
		num_seaweedchicken = 3;
		num_dumpling = 6;
		num_carrotcake = 6;
		num_chickenfeet = 2;
		num_siewmai = 1;
		num_hargao = 2;
		num_charsiewbao = 1;
		num_doushabao = 2;
		num_coffeebao = 2;
		num_plainccf = 4;
		num_prawnccf = 4;
	}
}

void HawkerSceneUpdate(float dt)
{
	float& black_from_cutscene = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "BlackFromCutscene" )->tint.w;
	if ( black_from_cutscene > 0.0f )
	{
		black_from_cutscene -= dt;
		return;
	}

	bool food_count = springroll_count <= 0 && carrotcake_count <= 0 && wanton_count <= 0 && seaweedchicken_count <= 0;
	if ( hawker_scene_day == DAY::TWO )
	{
		food_count = food_count && ( chickenfeet_count <= 0 && hargao_count <= 0 && siewmai_count <= 0 && charsiewbao_count <= 0 && doushabao_count <= 0 && coffeebao_count <= 0 );
	}
	if ( hawker_scene_day == DAY::THREE )
	{
		food_count = food_count && ( plainccf_count <= 0 && prawnccf_count <= 0 );
	}

	if (( num_customers <= 0 ||
		food_count) &&
		current_hawker_scene_state != HawkerSceneState::Win)
	{
		/*FlagLoseBar ( true );
		current_hawker_scene_state = HawkerSceneState::Lose;*/
		// check if win or lose

		if ( current_coins >= target_coins )
		{
			// win
			coin_last_update = true;
		}
		else
		{
			// lose
			FlagLoseBar ( true );
			current_hawker_scene_state = HawkerSceneState::Lose;
		}
	}

	// win lose shortcut
	if ( JZEngine::InputHandler::IsKeyPressed ( JZEngine::KEY::KEY_W ) )
	{
		win_shortcut = true;
	}
	if ( JZEngine::InputHandler::IsKeyPressed ( JZEngine::KEY::KEY_L ) )
	{
		// lose
		FlagLoseBar ( true );
		current_hawker_scene_state = HawkerSceneState::Lose;
	}

	if ( day_begin )
	{
		if ( day_time > 0.0f )
		{
			day_time -= dt;
		}
		else
		{
			BringNightSky ( dt );
		}
	}

	// update phone transition
	UpdatePhoneTransition ( dt );

	if ( customers_in_queue_ > 0 && click_customer_notification )
	{
		click_customer_notification = false;
		ShowNotification ( 0 );
	}
	UpdateGuidedCircle ( dt );

	if ( hawker_queue_display_order_toggle )
	{
		UnDisplayOrder ();
		hawker_queue_display_order_toggle = false;
	}

	switch (current_hawker_scene_state)
	{
	case HawkerSceneState::Main:
		UpdateMainScene(dt);
		break;
	case HawkerSceneState::Win:
		UpdateWinScreen(dt);
		break;
	case HawkerSceneState::App:
		if (!paused)
		{
			//phone_icon_open = false;
			//SetPhoneIcon ( false );
			//current_hawker_scene_state = HawkerSceneState::Main;
			StartPhoneTransition ( false );
		}
		else
		{
			UpdateHomeScreen ( dt );
		}
		break;
	case HawkerSceneState::Shop:
		UpdateShop (dt);
		break;
	case HawkerSceneState::Goal:
		UpdateGoal (dt);
		break;
	case HawkerSceneState::Lose:
		UpdateLoseBar ( dt );
		break;
	}
}

void ResetCursors()
{
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("EmptyTongs"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("TongsCarrotCake"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("TongsDumpling"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("TongsSeaweedChicken"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("TongsSpringroll"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("ScizzorsCursor"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	if (JZEngine::Transform* cursor = Scene().GetComponent<JZEngine::Transform>("PlateCursor"))
	{
		cursor->child_position_ = { 0.0f, 0.0f };
	}
	FlagAllCursorsFalse();
}