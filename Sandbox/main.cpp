#include <JZEngine.h>
#include "GameLogic/HawkerScene/HawkerScene.h"

#include <iostream>

class Sandbox : public JZEngine::Application
{
public:
	Sandbox ()
		:
		Application ()
	{
		Scene().RegisterSceneInit("NewHawkerScene", HawkerSceneInit);
		Scene().RegisterSceneLogic("NewHawkerScene", HawkerSceneUpdate);
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}