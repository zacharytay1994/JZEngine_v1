#include <JZEngine.h>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <math.h>

class Sandbox : public JZEngine::Application
{
public:
	Sandbox ()
		:
		Application ()
	{
		JZEngine::Vec2 test_int ( 4 , -9 );
		JZEngine::Vec2 test_float2 ( 404.404f , 81.0f );
		JZEngine::Vec2<float> test_something = test_int.Normalize() ;

		std::cout << "\n test_something 1 : " << test_something << " \n";
	}
};

JZEngine::Application* JZEngine::CreateApplication ()
{
	return new Sandbox ();
}