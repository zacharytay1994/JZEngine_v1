#pragma once

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

void InitPhoneScreen()
{
	FlagPhone(false);
	FlagPhoneHomeScreen(false);
}

void UpdatePhoneScreen(float dt)
{
	FlagPhone(true);
	FlagPhoneHomeScreen(true);
}
