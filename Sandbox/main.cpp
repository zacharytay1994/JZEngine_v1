#include <JZEngine.h>

class Sandbox : public JZEngine::Application
{
public:
	Sandbox()
	{

	}
};

JZEngine::Application* JZEngine::CreateApplication()
{
	return new Sandbox();
}