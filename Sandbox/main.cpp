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
		Scene ().RegisterSceneLogic ( "InitMainMenu" , InitMainMenu, "UpdateMainMenu", UpdateMainMenu );
		Scene ().RegisterSceneLogic ( "HawkerSceneInit" , HawkerSceneInit , "HawkerSceneUpdate" , HawkerSceneUpdate );
		Scene ().RegisterSceneLogic ( "CutSceneInit" , CutSceneInit , "CutSceneUpdate" , CutSceneUpdate );

		Scene ().RegisterLogic ( "MoveRight" , MoveRight );
		Scene ().RegisterLogic ( "MoveUp" , MoveUp );

		/*! LEGACY CODE */
		Scene ().RegisterSceneInit ( "MainMenu" , "InitMainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "MainMenu" , "UpdateMainMenu" , UpdateMainMenu );

		Scene ().RegisterSceneInit ( "S_MainMenu" , "InitMainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "S_MainMenu" , "UpdateMainMenu" , UpdateMainMenu );

		Scene ().RegisterSceneInit ( "S_MainMenu2" , "InitMainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "S_MainMenu2" , "UpdateMainMenu" , UpdateMainMenu );

		Scene ().RegisterSceneInit ( "HawkerV2" , "HawkerSceneInit" , HawkerSceneInit );
		Scene ().RegisterSceneLogic ( "HawkerV2" , "HawkerSceneUpdate" , HawkerSceneUpdate );

		Scene ().RegisterSceneInit ( "Hawker_w_CoinLogic" , "HawkerSceneInit" , HawkerSceneInit );
		Scene ().RegisterSceneLogic ( "Hawker_w_CoinLogic" , "HawkerSceneUpdate" , HawkerSceneUpdate );

		Scene ().RegisterSceneInit ( "CutScene" , "CutSceneInit" , CutSceneInit );
		Scene ().RegisterSceneLogic ( "CutScene" , "CutSceneUpdate" , CutSceneUpdate );

		Scene ().RegisterSceneInit ( "S_Cutscene" , "CutSceneInit" , CutSceneInit );
		Scene ().RegisterSceneLogic ( "S_Cutscene" , "CutSceneUpdate" , CutSceneUpdate );
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}