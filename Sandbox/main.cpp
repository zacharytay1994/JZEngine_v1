#include <JZEngine.h>

#include <iostream>


class Sandbox : public JZEngine::Application
{
public:
	Sandbox ()
		:
		Application ()
	{
		JZEngine::Timer timer;
		timer.Mark (); 
		//std::cout << "Start timer : " << start << std::endl;
		JZEngine::Vec2 test_int ( 4 , -9 );
		JZEngine::Vec2 test_float2 ( 404.404f , 81.0f );
		JZEngine::Vec2<float> test_something = test_int.Normalize () ;
		std::cout << test_something << std::endl;
		auto time = timer.Peek ();
		std::cout << "From timer : " << time << std::endl;

		timer.TimerHistory ();

	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}