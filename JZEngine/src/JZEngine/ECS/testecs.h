#pragma once

#include "ECS.h"

struct TestComponent
{
	int x{-90}, y{-5};
};

struct TestComponent2
{
	int d{1};
};

struct TestSystem : public JZEngine::ECS::System
{
	int z{ 0 };

	static std::array<JZEngine::ECS::ui32, JZEngine::ECS::MAX_COMPONENTS> components_;

	TestSystem()
	{
		RegisterComponents<TestComponent, TestComponent2>(components_);
	}

	virtual void FrameBegin() override 
	{
		//std::cout << "override test" << std::endl; 
	}

	virtual void Update(const float& dt) override
	{
		std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent>().x << ")" << std::endl;
		std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent>().y << ")" << std::endl;
		std::cout << "override update " << (int)current_id_ << " (" << GetComponent<TestComponent2>().d << ")" << std::endl;
	}
};
