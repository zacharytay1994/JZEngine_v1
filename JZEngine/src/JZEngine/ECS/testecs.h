#pragma once

#include "ECS.h"

struct TestComponent
{
	int x{-90}, y{-5};
};

struct TestComponent2
{
	int x{0}, d{1};
};

struct TestSystem : public JZEngine::ECS::System
{
	int z{ 0 };

	static JZEngine::ECS::SystemComponents components_;

	TestSystem()
	{
		//RegisterComponents<TestComponent, TestComponent2>(components_);
	}

	virtual void FrameBegin() override 
	{
		//std::cout << "override test" << std::endl; 
	}

	virtual void Update(const float& dt) override
	{
		/*std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent>().x << ")" << std::endl;
		std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent>().y << ")" << std::endl;
		std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent2>().d << ")" << std::endl;*/
	}
};

struct TestComponent3
{
	int x{ -90 }, y{ -3 };
};

struct TestSystem2 : public JZEngine::ECS::System
{
	int z{ 0 };

	static JZEngine::ECS::SystemComponents components_;

	TestSystem2()
	{
		//RegisterComponents<TestComponent, TestComponent3>(components_);
	}

	virtual void FrameBegin() override
	{
		//std::cout << "override test" << std::endl; 
	}

	virtual void Update(const float& dt) override
	{
		/*std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent>().x << ")" << std::endl;
		std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent>().y << ")" << std::endl;
		std::cout << "system2: " << (int)current_id_ << std::endl;*/
	}
};

template <typename...COMPONENTS>
struct TestSystem3
{
	using type = std::tuple<COMPONENTS...>;

	void Update() {}
};
