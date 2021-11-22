/*	__FILE HEADER__
*	File:		CutScene.h
	Primary:	Zachary Tay
	Date:		19/06/21
	Brief:		Cutscene logic.
*/

#pragma once

#include <JZEngine.h>
#include <string>
#include <sstream>
#include "../ButtonLogic.h"

enum class CutSceneState
{
	CutScene,
	Skip
};

enum class MessageState
{
	Nothing,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Eleven,
	Twelve,
	Thirteen
};

CutSceneState current_cut_scene_state = CutSceneState::CutScene;
MessageState message_state = MessageState::Nothing;
float message_out_of_the_screen{200.0f};
float message_move_up_max{190.0f};
float message_move_up_large{165.0f};
float message_move_up_medium{135.0f};
float message_move_up_small{-40.0f};
float text_leading{3.0f};

// relative position of the text in message box
float message_left_position_x { -130.0f }; //
float message_right_position_y{ -200.0f }; //


void Flag1stMsg(bool flag)
{
	// active/inactive 1st msg
	Scene().EntityFlagActive("1st_msg_bg", flag);
	Scene().EntityFlagActive("1st_msg_emoji", flag);
	Scene().EntityFlagActive("1st_msg_text", flag);
}

void Flag2ndMsg(bool flag)
{
	// active/inactive 2nd msg
	Scene().EntityFlagActive("2nd_msg_bg", flag);
	Scene().EntityFlagActive("2nd_msg_emoji", flag);
	Scene().EntityFlagActive("2nd_msg_text", flag);
}

void Flag3rdMsg(bool flag)
{
	// active/inactive 3rd msg
	Scene().EntityFlagActive("3rd_msg_bg", flag);
	Scene().EntityFlagActive("3rd_msg_emoji", flag);
	Scene().EntityFlagActive("3rd_msg_text", flag);
}

void Flag4thMsg(bool flag)
{
	// active/inactive 4th msg
	Scene().EntityFlagActive("4th_msg_bg", flag);
	Scene().EntityFlagActive("4th_msg_emoji", flag);
	Scene().EntityFlagActive("4th_msg_text", flag);
}

void Flag5thMsg(bool flag)
{
	// active/inactive 5th msg
	Scene().EntityFlagActive("5th_msg_bg", flag);
	Scene().EntityFlagActive("5th_msg_emoji", flag);
	Scene().EntityFlagActive("5th_msg_text", flag);
}

void Flag6thMsg(bool flag)
{
	// active/inactive 6th msg
	Scene().EntityFlagActive("6th_msg_bg", flag);
	Scene().EntityFlagActive("6th_msg_emoji", flag);
	Scene().EntityFlagActive("6th_msg_text", flag);
}

void Flag7thMsg(bool flag)
{
	// active/inactive 7th msg
	Scene().EntityFlagActive("7th_msg_bg", flag);
	Scene().EntityFlagActive("7th_msg_emoji", flag);
	Scene().EntityFlagActive("7th_msg_text", flag);
}

void Flag8thMsg(bool flag)
{
	// active/inactive 8th msg
	Scene().EntityFlagActive("8th_msg_bg", flag);
	Scene().EntityFlagActive("8th_msg_emoji", flag);
	Scene().EntityFlagActive("8th_msg_text", flag);
}

void Flag9thMsg(bool flag)
{
	// active/inactive 9th msg
	Scene().EntityFlagActive("9th_msg_bg", flag);
	Scene().EntityFlagActive("9th_msg_emoji", flag);
	Scene().EntityFlagActive("9th_msg_text", flag);
}

void Flag10thMsg(bool flag)
{
	// active/inactive 10th msg
	Scene().EntityFlagActive("10th_msg_bg", flag);
	Scene().EntityFlagActive("10th_msg_emoji", flag);
	Scene().EntityFlagActive("10th_msg_text", flag);
}

void Flag11thMsg(bool flag)
{
	// active/inactive 11th msg
	Scene().EntityFlagActive("11th_msg_bg", flag);
	Scene().EntityFlagActive("11th_msg_emoji", flag);
	Scene().EntityFlagActive("11th_msg_text", flag);
}

void Flag12thMsg(bool flag)
{
	// active/inactive 12th msg
	Scene().EntityFlagActive("12th_msg_bg", flag);
	Scene().EntityFlagActive("12th_msg_emoji", flag);
	Scene().EntityFlagActive("12th_msg_text", flag);
}

void Flag13thMsg(bool flag)
{
	// active/inactive 13th msg
	Scene().EntityFlagActive("13th_msg_bg", flag);
	Scene().EntityFlagActive("13th_msg_emoji", flag);
	Scene().EntityFlagActive("13th_msg_text", flag);
}

void CutSceneInit()
{
	current_cut_scene_state = CutSceneState::CutScene;
	message_state = MessageState::Nothing;
	Flag1stMsg(false);
	Flag2ndMsg(false);
	Flag3rdMsg(false);
	Flag4thMsg(false);
	Flag5thMsg(false);
	Flag6thMsg(false);
	Flag7thMsg(false);
	Flag8thMsg(false);
	Flag9thMsg(false);
	Flag10thMsg(false);
	Flag11thMsg(false);
	Flag12thMsg(false);
	Flag13thMsg(false);

	Scene().GetComponent<JZEngine::TextData>("1st_msg_text")->text = JZEngine::String("Baozi, are you still up?");
	Scene().GetComponent<JZEngine::TextData>("2nd_msg_text")->text = JZEngine::String("           Yea, what's up?");
	Scene().GetComponent<JZEngine::TextData>("2nd_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("3rd_msg_text")->text = JZEngine::String("I'm in the hospital.");
	Scene().GetComponent<JZEngine::TextData>("4th_msg_text")->text = 
	JZEngine::String ( "      WHAT! WHY? ARE\n                  YOU HURT?" ); 
	Scene().GetComponent<JZEngine::TextData>("4th_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("4th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("5th_msg_text")->text = 
	JZEngine::String("I slipped and fell at the\nhawker centre while\npreparing for the day.");
	Scene().GetComponent<JZEngine::TextData>("5th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("6th_msg_text")->text = 
	JZEngine::String("Oh dear...");
	Scene().GetComponent<JZEngine::TextData>("6th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("7th_msg_text")->text = 
	JZEngine::String("It seems like I may need\nto stay a few days in the\nhospital though.");
	Scene().GetComponent<JZEngine::TextData>("7th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("8th_msg_text")->text = 
	JZEngine::String("Baozi, can you help me\nrun the stall today?");
	Scene().GetComponent<JZEngine::TextData>("8th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("9th_msg_text")->text = 
	JZEngine::String ( "Ai yo... I told you to be\n                           careful!" );
	Scene().GetComponent<JZEngine::TextData>("9th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("9th_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("10th_msg_text")->text = 
	JZEngine::String ( "         Do I have to? I've\n  never done it before." );
	Scene().GetComponent<JZEngine::TextData>("10th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("10th_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("11th_msg_text")->text = 
	JZEngine::String("Well, it’s your school\nholiday. Help your dad\nout...");
	Scene().GetComponent<JZEngine::TextData>("11th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("12th_msg_text")->text = JZEngine::String("I will text you if you need\nguidance!");
	Scene().GetComponent<JZEngine::TextData>("12th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("13th_msg_text")->text = 
	JZEngine::String ( "   Okay okayyy. Let me\nsleep for an hour first." );
	Scene().GetComponent<JZEngine::TextData>("13th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("13th_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	
	JZEngine::Log::Info("Main", "Cut Scene Initialized.");
}

void CutSceneUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//if the mouse event phone app background exist
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Phone_app_bg"))
	{
		// Align the text for left pop up messages
		Scene ().GetComponent<JZEngine::Transform> ( "1st_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "3rd_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "5th_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "6th_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "7th_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "8th_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "11th_msg_text" )->child_position_.x = message_left_position_x; //
		Scene ().GetComponent<JZEngine::Transform> ( "12th_msg_text" )->child_position_.x = message_left_position_x; //
																												 
		// Align the text for right pop up messages
		Scene ().GetComponent<JZEngine::Transform> ( "2nd_msg_text" )->child_position_.x = message_right_position_y; //
		Scene ().GetComponent<JZEngine::Transform> ( "4th_msg_text" )->child_position_.x = message_right_position_y; //
		Scene ().GetComponent<JZEngine::Transform> ( "9th_msg_text" )->child_position_.x = message_right_position_y; //
		Scene ().GetComponent<JZEngine::Transform> ( "10th_msg_text" )->child_position_.x = message_right_position_y; //
		Scene ().GetComponent<JZEngine::Transform> ( "13th_msg_text" )->child_position_.x = message_right_position_y; //

		if (e->on_click_)
		{
			if (message_state == MessageState::Nothing)
			{
				//if nothing show the first message
				Flag1stMsg(true);
				message_state = MessageState::One;
			}
			else if (message_state == MessageState::One)
			{
				Flag2ndMsg(true);
				//shift up the message
				Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->position_.y = -80.0f;
				message_state = MessageState::Two;
			}
			else if (message_state == MessageState::Two)
			{
				Flag3rdMsg(true);
				Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->position_.y = 74.0f;
				Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y = -80.0f;
				message_state = MessageState::Three;
			}
			else if (message_state == MessageState::Three)
			{
				Flag4thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y = message_move_up_medium;
				Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y = message_move_up_small;
				Flag1stMsg(false);
				message_state = MessageState::Four;
			}
			else if (message_state == MessageState::Four)
			{
				Flag5thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->position_.y = 1.0f;
				Flag2ndMsg(false);
				message_state = MessageState::Five;
			}
			else if (message_state == MessageState::Five)
			{
				Flag6thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->position_.y = message_move_up_max;
				Scene().GetComponent<JZEngine::Transform>("5th_msg_bg")->position_.y = -10.0f;
				Flag3rdMsg(false);
				message_state = MessageState::Six;
			}
			else if (message_state == MessageState::Six)
			{
				Flag7thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("5th_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("6th_msg_bg")->position_.y = -35.0f;
				Flag4thMsg(false);
				message_state = MessageState::Seven;
			}
			else if (message_state == MessageState::Seven)
			{
				Flag8thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("5th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("6th_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("7th_msg_bg")->position_.y = -10.0f;
				Flag5thMsg(false);
				message_state = MessageState::Eight;
			}
			else if (message_state == MessageState::Eight)
			{
				Flag9thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("6th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("7th_msg_bg")->position_.y = 150.0f;
				Scene().GetComponent<JZEngine::Transform>("8th_msg_bg")->position_.y = -30.0f;
				Flag6thMsg(false);
				message_state = MessageState::Nine;
			}
			else if (message_state == MessageState::Nine)
			{
				Flag10thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("7th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("8th_msg_bg")->position_.y = message_move_up_medium;
				Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y = message_move_up_small;
				Flag7thMsg(false);
				message_state = MessageState::Ten;
			}
			else if (message_state == MessageState::Ten)
			{
				Flag11thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("8th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y = message_move_up_medium;
				Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y = message_move_up_small;
				Flag8thMsg(false);
				message_state = MessageState::Eleven;
			}
			else if (message_state == MessageState::Eleven)
			{
				Flag12thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("11th_msg_bg")->position_.y = 5.0f;
				Flag9thMsg(false);
				message_state = MessageState::Twelve;
			}
			else if (message_state == MessageState::Twelve)
			{
				Flag13thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("11th_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("12th_msg_bg")->position_.y = -10.0f;
				Flag10thMsg(false);
				message_state = MessageState::Thirteen;
			}
		}
		
	}

	//skip button
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("mouse_event_skip"))
	{
		if (e->on_released_)
		{
			Scene().ChangeScene("HawkerV2");
			current_cut_scene_state = CutSceneState::Skip;
		}
		if (e->on_held_)
		{
			ToggleButton("Skip", ButtonState::Clicked);
		}
		else if (e->on_hover_)
		{
			ToggleButton("Skip", ButtonState::Hover);
		}
		else
		{
			ToggleButton("Skip", ButtonState::Normal);
		}
	}
	
	
}
