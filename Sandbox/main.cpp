#include <JZEngine.h>

class Sandbox : public JZEngine::Application
{
public:
	Sandbox()
		:
		Application()
	{
		JZEngine::Console::Log("Engine Up and Running!");
		JZEngine::Console::Log("Engine Up and Running!%f", 1.02f);
	}
};

JZEngine::Application* JZEngine::CreateApplication()
{
	return new Sandbox();
}