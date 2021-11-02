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
		Scene().RegisterSceneInit("HawkerV2", HawkerSceneInit);
		Scene().RegisterSceneLogic("HawkerV2", HawkerSceneUpdate);
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}