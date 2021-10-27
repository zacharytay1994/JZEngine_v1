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
}