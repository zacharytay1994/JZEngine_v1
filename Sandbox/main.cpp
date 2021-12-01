#include <JZEngine.h>
#include "GameLogic/HawkerScene/HawkerScene.h"
#include "GameLogic/MainMenu/MainMenu.h"
#include "GameLogic/CutScene/CutScene.h"

#include <iostream>

struct CustomDataTest
{
	float a { 10 } , b;
};

void MoveRight ( float const& dt , JZEngine::EntityPacket& ep )
{
	CustomDataTest& cdt = Scene ().GetCustomComponent<CustomDataTest> ( ep );
	cdt.a += 5.0f * dt;
	Scene ().GetComponent<JZEngine::Transform> ( ep ).position_.x += (float)cdt.a * dt;
}

void MoveUp ( float const& dt , JZEngine::EntityPacket& ep )
{
	Scene ().GetComponent<JZEngine::Transform> ( ep ).position_.y += 10.0f * dt;
}

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

		Scene ().RegisterLogic ( "MoveRight" , MoveRight );
		Scene ().RegisterLogic ( "MoveUp" , MoveUp );
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}