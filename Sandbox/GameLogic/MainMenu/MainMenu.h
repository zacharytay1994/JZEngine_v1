#pragma once
#include <JZEngine.h>

void TogglePlayButtonHover(bool flag)
{
	Scene().EntityFlagActive("Play", !flag);
	Scene().EntityFlagActive("PlayHighlight", flag);
}

void InitMainMenu()
{
	
}

void UpdateMainMenu(float dt)
{
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_play"))
	{
		// if tray was clicked and plate has nothing on it

		TogglePlayButtonHover(e->on_hover_);

		if (e->on_click_)
		{
			Scene().ChangeScene("HawkerV2");
		}
	}
}