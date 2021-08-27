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
		JZEngine::Vec3 test_int ( 4 , -9 , 1);
		JZEngine::Vec3 test_float2 ( 404.222f , 8.1111f , 5.00f );
		JZEngine::Vec3 test_float3 ( 2.1122f , 9.1111f , 1.0f );
		JZEngine::Vec3 test_something{1,2,3};
		test_float2 += test_int  ;
		test_something *= test_float2 * test_float3;
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