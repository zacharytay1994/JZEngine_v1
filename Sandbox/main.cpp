/*	__FILE HEADER__
*	File:		main.cpp
	Primary:	Zachary Tay
	Date:		12/08/21
	Brief:		Entry point to sandbox.
*/

#include <JZEngine.h>
#include "GameLogic/HawkerScene/HawkerScene.h"
#include "GameLogic/MainMenu/MainMenu.h"
#include "GameLogic/CutScene/CutScene.h"
#include "GameLogic/CutScene/FinalCreditCutScene.h"

#include <iostream>

struct CustomDataTest
{
	float a { 10 } , b;
};

void MoveRight ( float const& dt , JZEngine::EntityPacket& ep )
{
	/*CustomDataTest& cdt = Scene ().GetCustomComponent<CustomDataTest> ( ep );
	cdt.a += 5.0f * dt;*/
	Scene ().GetComponent<JZEngine::Transform> ( ep ).position_.x += 10.0f * dt;
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

		/*! SOON TO BE LEGACY CODE */
		Scene ().RegisterSceneInit ( "MainMenu" , "InitMainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "MainMenu" , "UpdateMainMenu" , UpdateMainMenu );

		/*Scene ().RegisterSceneInit ( "MainMenuS" , "InitMainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "MainMenuS" , "UpdateMainMenu" , UpdateMainMenu );

		Scene ().RegisterSceneInit ( "S_MainMenu2" , "InitMainMenu" , InitMainMenu );
		Scene ().RegisterSceneLogic ( "S_MainMenu2" , "UpdateMainMenu" , UpdateMainMenu );*/

		Scene ().RegisterSceneInit ( "HawkerScene" , "HawkerSceneInit" , HawkerSceneInit );
		Scene ().RegisterSceneLogic ( "HawkerScene" , "HawkerSceneUpdate" , HawkerSceneUpdate );

		/*Scene ().RegisterSceneInit ( "HawkerSceneS" , "HawkerSceneInit" , HawkerSceneInit );
		Scene ().RegisterSceneLogic ( "HawkerSceneS" , "HawkerSceneUpdate" , HawkerSceneUpdate );

		Scene ().RegisterSceneInit ( "Hawker_w_CoinLogic" , "HawkerSceneInit" , HawkerSceneInit );
		Scene ().RegisterSceneLogic ( "Hawker_w_CoinLogic" , "HawkerSceneUpdate" , HawkerSceneUpdate );*/

		Scene ().RegisterSceneInit ( "CutScene" , "CutSceneInit" , CutSceneInit );
		Scene ().RegisterSceneLogic ( "CutScene" , "CutSceneUpdate" , CutSceneUpdate );

		/*Scene ().RegisterSceneInit ( "CutSceneS" , "CutSceneInit" , CutSceneInit );
		Scene ().RegisterSceneLogic ( "CutSceneS" , "CutSceneUpdate" , CutSceneUpdate );*/

		Scene().RegisterSceneInit( "FinalCreditScene", "FinalCutSceneInit", FinalCutSceneInit );
		Scene().RegisterSceneLogic( "FinalCreditScene", "FinalCutSceneUpdate", FinalCutSceneUpdate );
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}