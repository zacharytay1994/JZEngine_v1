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
	// reset flags
	display_up_ = false;
	timer_ = display_time_;
	display_up_ = false;
	Scene().GetComponent<JZEngine::Transform>("GreenBar")->scale_.y = greenbar_original_scale_y;
}

void DisplayOrder(CustomerOrder order)
{
	UnDisplayOrder();
	// flag board
	Scene().EntityFlagActive("OrderBoard", true);
	Scene().EntityFlagActive("EmptyBar", true);
	Scene().EntityFlagActive("GreenBar", true);
	Scene().EntityFlagActive("RedBar", true);
	display_up_ = true;
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
float initial_progress_scale{ 1.0f };

void UpdateCoinProgressBar()
{
	Scene().GetComponent<JZEngine::Transform>("ui_coin_progress")->scale_.x 
		= static_cast<float>(current_coins) / static_cast<float>(target_coins) * initial_progress_scale;
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
void SetCoinText(T...text)
{
	std::stringstream ss;
	((ss << text), ...);
	Scene().GetComponent<JZEngine::TextData>("ui_coin_text")->text = JZEngine::String(ss.str().c_str());
}

template <typename...T>
void SetGoalText(T...text)
{
	std::stringstream ss;
	((ss << text), ...);
	Scene().GetComponent<JZEngine::TextData>("ui_goal_text")->text = JZEngine::String(ss.str().c_str());
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

void UpdateMainScene(float dt)
{
	UpdateHawkerQueue(dt);
	//UpdateGoalProgressBar(dt);

	// process click inputs
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_springroll"))
	{
		if (e->on_click_)
		{
			if (CheckCursorState(CursorState::EmptyTongs))
			{
				JZEngine::Log::Info("Main", "SpringRoll Selected");
				FlagCursorState(CursorState::TongsSpringroll);
			}
			else if (CheckCursorState(CursorState::TongsSpringroll))
			{
				JZEngine::Log::Info("Main", "SpringRoll Returned");
				FlagCursorState(CursorState::EmptyTongs);
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
		//esc_again = true;
	}

	// give customer food
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_customer"))
	{
		if (e->on_click_)
		{
			if (!plate_on_hand)
			{
				DisplayOrder(GetNextCustomerOrder());
			}
			if (InteractWithQueue(plate_on_hand, current_order))
			{
				if (plate_on_hand)
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
					SetCoinText("$", current_coins);
					UpdateCoinProgressBar();
					if (current_coins >= target_coins)
					{
						win = true;
						JZEngine::Log::Info("Main", "You have won the game!");
						//Scene().ChangeScene("MainMenu");
						ToggleWin(true);
						current_hawker_scene_state = HawkerSceneState::Win;
					}
				}
			}
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
	total_time = 60.0f;
	current_time = 0.0f;
	//current_angry_customers = 0;
	win = false;
	lose = false;

	// set scale of coin bar and angry customer bar to 0
	initial_progress_scale = 6.4f;
	Scene().GetComponent<JZEngine::Transform>("ui_coin_progress")->scale_.x = 0.0f;
	Scene().GetComponent<JZEngine::Transform>("ui_goal_progress")->scale_.x = 0.0f;

	// initialize cursors
	ResetCursors();

	// inititalize tray items
	original_plate_position_ = Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_;
	FlagAllTrayItemsFalse();

	// turn off order ui
	UnDisplayOrder();

	SetCoinText("$", current_coins);
	SetGoalText("$", target_coins);

	Scene().GetComponent<JZEngine::TextData>("Win_words")->text = JZEngine::String("I knew you had it in you Baozi,");
	Scene().GetComponent<JZEngine::TextData>("Win_words2")->text = JZEngine::String("    continue to the next level?    ");

	JZEngine::Log::Info("Main", "Hawker Scene Initialized.");
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