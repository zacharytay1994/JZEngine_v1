#include <JZEngine.h>

#include <iostream>



class Sandbox : public JZEngine::Application
{
public:
	Sandbox ()
		:
		Application ()
	{
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}