#pragma once
#include <JZEngine.h>
#include "HawkerQueue.h"

void FlagAllCursorsFalse()
{
	Scene().EntityFlagActive("EmptyTongs", false);
	Scene().EntityFlagActive("TongsCarrotCake", false);
	Scene().EntityFlagActive("TongsDumpling", false);
	Scene().EntityFlagActive("TongsSeaweedChicken", false);
	Scene().EntityFlagActive("TongsSpringroll", false);
	Scene().EntityFlagActive("ScizzorsCursor", false);
	Scene().EntityFlagActive("PlateCursor", false);
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

bool has_tongs_{ false };
bool has_scizzors_{ false };

void ResetCursorFlags()
{
	has_tongs_ = false;
	has_scizzors_ = false;
}

void HawkerSceneInit()
{
	InitHawkerQueue();

	// initialize cursors
	ResetCursors();

	JZEngine::Log::Info("Main", "Hawker Scene Initialized.");
}

void HawkerSceneUpdate(float dt)
{
	UpdateHawkerQueue(dt);

	// process click inputs
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_springroll"))
	{
		if (e->on_click_ && has_tongs_)
		{
			JZEngine::Log::Info("Main", "SpringRoll Selected");
			ResetCursors();
			Scene().EntityFlagActive("TongsSpringroll", true);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_wanton"))
	{
		if (e->on_click_ && has_tongs_)
		{
			JZEngine::Log::Info("Main", "Wanton Selected");
			ResetCursors();
			Scene().EntityFlagActive("TongsDumpling", true);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_seaweedchicken"))
	{
		if (e->on_click_ && has_tongs_)
		{
			JZEngine::Log::Info("Main", "SeaweedChicken Selected");
			ResetCursors();
			Scene().EntityFlagActive("TongsSeaweedChicken", true);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_carrotcake"))
	{
		if (e->on_click_ && has_tongs_)
		{
			JZEngine::Log::Info("Main", "CarrotCake Selected");
			ResetCursors();
			Scene().EntityFlagActive("TongsCarrotCake", true);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_plate"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Plate Selected");
			ResetCursors();
			Scene().EntityFlagActive("PlateCursor", true);
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tongs"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Tongs Selected");
			ResetCursors();
			Scene().EntityFlagActive("EmptyTongs", true);
			ResetCursorFlags();
			has_tongs_ = true;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_scizzors"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Scizzors Selected");
			ResetCursors();
			Scene().EntityFlagActive("ScizzorsCursor", true);
			ResetCursorFlags();
			has_scizzors_ = true;
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_trashbin"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Trashbin Selected");
			ResetCursors();
			if (has_tongs_)
			{
				Scene().EntityFlagActive("EmptyTongs", true);
			}
			if (has_scizzors_)
			{
				Scene().EntityFlagActive("ScizzorsCursor", true);
			}
		}
	}
}