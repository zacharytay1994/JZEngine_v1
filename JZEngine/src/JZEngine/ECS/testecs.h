#pragma once

#include "ECS.h"

struct TestComponent
{
	int x{-90}, y{0};
};

struct TestComponent2
{
	int d{1};
};

struct TestSystem : public JZEngine::ECS::System
{
	int z{ 0 };

	TestSystem()
	{
		RegisterComponents<JZEngine::ECS::TestData>();
	}

	virtual void FrameBegin() override 
	{
		//std::cout << "override test" << std::endl; 
	}

	virtual void Update(const float& dt) override
	{
		std::cout << "override update (" << GetComponent<JZEngine::ECS::TestData>().x << ")" << std::endl;
	}
};