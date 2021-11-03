#pragma once
#include <JZEngine.h>
#include "HawkerQueue.h"
#include <string>

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

//enum class TrayPlateState
//{
//	Nothing,
//	Wanton,
//	SeaweedChicken,
//	SpringRoll,
//	CarrotCake,
//};

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
void HawkerSceneInit()
{
	InitHawkerQueue();

	// initialize cursors
	ResetCursors();

	// inititalize tray items
	original_plate_position_ = Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_;
	FlagAllTrayItemsFalse();

	JZEngine::Log::Info("Main", "Hawker Scene Initialized.");
}

void HawkerSceneUpdate(float dt)
{
	UpdateHawkerQueue(dt);

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
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Plate Selected");
			FlagCursorState(CursorState::Plate);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tongs"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Tongs Selected");
			FlagCursorState(CursorState::EmptyTongs);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_scizzors"))
	{
		if (e->on_click_)
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
			else if (!plate_on_tray && CheckCursorState(CursorState::Plate))
			{
				FlagPlateState(true);
				FlagAllCursorsFalse();
			}
			else if (plate_on_tray && current_order != CustomerOrder::Nothing)
			{
				plate_on_hand = true;
			}
		}
	}

	if (plate_on_hand)
	{
		Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_ = JZEngine::Camera::mouse_world_position_;
	}

	// give customer food
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_customer"))
	{
		if (e->on_click_)
		{
			if (InteractWithQueue(plate_on_hand, current_order))
			{
				if (plate_on_hand)
				{
					plate_on_hand = false;
					// make invisible all tray items
					FlagAllTrayItemsFalse();
					// place plate back on tray
					Scene().GetComponent<JZEngine::Transform>("tray_plate")->position_ = original_plate_position_;
				}
			}
			/*Customer& customer = *customers.begin();
			SetCustomerAnimation(customer.animation_pack_, AnimationStates::Ordering, customer.scene_object_id_);*/
		}
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