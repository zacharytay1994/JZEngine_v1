/*	__FILE HEADER__
*	File:		HawkerApp.h
	Primary:	Yu Ching Yin
	Date:		05/12/21
	Brief:		Apps logic.
*/

#pragma once

enum class HawkerAppState
{
	MainScreen,
	Theresapp,
	Album,
	HowtoPlay
};

HawkerAppState current_app_state = HawkerAppState::MainScreen;

float hp_text_leading{ 3.0f };
float scrolling_speed{ 20.0f };
float top_boundary{ 280.0f };
float bottom_boundary{ -375.0f };
float top_line{ 220.0f };
float bottom_line{ -340.0f };
float upper_bound{ 270.0f };
bool scroll_up{ false };
bool scroll_down{ false };
int album_black_bg_layer{ 0 };
int add_layer{ 7 };
bool paused{ false };
//bool esc_again{ false };

void FlagPhone(bool flag)
{
	Scene().EntityFlagActive("Phone_black_bg", flag);
	Scene().EntityFlagActive("Phone_outercase", flag);
	Scene().EntityFlagActive("Phone_battery", flag);
	Scene().EntityFlagActive("Phone_time", flag);
}

void FlagPhoneHomeScreen(bool flag)
{
	Scene().EntityFlagActive("Phone_main_screen", flag);
	Scene().EntityFlagActive("Theresapp", flag);
	Scene().EntityFlagActive("Album", flag);
	Scene().EntityFlagActive("Shop", flag);
	Scene().EntityFlagActive("How_to_Play_app", flag);
	Scene().EntityFlagActive("Main_Menu_app", flag);
	Scene().EntityFlagActive("Resume", flag);
	Scene().EntityFlagActive("Restart", flag);
	Scene().EntityFlagActive("Options", flag);
	Scene().EntityFlagActive("Exit", flag);
}

void FlagTheresappScreen(bool flag)
{
	Scene().EntityFlagActive("Phone_blacker_bg", flag);
	Scene().EntityFlagActive("Theresapp_main_screen", flag);
	Scene().EntityFlagActive("Theresapp_Dad_chat", flag);
	Scene().EntityFlagActive("Theresapp_back_arrow", flag);
}

void FlagAlbumScreen(bool flag)
{
	Scene().EntityFlagActive("Album_blacker_bg", flag);
	Scene().EntityFlagActive("Album_main_screen", flag);
	Scene().EntityFlagActive("Album_top", flag);
	Scene().EntityFlagActive("Album_time", flag);
	Scene().EntityFlagActive("Album_battery", flag);
	Scene().EntityFlagActive("Album_text", flag);
	Scene().EntityFlagActive("Album_back_arrow", flag);
	Scene().EntityFlagActive("Album_photo_2021s", flag);
	Scene().EntityFlagActive("black_cover_2021s", flag);
	Scene().EntityFlagActive("text_2021s", flag);
	Scene().EntityFlagActive("Album_photo_1980s", flag);
	Scene().EntityFlagActive("black_cover_1980s", flag);
	Scene().EntityFlagActive("text_1980s", flag);
	Scene().EntityFlagActive("Album_photo_1960s", flag);
	Scene().EntityFlagActive("black_cover_1960s", flag);
	Scene().EntityFlagActive("text_1960s", flag);
}

void FlagHowtoPlayScreen(bool flag)
{
	Scene().EntityFlagActive("How_to_Play_photo", flag);
	Scene().EntityFlagActive("How_to_Play_text", flag);
	Scene().EntityFlagActive("How_to_Play_x", flag);
}

void FlagMsg1(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_1_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_1_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_1_text", flag);
}

void FlagMsg2(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_2_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_2_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_2_text", flag);
}

void FlagMsg3(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_3_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_3_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_3_text", flag);
}

void FlagMsg4(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_4_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_4_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_4_text", flag);
}

void FlagMsg5(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_5_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_5_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_5_text", flag);
}

void FlagMsg6(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_6_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_6_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_6_text", flag);
}

void FlagMsg7(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_7_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_7_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_7_text", flag);
}

void FlagMsg8(bool flag)
{
	Scene().EntityFlagActive("First_page_msg_8_bg", flag);
	Scene().EntityFlagActive("First_page_msg_8_emoji", flag);
	Scene().EntityFlagActive("First_page_msg_8_text", flag);
}

void FlagMsg9(bool flag)
{
	Scene().EntityFlagActive("First_page_msg_9_bg", flag);
	Scene().EntityFlagActive("First_page_msg_9_emoji", flag);
	Scene().EntityFlagActive("First_page_msg_9_text", flag);
}

void FlagMsg10(bool flag)
{
	Scene().EntityFlagActive("First_page_msg_10_bg", flag);
	Scene().EntityFlagActive("First_page_msg_10_emoji", flag);
	Scene().EntityFlagActive("First_page_msg_10_text", flag);
}

void FlagMsg11(bool flag)
{
	Scene().EntityFlagActive("First_page_msg_11_bg", flag);
	Scene().EntityFlagActive("First_page_msg_11_emoji", flag);
	Scene().EntityFlagActive("First_page_msg_11_text", flag);
}

void FlagMsg12(bool flag)
{
	Scene().EntityFlagActive("First_page_msg_12_bg", flag);
	Scene().EntityFlagActive("First_page_msg_12_emoji", flag);
	Scene().EntityFlagActive("First_page_msg_12_text", flag);
}

void FlagMsg13(bool flag)
{
	Scene().EntityFlagActive("First_page_msg_13_bg", flag);
	Scene().EntityFlagActive("First_page_msg_13_emoji", flag);
	Scene().EntityFlagActive("First_page_msg_13_text", flag);
}

void InitPhoneScreen()
{
	current_app_state = HawkerAppState::MainScreen;

	FlagPhone(false);
	FlagPhoneHomeScreen(false);
	FlagTheresappScreen(false);
	FlagAlbumScreen(false);
	FlagHowtoPlayScreen(false);
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
	Scene().EntityFlagActive("Album_1960_big_photo", false);
	Scene().EntityFlagActive("Album_1960_big_photo_quit", false);
	Scene().EntityFlagActive("Album_1980_big_photo", false);
	Scene().EntityFlagActive("Album_1980_big_photo_quit", false);
	Scene().EntityFlagActive("Album_2021_big_photo", false);
	Scene().EntityFlagActive("Album_2021_big_photo_quit", false);

	album_black_bg_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_;

	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_1_text")->text =
	JZEngine::String("   Okay okayyy. Let me\nsleep for an hour first.");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_1_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_1_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_2_text")->text = 
	JZEngine::String("I will text you if you need\nguidance!");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_2_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_3_text")->text =
	JZEngine::String("Well, it�s your school\nholiday. Help your dad\nout...");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_3_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_4_text")->text =
	JZEngine::String("         Do I have to? I've\n  never done it before.");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_4_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_4_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_5_text")->text =
	JZEngine::String("Ai yo... I told you to be\n                           careful!");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_5_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_5_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_6_text")->text =
	JZEngine::String("Baozi, can you help me\nrun the stall today?");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_6_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_7_text")->text =
	JZEngine::String("It seems like I may need\nto stay a few days in the\nhospital though.");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_7_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_8_text")->text =
	JZEngine::String("Oh dear...");
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_8_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_9_text")->text =
	JZEngine::String("I slipped and fell at the\nhawker centre while\npreparing for the day.");
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_9_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_10_text")->text =
	JZEngine::String("      WHAT! WHY? ARE\n                  YOU HURT?");
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_10_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_10_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_11_text")->text = JZEngine::String("I'm in the hospital.");
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_12_text")->text = JZEngine::String("           Yea, what's up?");
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_12_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("First_page_msg_13_text")->text = JZEngine::String("Baozi, are you still up?");

	Scene().GetComponent<JZEngine::TextData>("Album_text")->text = JZEngine::String("My Albums");
	Scene().GetComponent<JZEngine::TextData>("text_2021s")->text = JZEngine::String("2021s");
	Scene().GetComponent<JZEngine::TextData>("text_2021s")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("text_1980s")->text = JZEngine::String("1980s");
	Scene().GetComponent<JZEngine::TextData>("text_1980s")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("text_1960s")->text = JZEngine::String("1960s");
	Scene().GetComponent<JZEngine::TextData>("text_1960s")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);

	Scene().GetComponent<JZEngine::TextData>("How_to_Play_text")->text = JZEngine::String("HOW TO PLAY");
	Scene().GetComponent<JZEngine::TextData>("How_to_Play_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
}

void UpdatePhoneScreen(float dt)
{
	FlagPhone(true);
	FlagPhoneHomeScreen(true);

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Theresapp"))
	{
		if (e->on_click_)
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
			current_app_state = HawkerAppState::Theresapp;
			std::cout << "enter!\n";
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Phone_battery", false);
			Scene().EntityFlagActive("Phone_time", false);
			FlagPhoneHomeScreen(false);
			FlagAlbumScreen(true);
			current_app_state = HawkerAppState::Album;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("How_to_Play_app"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Phone_outercase", false);
			Scene().EntityFlagActive("Phone_battery", false);
			Scene().EntityFlagActive("Phone_time", false);
			FlagPhoneHomeScreen(false);
			FlagHowtoPlayScreen(true);
			current_app_state = HawkerAppState::HowtoPlay;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Main_Menu_app"))
	{
		if (e->on_click_)
		{
			Scene().ChangeScene("MainMenu");
		}
	}
	if (paused == true && JZEngine::InputHandler::IsKeyReleased(JZEngine::KEY::KEY_ESCAPE))
	{
		FlagPhone(false);
		FlagPhoneHomeScreen(false);
		Scene().EntityFlagActive("PhoneOptions", true);
		paused = false;
		//esc_again = false;
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Restart"))
	{
		if (e->on_click_)
		{
			Scene().ChangeScene("HawkerV2");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Exit"))
	{
		if (e->on_click_)
		{
			//Scene().ChangeScene("MainMenu");
		}
	}

}

void UpdateTheresapp(float dt)
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

	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_.y > bottom_line ||
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_.y < top_line)
	{
		scroll_up = true;
	}
	else
	{
		scroll_up = false;
	}

	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y > upper_bound)
	{
		scroll_down = true;
	}
	else
	{
		scroll_down = false;
	}

	if (scroll_down == true && JZEngine::InputHandler::IsKeyPressed(JZEngine::KEY::KEY_M) && JZEngine::InputHandler::mouse_scrolled_ == -1)
	{
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_2_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_3_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_4_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_5_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_6_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_8_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_9_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_10_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_11_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_12_bg")->position_.y -= scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y -= scrolling_speed;
	}
	else if (scroll_up == true && JZEngine::InputHandler::IsKeyPressed(JZEngine::KEY::KEY_M) && JZEngine::InputHandler::mouse_scrolled_ == 1)
	{
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_2_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_3_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_4_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_5_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_6_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("Last_page_msg_7_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_8_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_9_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_10_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_11_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_12_bg")->position_.y += scrolling_speed;
		Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y += scrolling_speed;
	}


	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_1_bg")->position_.y < bottom_boundary)
	{
		FlagMsg1(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_2_bg")->position_.y < bottom_boundary)
	{
		FlagMsg2(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_3_bg")->position_.y < bottom_boundary)
	{
		FlagMsg3(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_4_bg")->position_.y < bottom_boundary)
	{
		FlagMsg4(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_5_bg")->position_.y < bottom_boundary)
	{
		FlagMsg5(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("Last_page_msg_6_bg")->position_.y < bottom_boundary)
	{
		FlagMsg6(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_8_bg")->position_.y > top_boundary)
	{
		FlagMsg8(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_9_bg")->position_.y > top_boundary)
	{
		FlagMsg9(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_10_bg")->position_.y > top_boundary)
	{
		FlagMsg10(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_11_bg")->position_.y > top_boundary)
	{
		FlagMsg11(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_12_bg")->position_.y > top_boundary)
	{
		FlagMsg12(false);
	}
	if (Scene().GetComponent<JZEngine::Transform>("First_page_msg_13_bg")->position_.y > top_boundary)
	{
		FlagMsg13(false);
	}

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Theresapp_back_arrow"))
	{
		if (e->on_click_)
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

			current_app_state = HawkerAppState::MainScreen;
			std::cout << "back button!\n";
		}
	}
}

void UpdateAlbum(float dt)
{
	Scene().EntityFlagActive("Phone_battery", false);
	Scene().EntityFlagActive("Phone_time", false);
	FlagPhoneHomeScreen(false);
	FlagAlbumScreen(true);

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_photo_1960s"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Album_1960_big_photo", true);
			Scene().EntityFlagActive("Album_1960_big_photo_quit", true);
			Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_ = album_black_bg_layer + add_layer;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_1960_big_photo_quit"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Album_1960_big_photo", false);
			Scene().EntityFlagActive("Album_1960_big_photo_quit", false);
			Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_ = album_black_bg_layer;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_photo_1980s"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Album_1980_big_photo", true);
			Scene().EntityFlagActive("Album_1980_big_photo_quit", true);
			Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_ = album_black_bg_layer + add_layer;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_1980_big_photo_quit"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Album_1980_big_photo", false);
			Scene().EntityFlagActive("Album_1980_big_photo_quit", false);
			Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_ = album_black_bg_layer;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_photo_2021s"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Album_2021_big_photo", true);
			Scene().EntityFlagActive("Album_2021_big_photo_quit", true);
			Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_ = album_black_bg_layer + add_layer;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_2021_big_photo_quit"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Album_2021_big_photo", false);
			Scene().EntityFlagActive("Album_2021_big_photo_quit", false);
			Scene().GetComponent<JZEngine::SpriteLayer>("Album_blacker_bg")->layer_ = album_black_bg_layer;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("Album_back_arrow"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Phone_battery", true);
			Scene().EntityFlagActive("Phone_time", true);
			FlagPhoneHomeScreen(true);
			FlagAlbumScreen(false);

			current_app_state = HawkerAppState::MainScreen;
		}
	}
}

void UpdateHowtoPlay(float dt)
{
	Scene().EntityFlagActive("Phone_outercase", false);
	Scene().EntityFlagActive("Phone_battery", false);
	Scene().EntityFlagActive("Phone_time", false);
	FlagPhoneHomeScreen(false);
	FlagHowtoPlayScreen(true);

	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("How_to_Play_x"))
	{
		if (e->on_click_)
		{
			Scene().EntityFlagActive("Phone_outercase", true);
			Scene().EntityFlagActive("Phone_battery", true);
			Scene().EntityFlagActive("Phone_time", true);
			FlagPhoneHomeScreen(true);
			FlagHowtoPlayScreen(false);

			current_app_state = HawkerAppState::MainScreen;
		}
	}
}

void UpdateHomeScreen(float dt)
{
	switch (current_app_state)
	{
	case HawkerAppState::MainScreen:
		UpdatePhoneScreen(dt);
		break;
	case HawkerAppState::Theresapp:
		UpdateTheresapp(dt);
		break;
	case HawkerAppState::Album:
		UpdateAlbum(dt);
		break;
	case HawkerAppState::HowtoPlay:
		UpdateHowtoPlay(dt);
		break;
	}
}