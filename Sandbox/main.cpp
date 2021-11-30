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

		Scene ().RegisterSceneInit ( "S_MainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "S_MainMenu" , UpdateMainMenu );

		Scene ().RegisterSceneInit ( "S_MainMenu2" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "S_MainMenu2" , UpdateMainMenu );
		
		Scene().RegisterSceneInit("HawkerV2", HawkerSceneInit);
		Scene().RegisterSceneLogic("HawkerV2", HawkerSceneUpdate);

		Scene().RegisterSceneInit("CutScene", CutSceneInit);
		Scene().RegisterSceneLogic("CutScene", CutSceneUpdate);

		Scene ().RegisterSceneInit ( "S_Cutscene" , CutSceneInit );
		Scene ().RegisterSceneLogic ( "S_Cutscene" , CutSceneUpdate );
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}