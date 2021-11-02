#pragma once
#include <JZEngine.h>
#include "HawkerQueue.h"

void HawkerSceneInit()
{
	InitHawkerQueue();
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
			JZEngine::Log::Info("Main", "SpringRoll Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_wanton"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Wanton Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_seaweedchicken"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "SeaweedChicken Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_carrotcake"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "CarrotCake Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_plate"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Plate Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_tongs"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Tongs Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_scizzors"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Scizzors Selected");
		}
	}
	if (JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>("bb_trashbin"))
	{
		if (e->on_click_)
		{
			JZEngine::Log::Info("Main", "Trashbin Selected");
		}
	}
}