#include <JZEngine.h>
#include "GameLogic/HawkerScene/HawkerScene.h"
#include "GameLogic/MainMenu/MainMenu.h"
#include "GameLogic/CutScene/CutScene.h"

#include <iostream>

class Sandbox : public JZEngine::Application
{
public:
	Sandbox ()
		:
		Application ()
	{
		
		Scene().RegisterSceneInit("MainMenu", InitMainMenu);
		Scene().RegisterSceneLogic("MainMenu", UpdateMainMenu);
		
		Scene().RegisterSceneInit("HawkerV2", HawkerSceneInit);
		Scene().RegisterSceneLogic("HawkerV2", HawkerSceneUpdate);

		Scene().RegisterSceneInit("CutScene", CutSceneInit);
		Scene().RegisterSceneLogic("CutScene", CutSceneUpdate);
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}