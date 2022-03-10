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
float message_move_up_small{-10.0f};
float message_move_up_tiny{-40.0f};
float text_leading{3.0f};
float bigger_box{ 10.0f };

// relative position of the text in message box
float message_left_position_x { -130.0f }; //
float message_right_position_y{ -200.0f }; //

// related to transition screen
bool transition_cutscene_hawker{ false };
bool transition_skip_pressed{ false };


void Flag1stMsg(bool flag)
{
	// active/inactive 1st msg
	Scene().EntityFlagActive("1st_msg_bg", flag);
	//Scene().EntityFlagActive("1st_msg_emoji", flag);
	//Scene().EntityFlagActive("1st_msg_text", flag);
}

void Flag2ndMsg(bool flag)
{
	// active/inactive 2nd msg
	Scene().EntityFlagActive("2nd_msg_bg", flag);
	//Scene().EntityFlagActive("2nd_msg_emoji", flag);
	//Scene().EntityFlagActive("2nd_msg_text", flag);
}

void Flag3rdMsg(bool flag)
{
	// active/inactive 3rd msg
	Scene().EntityFlagActive("3rd_msg_bg", flag);
	//Scene().EntityFlagActive("3rd_msg_emoji", flag);
	//Scene().EntityFlagActive("3rd_msg_text", flag);
}

void Flag4thMsg(bool flag)
{
	// active/inactive 4th msg
	Scene().EntityFlagActive("4th_msg_bg", flag);
	//Scene().EntityFlagActive("4th_msg_emoji", flag);
	//Scene().EntityFlagActive("4th_msg_text", flag);
}

void Flag5thMsg(bool flag)
{
	// active/inactive 5th msg
	Scene().EntityFlagActive("5th_msg_bg", flag);
	//Scene().EntityFlagActive("5th_msg_emoji", flag);
	//Scene().EntityFlagActive("5th_msg_text", flag);
}

void Flag6thMsg(bool flag)
{
	// active/inactive 6th msg
	Scene().EntityFlagActive("6th_msg_bg", flag);
	//Scene().EntityFlagActive("6th_msg_emoji", flag);
	//Scene().EntityFlagActive("6th_msg_text", flag);
}

void Flag7thMsg(bool flag)
{
	// active/inactive 7th msg
	Scene().EntityFlagActive("7th_msg_bg", flag);
	//Scene().EntityFlagActive("7th_msg_emoji", flag);
	//Scene().EntityFlagActive("7th_msg_text", flag);
}

void Flag8thMsg(bool flag)
{
	// active/inactive 8th msg
	Scene().EntityFlagActive("8th_msg_bg", flag);
	//Scene().EntityFlagActive("8th_msg_emoji", flag);
	//Scene().EntityFlagActive("8th_msg_text", flag);
}

void Flag9thMsg(bool flag)
{
	// active/inactive 9th msg
	Scene().EntityFlagActive("9th_msg_bg", flag);
	//Scene().EntityFlagActive("9th_msg_emoji", flag);
	//Scene().EntityFlagActive("9th_msg_text", flag);
}

void Flag10thMsg(bool flag)
{
	// active/inactive 10th msg
	Scene().EntityFlagActive("10th_msg_bg", flag);
	//Scene().EntityFlagActive("10th_msg_emoji", flag);
	//Scene().EntityFlagActive("10th_msg_text", flag);
}

void Flag11thMsg(bool flag)
{
	// active/inactive 11th msg
	Scene().EntityFlagActive("11th_msg_bg", flag);
	//Scene().EntityFlagActive("11th_msg_emoji", flag);
	//Scene().EntityFlagActive("11th_msg_text", flag);
}

void Flag12thMsg(bool flag)
{
	// active/inactive 12th msg
	Scene().EntityFlagActive("12th_msg_bg", flag);
	//Scene().EntityFlagActive("12th_msg_emoji", flag);
	//Scene().EntityFlagActive("12th_msg_text", flag);
}

void Flag13thMsg(bool flag)
{
	// active/inactive 13th msg
	Scene().EntityFlagActive("13th_msg_bg", flag);
	//Scene().EntityFlagActive("13th_msg_emoji", flag);
	//Scene().EntityFlagActive("13th_msg_text", flag);
}

void FlagAllScreenItems ( bool flag )
{

	Flag1stMsg ( flag );
	Flag2ndMsg ( flag );
	Flag3rdMsg ( flag );
	Flag4thMsg ( flag );
	Flag5thMsg ( flag );
	Flag6thMsg ( flag );
	Flag7thMsg ( flag );
	Flag8thMsg ( flag );
	Flag9thMsg ( flag );
	Flag10thMsg ( flag );
	Flag11thMsg ( flag );
	Flag12thMsg ( flag );
	Flag13thMsg ( flag );

	Scene ().EntityFlagActive ( "1st_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "1st_msg_text" , flag );
	Scene ().EntityFlagActive ( "2nd_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "2nd_msg_text" , flag );
	Scene ().EntityFlagActive ( "3rd_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "3rd_msg_text" , flag );
	Scene ().EntityFlagActive ( "4th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "4th_msg_text" , flag );
	Scene ().EntityFlagActive ( "5th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "5th_msg_text" , flag );
	Scene ().EntityFlagActive ( "6th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "6th_msg_text" , flag );
	Scene ().EntityFlagActive ( "7th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "7th_msg_text" , flag );
	Scene ().EntityFlagActive ( "8th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "8th_msg_text" , flag );
	Scene ().EntityFlagActive ( "9th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "9th_msg_text" , flag );
	Scene ().EntityFlagActive ( "10th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "10th_msg_text" , flag );
	Scene ().EntityFlagActive ( "11th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "11th_msg_text" , flag );
	Scene ().EntityFlagActive ( "12th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "12th_msg_text" , flag );
	Scene ().EntityFlagActive ( "13th_msg_emoji" , flag );
	Scene ().EntityFlagActive ( "13th_msg_text" , flag );
}

void CutSceneInit()
{
	current_cut_scene_state = CutSceneState::CutScene;
	message_state = MessageState::Nothing;
	
	FlagAllScreenItems ( false );

	//Scene().GetComponent<JZEngine::TextData>("1st_msg_text")->text = JZEngine::String("Baozi, are you still up?");
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
	JZEngine::String("Well, it�s your school\nholiday. Help your dad\nout...");
	Scene().GetComponent<JZEngine::TextData>("11th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("12th_msg_text")->text = JZEngine::String("I will text you if you need\nguidance!");
	Scene().GetComponent<JZEngine::TextData>("12th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("13th_msg_text")->text = 
	JZEngine::String ( "   Okay okayyy. Let me\nsleep for an hour first." );
	Scene().GetComponent<JZEngine::TextData>("13th_msg_text")->leading_y_ = text_leading;
	Scene().GetComponent<JZEngine::TextData>("13th_msg_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	
	JZEngine::Log::Info("Main", "Cut Scene Initialized.");


	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black_1" )->tint.w = 1.0f;
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black_2" )->tint.w = 1.0f;
	Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black_3" )->tint.w = 0.0f;

	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("1st_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("2nd_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("3rd_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("4th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("5th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("6th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("7th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("8th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("9th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("10th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("11th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("12th_msg_bg")->active_flag = true;
	Scene().GetComponent<JZEngine::AnimatedTransformComponent>("13th_msg_bg")->active_flag = true;
	//Scene().GetComponent<JZEngine::AnimatedTransformComponent>("1st_msg_emoji")->active_flag = true;

	Scene ().PlaySound ( "temp_phone_notification" , false );
}

void CutSceneUpdate(float dt)
{
	float TransitionSpeed = dt * 0.4f;
	float phone_light_up_speed = dt * 5.0f;
	float darken_speed = dt * 2.0f;

	float& TransitionBlack2 = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black_2" )->tint.w;
	float& TransitionBlack1 = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black_1" )->tint.w;

	if ( !transition_cutscene_hawker )
	{
		if ( TransitionBlack2 > 0.0f )
		{
			TransitionBlack2 -= phone_light_up_speed;
		}
		else
		{
			TransitionBlack2 = 0.0f;
		}

		if ( TransitionBlack1 > 0.0f )
		{
			TransitionBlack1 -= TransitionSpeed;
		}
		else
		{
			TransitionBlack1 = 0.0f;
		}
	}
	

	if (JZEngine::InputHandler::IsMouseTriggered(JZEngine::MOUSE::MOUSE_BUTTON_1))
		Scene().PlaySound("click", false);

	////Text animation
	//if (Scene().GetComponent<JZEngine::TextData>("1st_msg_text")->font_size_ < 1.2f)
	//{
	//	Scene().GetComponent<JZEngine::TextData>("1st_msg_text")->font_size_ += 0.12 * dt;
	//}


	//Extra section for splitting box and the text and emoji out
	if (Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("1st_msg_emoji", true);
		Scene().EntityFlagActive("1st_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("1st_msg_emoji", false);
		Scene().EntityFlagActive("1st_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("2nd_msg_emoji", true);
		Scene().EntityFlagActive("2nd_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("2nd_msg_emoji", false);
		Scene().EntityFlagActive("2nd_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("3rd_msg_emoji", true);
		Scene().EntityFlagActive("3rd_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("3rd_msg_emoji", false);
		Scene().EntityFlagActive("3rd_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("4th_msg_emoji", true);
		Scene().EntityFlagActive("4th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("4th_msg_emoji", false);
		Scene().EntityFlagActive("4th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("5th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("5th_msg_emoji", true);
		Scene().EntityFlagActive("5th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("5th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("5th_msg_emoji", false);
		Scene().EntityFlagActive("5th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("6th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("6th_msg_emoji", true);
		Scene().EntityFlagActive("6th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("6th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("6th_msg_emoji", false);
		Scene().EntityFlagActive("6th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("7th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("7th_msg_emoji", true);
		Scene().EntityFlagActive("7th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("7th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("7th_msg_emoji", false);
		Scene().EntityFlagActive("7th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("8th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("8th_msg_emoji", true);
		Scene().EntityFlagActive("8th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("8th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("8th_msg_emoji", false);
		Scene().EntityFlagActive("8th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("9th_msg_emoji", true);
		Scene().EntityFlagActive("9th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("9th_msg_emoji", false);
		Scene().EntityFlagActive("9th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("10th_msg_emoji", true);
		Scene().EntityFlagActive("10th_msg_text", true);
	}
	if (Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y == message_out_of_the_screen)
	{
		Scene().EntityFlagActive("10th_msg_emoji", false);
		Scene().EntityFlagActive("10th_msg_text", false);
	}

	if (Scene().GetComponent<JZEngine::Transform>("11th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("11th_msg_emoji", true);
		Scene().EntityFlagActive("11th_msg_text", true);
	}
	
	if (Scene().GetComponent<JZEngine::Transform>("12th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("12th_msg_emoji", true);
		Scene().EntityFlagActive("12th_msg_text", true);
	}

	if (Scene().GetComponent<JZEngine::Transform>("13th_msg_bg")->scale_.x > bigger_box)
	{
		Scene().EntityFlagActive("13th_msg_emoji", true);
		Scene().EntityFlagActive("13th_msg_text", true);
	}

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
				Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->position_.y = 90.0f;
				Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y = -80.0f;
				message_state = MessageState::Three;
			}
			else if (message_state == MessageState::Three)
			{
				Flag4thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("1st_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y = message_move_up_medium;
				Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y = message_move_up_tiny;
				Flag1stMsg(false);
				message_state = MessageState::Four;
			}
			else if (message_state == MessageState::Four)
			{
				Flag5thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("2nd_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->position_.y = message_move_up_small;
				Flag2ndMsg(false);
				message_state = MessageState::Five;
			}
			else if (message_state == MessageState::Five)
			{
				Flag6thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("3rd_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("4th_msg_bg")->position_.y = message_move_up_max;
				Scene().GetComponent<JZEngine::Transform>("5th_msg_bg")->position_.y = message_move_up_small;
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
				Scene().GetComponent<JZEngine::Transform>("7th_msg_bg")->position_.y = message_move_up_small;
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
				Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y = message_move_up_tiny;
				Flag7thMsg(false);
				message_state = MessageState::Ten;
			}
			else if (message_state == MessageState::Ten)
			{
				Flag11thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("8th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y = message_move_up_medium;
				Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y = message_move_up_tiny;
				Flag8thMsg(false);
				message_state = MessageState::Eleven;
			}
			else if (message_state == MessageState::Eleven)
			{
				Flag12thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("9th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("11th_msg_bg")->position_.y = -4.0f;
				Flag9thMsg(false);
				message_state = MessageState::Twelve;
			}
			else if (message_state == MessageState::Twelve)
			{
				Flag13thMsg(true);
				Scene().GetComponent<JZEngine::Transform>("10th_msg_bg")->position_.y = message_out_of_the_screen;
				Scene().GetComponent<JZEngine::Transform>("11th_msg_bg")->position_.y = message_move_up_large;
				Scene().GetComponent<JZEngine::Transform>("12th_msg_bg")->position_.y = message_move_up_small;
				Flag10thMsg(false);
				message_state = MessageState::Thirteen;
			}
			else if (message_state == MessageState::Thirteen)
			{
				// apply black transition screen
				transition_cutscene_hawker = true;
			}
		}
		
	}

	//skip button
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("mouse_event_skip"))
	{
		if (e->on_released_)
		{
			//Scene().ChangeScene("HawkerScene");
			//current_cut_scene_state = CutSceneState::Skip;

			transition_cutscene_hawker = true;
			transition_skip_pressed = true;
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

	if( transition_cutscene_hawker )
	{
		FlagAllScreenItems ( false );

		float& TransitionBlack3 = Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Transition_Black_3" )->tint.w;

		if ( TransitionBlack2 < 1.0f )
		{
			TransitionBlack2 += phone_light_up_speed;
		}
		else if ( TransitionBlack3 < 1.0f )
		{
			TransitionBlack3 += darken_speed;
		}
		else
		{
			Scene ().ChangeScene ( "HawkerScene" );
			if( transition_skip_pressed )
			{
				current_cut_scene_state = CutSceneState::Skip;
			}
			transition_cutscene_hawker = false;
		}
	}
	
	
}
