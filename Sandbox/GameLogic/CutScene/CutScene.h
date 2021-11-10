#pragma once

#include "../ButtonLogic.h"

enum class CutSceneState
{
	CutScene,
	Skip
};

CutSceneState current_cut_scene_state = CutSceneState::CutScene;
bool Message1st{false};

void Flag1stMsg(bool flag)
{
	// active/inactive 1st msg
	Scene().EntityFlagActive("1st_msg_bg", flag);
	Scene().EntityFlagActive("1st_msg_emoji", flag);
	Scene().EntityFlagActive("1st_msg_text", flag);
}

void CutSceneInit()
{
	current_cut_scene_state = CutSceneState::CutScene;
	Flag1stMsg(false);
}
void CutSceneUpdate(float dt)
{

}
