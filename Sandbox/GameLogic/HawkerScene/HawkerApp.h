#pragma once

float hp_text_leading{ 3.0f };

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

void FlagLastPageMsg(bool flag)
{
	Scene().EntityFlagActive("Last_page_msg_1_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_1_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_1_text", flag);
	Scene().EntityFlagActive("Last_page_msg_2_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_2_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_2_text", flag);
	Scene().EntityFlagActive("Last_page_msg_3_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_3_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_3_text", flag);
	Scene().EntityFlagActive("Last_page_msg_4_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_4_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_4_text", flag);
	Scene().EntityFlagActive("Last_page_msg_5_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_5_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_5_text", flag);
	Scene().EntityFlagActive("Last_page_msg_6_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_6_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_6_text", flag);
	Scene().EntityFlagActive("Last_page_msg_7_bg", flag);
	Scene().EntityFlagActive("Last_page_msg_7_emoji", flag);
	Scene().EntityFlagActive("Last_page_msg_7_text", flag);
}

void InitPhoneScreen()
{
	FlagPhone(false);
	FlagPhoneHomeScreen(false);
	FlagTheresappScreen(false);
	FlagLastPageMsg(false);

	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_1_text")->text =
	JZEngine::String("   Okay okayyy. Let me\nsleep for an hour first.");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_1_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_1_text")->color_ = JZEngine::Vec3f(255.0f, 255.0f, 255.0f);
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_2_text")->text = 
	JZEngine::String("I will text you if you need\nguidance!");
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_2_text")->leading_y_ = hp_text_leading;
	Scene().GetComponent<JZEngine::TextData>("Last_page_msg_3_text")->text =
	JZEngine::String("Well, it’s your school\nholiday. Help your dad\nout...");
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
			FlagLastPageMsg(true);
		}
	}
}
