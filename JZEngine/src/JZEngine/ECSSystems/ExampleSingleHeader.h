#pragma once

#include "../ECS/ECS.h"
#include "../EngineGUI/Console.h"

struct TestComponent
{
	int x{ -90 }, y{ -5 };
};

struct TestComponent2
{
	int x{0}, d{1};
};

struct TestComponent3
{
	float x{ -90.0f }, y{ -3.0f };
};

struct Transform
{
	float x, y;
	float theta;
	float sx, sy;
};

struct TestSystem : public JZEngine::ECS::System
{
	int z{ 0 };

	TestSystem()
	{
		// registers components that this system is going to work on
		// only entities with at least these components will be processed
		// by the system.
		RegisterComponents<TestComponent3, TestComponent2>();
	}

	// updates once per entity component per system per frame
	virtual void Update(const float& dt) override
	{
	}
};

struct TestSystem2 : public JZEngine::ECS::System
{
	int z{ 0 };
	float clock = 0.0f;
	bool write = false;

	TestSystem2()
	{
		RegisterComponents<TestComponent, TestComponent3>();
	}

	// frame begin is optional and is special as it only updates once per system per frame,
	// not once per entity component per system per frame
	virtual void FrameBegin(const float& dt) override
	{
		if (write)
		{
			clock = 0.0f;
			write = false;
		}
		if (clock < 10.0f)
		{
			clock += dt;
		}
		else
		{
			write = true;
		}
		if (write)
		{
			JZEngine::Console::Log("TestSystem Updated FrameBegin");
		}
	}

	// take note here if 2 or more entities contain TestComponent and TestComponent3,
	// this will be run twice, whereas FrameBegin will run once no matter how many entities
	virtual void Update(const float& dt) override
	{
		if (write)
		{
			JZEngine::Console::Log("TestSystem Updated Entity");
		}
	}
};
