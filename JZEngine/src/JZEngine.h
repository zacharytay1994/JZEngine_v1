/*	__FILE HEADER__
*	File:		JZEngine.h
	Primary:	JZ
	Date:		01/07/21
	Brief:		dll interface.
*/

#pragma once

#include "JZEngine/Application.h"
#include "JZEngine/DebugTools/Log.h"
#include "JZEngine/SceneLogic/SceneLogic.h"
#include "JZEngine/ECS/ECSConfig.h"

//---Entry Point------------------
#include "JZEngine/EntryPoint.h"
#include "JZEngine/Math/Vec2.h"
#include "JZEngine/Math/Vec3.h"
#include "JZEngine/Math/Timer.h"
#include "JZEngine/EntryPoint.h"

#include "JZEngine/Sound/Sound.h"

// shortcuts
JZEngine::SceneLogic& Scene()
{
	return JZEngine::SceneLogic::Instance();
}
