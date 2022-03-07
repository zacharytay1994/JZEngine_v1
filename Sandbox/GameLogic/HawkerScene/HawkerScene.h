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

#include "../ButtonLogic.h"

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
	TongsCarrotCake
};

std::string cursor_object_names[] = {
	"Nothing",
	"EmptyTongs",
	"ScizzorsCursor",
	"PlateCursor",
	"TongsDumpling",
	"TongsSeaweedChicken",
	"TongsSpringroll",
	"TongsCarrotCake"
};

CursorState cursor_state = CursorState::Nothing;

void FlagAllCursorsFalse()
{
	Scene().EntityFlagActive("EmptyTongs", false);
	Scene().EntityFlagActive("TongsCarrotCake", false);
	Scene().EntityFlagActive("TongsDumpling", false);
	Scene().EntityFlagActive("TongsSeaweedChicken", false);
	Scene().EntityFlagActive("TongsSpringroll", false);
	Scene().EntityFlagActive("ScizzorsCursor", false);
	Scene().EntityFlagActive("PlateCursor", false);
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
		state == CursorState::TongsWanton )
	{
		Scene ().GetComponent<JZEngine::Texture> ( "Tongs" )->texture_id_ = Scene ().GetTexture ( "Tongs(Shaded)_Equipment_hawker" );
	}
}

bool CheckCursorState(CursorState state)
{
	return state == cursor_state;
}

void ResetCursors();

/*!
 * @brief CURSOR CODE - END
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
 * @brief BEGIN SHOP - START
*/

void FlagShopActive ( bool flag )
{
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
}

unsigned int springroll_count { 8 };
unsigned int carrotcake_count { 8 };
unsigned int wanton_count { 9 };
unsigned int seaweedchicken_count { 7 };

unsigned int init_springroll_count { 0 };
unsigned int init_carrotcake_count { 0 };
unsigned int init_wanton_count { 0 };
unsigned int init_seaweedchicken_count { 0 };

unsigned int summary_sr_count { 0 };
unsigned int summary_sc_count { 0 };
unsigned int summary_fd_count { 0 };
unsigned int summary_cc_count { 0 };

unsigned int min_count { 0 };
unsigned int max_count { 10 };

void UpdateShop ()
{
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "BeginShop_Next" ) )
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

			FlagShopActive ( false );
			current_hawker_scene_state = HawkerSceneState::Main;

			init_springroll_count = springroll_count;
			init_carrotcake_count = carrotcake_count;
			init_wanton_count = wanton_count;
			init_seaweedchicken_count = seaweedchicken_count;
		}
	}
	// spring roll
	if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Shop_a_springroll" ) )
	{
		if ( e->on_released_ )
		{
			if ( springroll_count < max_count )
				++springroll_count;
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
			std::stringstream ss;
			ss << carrotcake_count;
			Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "Carrotcake_amt" )->text = JZEngine::String ( ss.str ().c_str () );
		}
	}

	float total_amt = 0.4f * springroll_count + 0.2f * seaweedchicken_count + 0.3f * wanton_count + 0.5f * carrotcake_count;
	std::stringstream ss;
	ss << "$" << std::setprecision (2) << std::fixed << total_amt;
	Scene ().GetComponent<JZEngine::TextData> ( "Total_amt" )->color_ = { 0.0f,0.0f,0.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "Total_amt" )->text = JZEngine::String ( ss.str ().c_str () );
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
	current_order = CustomerOrder::Nothing;
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
	current_coin_scale
		= static_cast<float>(current_coins) / static_cast<float>(target_coins) * initial_progress_scale;
}

bool won_bar_ { false };
float won_bar_counter_ { 0.0f };
bool coin_last_update { false };

void ShowWonBar ();
void AnimateCoinProgreeBar (float dt)
{
	float& x = Scene ().GetComponent<JZEngine::Transform> ( "ui_coin_progress" )->scale_.x;
	if ( x < current_coin_scale)
	{
		x += dt;
	}
	if ( coin_last_update && x > initial_progress_scale )
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
float notification_time_ { 3.0f };
float notification_time_counter_ { 0.0f };
constexpr int notification_count_ { 5 };
std::string notification[ notification_count_ ] =
{
	"Baozi! Click the customer for orders.",
	"Baozi! Use a tong to grab the food.",
	"Put it on the plate and serve it!",
	"For wrong orders, throw it in the bin.",
	"Don't take too long! They will get angry."
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

void ShowNotification (int i)
{
	TurnOffNotification ();
	if ( i < 5 )
	{
		if ( !notification_shown[ i ] )
		{
			notification_shown[ i ] = true;
			Scene ().GetComponent<JZEngine::TextData> ( "NotificationText" )->text = JZEngine::String ( notification[ i ].c_str () );
			Scene ().EntityFlagActive ( "NotificationText" , true );
			Scene ().EntityFlagActive ( "NotificationBar" , true );
			Scene ().GetComponent<JZEngine::AnimatedTransformComponent> ( "PhoneOptions" )->active_flag = true;
			notification_display_ = true;
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
	Scene ().EntityFlagActive ( "WinBlackCover" , false );
}

void ShowWonBar ()
{
	Scene ().EntityFlagActive ( "WinBar" , true );
	Scene ().EntityFlagActive ( "WinBarBG" , true );
	Scene ().EntityFlagActive ( "WinFireworks1" , true );
	Scene ().EntityFlagActive ( "WinFireworks2" , true );
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
}

bool summary_ready { false };
float summary_counter { 0.0f };
void SummaryInit ()
{
	summary_ready = false;
	Scene ().EntityFlagActive ( "BeginBlack" , true );
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "BeginBlack" )->tint.w = 0.0f;
	Scene ().GetComponent<JZEngine::Transform> ( "Summary_screen" )->position_.y = 2048.0f;

	summary_sr_count = 0;
	summary_sc_count = 0;
	summary_fd_count = 0;
	summary_cc_count = 0;

	summary_counter = 0.0f;

	std::stringstream ss;
	ss << "";
	Scene ().GetComponent<JZEngine::TextData> ( "sum_sr_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "sum_sr_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	Scene ().GetComponent<JZEngine::TextData> ( "sum_sc_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "sum_sc_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	Scene ().GetComponent<JZEngine::TextData> ( "sum_fd_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "sum_fd_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	Scene ().GetComponent<JZEngine::TextData> ( "sum_cc_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "sum_cc_amt" )->text = JZEngine::String ( ss.str ().c_str () );

	Scene ().GetComponent<JZEngine::TextData> ( "sum_total_amt" )->color_ = { 1.0f,1.0f,1.0f };
	Scene ().GetComponent<JZEngine::TextData> ( "sum_total_amt" )->text = JZEngine::String ( ss.str ().c_str () );
}

void UpdateWinScreen(float dt)
{
	UNREFERENCED_PARAMETER(dt);
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
		summary_y -= 1024.0f * dt;
		ready = false;
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

			std::stringstream ss;
			ss << summary_sr_count << " pcs";
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sr_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sr_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			ss.str ("");
			ss << summary_sc_count << " pcs";
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sc_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_sc_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			ss.str ( "" );
			ss << summary_fd_count << " pcs";
			Scene ().GetComponent<JZEngine::TextData> ( "sum_fd_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_fd_amt" )->text = JZEngine::String ( ss.str ().c_str () );
			ss.str ( "" );
			ss << summary_cc_count << " pcs";
			Scene ().GetComponent<JZEngine::TextData> ( "sum_cc_amt" )->color_ = { 1.0f,1.0f,1.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_cc_amt" )->text = JZEngine::String ( ss.str ().c_str () );

			float total_amt = 2.7f * summary_sr_count + 1.2f * summary_sc_count + 2.1f * summary_fd_count + 3.0f * summary_cc_count;
			ss.str ( "" );
			ss << "$" << std::setprecision(2) << std::fixed << total_amt;
			Scene ().GetComponent<JZEngine::TextData> ( "sum_total_amt" )->color_ = { 0.0f,0.0f,0.0f };
			Scene ().GetComponent<JZEngine::TextData> ( "sum_total_amt" )->text = JZEngine::String ( ss.str ().c_str () );

			if ( done_updating )
			{
				summary_ready = true;
			}
		}
	}


	if ( summary_ready )
	{
		if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Win_restart_bb" ) )
		{
			if ( e->on_released_ )
			{
				//Scene().ChangeScene("MainMenu");
			}
		}
		if ( JZEngine::MouseEvent* e = Scene ().GetComponent<JZEngine::MouseEvent> ( "Win_exit_bb" ) )
		{
			if ( e->on_released_ )
			{
				Scene ().ChangeScene ( "MainMenu" );
			}
		}
	}
}

/*!
 * @brief WIN - END
 * **********************************************************************
*/

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
		ShowNotification ( 4 );
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
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_plate"))
	{
		if (e->on_click_ && !plate_on_hand)
		{
			JZEngine::Log::Info("Main", "Plate Selected");
			FlagCursorState(CursorState::Plate);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tongs"))
	{
		if (e->on_click_ && !plate_on_hand)
		{
			ShowNotification ( 2 );
			JZEngine::Log::Info("Main", "Tongs Selected");
			FlagCursorState(CursorState::EmptyTongs);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_scizzors"))
	{
		if (e->on_click_ && !plate_on_hand)
		{
			/*JZEngine::Log::Info("Main", "Scizzors Selected");
			FlagCursorState(CursorState::Scizzors);*/
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
			}
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tray"))
	{
		// if tray was clicked and plate has nothing on it
		if (e->on_click_)
		{
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
				}
			}
			else if (plate_on_tray && current_order != CustomerOrder::Nothing)
			{
				plate_on_hand = true;
				FlagAllCursorsFalse();
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
			current_hawker_scene_state = HawkerSceneState::App;
			Scene().EntityFlagActive("PhoneOptions", false);
			paused = true;
		}
	}

	// give customer food
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_customer"))
	{
		if (e->on_click_)
		{
			ShowNotification ( 1 );
			if (!plate_on_hand)
			{
				DisplayOrder(GetNextCustomerOrder(wanton_count, seaweedchicken_count, carrotcake_count, springroll_count));
			}
			bool instant_win = false;
			if ( JZEngine::InputHandler::IsKeyPressed ( JZEngine::KEY::KEY_LEFT_CONTROL ) )
			{
				instant_win = true;
			}
			if (InteractWithQueue(plate_on_hand || instant_win, current_order, instant_win))
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
					if (current_coins >= target_coins)
					{
						coin_last_update = true;
					}
				}
			}
			else
			{
				if ( plate_on_hand && current_order != CustomerOrder::Nothing )
				{
					ShowNotification ( 3 );
				}
			}
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
	// initialize scene
	current_hawker_scene_state = HawkerSceneState::Goal;
	//esc_again = false;
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

	target_coins = 10.0f;
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

	ShowNotification ( 0 );

	// temporarily remove upgrades
	Scene ().EntityFlagActive ( "RoundSteamer" , false );
	Scene ().EntityFlagActive ( "SideTray" , false );

	customers_in_queue_ = 0;

	// set food count
	springroll_count = 8;
	carrotcake_count = 8;
	wanton_count = 9;
	seaweedchicken_count = 7;

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

	// initialize goal
	FlagGoalActive ( true );
	InitGoal ();

	InitLoseBar ();
}

void HawkerSceneUpdate(float dt)
{
	if (( num_customers <= 0 ||
		(springroll_count <= 0 && carrotcake_count <= 0 && wanton_count <= 0 && seaweedchicken_count <= 0)) &&
		current_hawker_scene_state != HawkerSceneState::Win)
	{
		FlagLoseBar ( true );
		current_hawker_scene_state = HawkerSceneState::Lose;
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
		UpdateHomeScreen(dt);
		if (!paused)
		{
			current_hawker_scene_state = HawkerSceneState::Main;
		}
		break;
	case HawkerSceneState::Shop:
		UpdateShop ();
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