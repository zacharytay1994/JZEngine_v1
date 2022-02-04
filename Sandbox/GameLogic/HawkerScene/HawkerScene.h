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
	App
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
}

void FlagCursorState(CursorState state)
{
	FlagAllCursorsFalse();
	cursor_state = state;
	Scene().EntityFlagActive(cursor_object_names[static_cast<int>(cursor_state)], true);
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

int target_coins{ 500 };
int current_coins{ 0 };
int coin_increment{ 100 };
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

			SetCoinText ( "$" , current_coins );
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

void UpdateWinScreen(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Win_restart_bb"))
	{
		if (e->on_released_)
		{
			Scene().ChangeScene("HawkerV2");
		}
		if (e->on_held_)
		{
			ToggleButton("Win_restart", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Win_restart", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Win_restart", ButtonState::Normal);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Win_exit_bb"))
	{
		if (e->on_released_)
		{
			Scene().ChangeScene("MainMenu");
		}
		if (e->on_held_)
		{
			ToggleButton("Win_exit", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Win_exit", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Win_exit", ButtonState::Normal);
		}
	}
}

/*!
 * @brief WIN - END
 * **********************************************************************
*/
unsigned int springroll_count_ { 10 };


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
				FlagCursorState(CursorState::TongsSpringroll);
				if ( springroll_count_ > 0 )
				{
					--springroll_count_;
					std::stringstream springroll_name;
					springroll_name << "DryFoodSpringRoll(" << springroll_count_ << ")_Equipment_hawker";
					Scene ().GetComponent<JZEngine::Texture> ( "SpringRoll" )->texture_id_ = Scene ().GetTexture ( springroll_name.str () );
				}
			}
			else if (CheckCursorState(CursorState::TongsSpringroll))
			{
				JZEngine::Log::Info("Main", "SpringRoll Returned");
				FlagCursorState(CursorState::EmptyTongs);
				++springroll_count_;
				std::stringstream springroll_name;
				springroll_name << "DryFoodSpringRoll(" << springroll_count_ << ")_Equipment_hawker";
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
				FlagCursorState(CursorState::TongsWanton);
			}
			else if (CheckCursorState(CursorState::TongsWanton))
			{
				JZEngine::Log::Info("Main", "Wanton Returned");
				FlagCursorState(CursorState::EmptyTongs);
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
				FlagCursorState(CursorState::TongsSeaweedChicken);
			}
			else if (CheckCursorState(CursorState::TongsSeaweedChicken))
			{
				JZEngine::Log::Info("Main", "SeaweedChicken Returned");
				FlagCursorState(CursorState::EmptyTongs);
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
				FlagCursorState(CursorState::TongsCarrotCake);
			}
			else if (CheckCursorState(CursorState::TongsCarrotCake))
			{
				JZEngine::Log::Info("Main", "CarrotCake Returned");
				FlagCursorState(CursorState::EmptyTongs);
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
			JZEngine::Log::Info("Main", "Scizzors Selected");
			FlagCursorState(CursorState::Scizzors);
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
				DisplayOrder(GetNextCustomerOrder());
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
					plate_on_hand = false;
					// make invisible all tray items
					FlagAllTrayItemsFalse();
					// place plate back on tray
					Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_ = original_plate_position_;
					// turn off order ui
					UnDisplayOrder();
					// if successfully served customer increment coins
					current_coins += coin_increment;
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
			ToggleWin ( true );
			current_hawker_scene_state = HawkerSceneState::Win;
		}
	}

	// process order ui
	DisplayUpdate(dt);
}

void HawkerSceneInit()
{
	// initialize scene
	current_hawker_scene_state = HawkerSceneState::Main;
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

	target_coins = 500;
	current_coins = 0;
	current_coin_scale = 0.0f;
	total_time = 60.0f;
	current_time = 0.0f;
	//current_angry_customers = 0;
	win = false;
	lose = false;

	HideWonBar ();
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
	
	// setup food
	std::stringstream springroll_name;
	springroll_name << "DryFoodSpringRoll(" << springroll_count_ << ")_Equipment_hawker";
	Scene ().GetComponent<JZEngine::Texture> ( "SpringRoll" )->texture_id_ = Scene ().GetTexture ( springroll_name.str () );

	// temporarily remove upgrades
	Scene ().EntityFlagActive ( "RoundSteamer" , false );
	Scene ().EntityFlagActive ( "SideTray" , false );

}

void HawkerSceneUpdate(float dt)
{
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