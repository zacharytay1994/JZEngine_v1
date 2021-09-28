#pragma once

#include "../ECS/ECS.h"
#include "../EngineGUI/Console.h"
#include "../DebugTools/Log.h"

struct TestComponent
{
	int x{ -90 }, y{ -5 };

	template <typename OStream>
	friend OStream& operator<<(OStream& os, const TestComponent& component)
	{
		return os << "(" << component.x << "," << component.y << ")";
	}
};

struct TestComponent2
{
	char test;
};

struct TestComponent3
{
	float x{ -90.0f }, y{ -3.0f };
};

struct TestSystem : public JZEngine::ECS::System
{
	int count{ 0 };
	TestSystem()
	{
		// registers components that this system is going to work on
		// only entities with at least these components will be processed
		// by the system.
		RegisterComponents<TestComponent2>();
	}

	virtual void FrameBegin(const float& dt) override
	{
		JZEngine::Log::Info("Main", "Count: {}", count);
		count = 0;
	}

	// updates once per entity component per system per frame
	virtual void Update(const float& dt) override
	{
		++count;
	}
};

struct TestSystem2 : public JZEngine::ECS::System
{
	int count{ 0 };

	TestSystem2()
	{
		RegisterComponents<TestComponent3>();
	}

	// frame begin is optional and is special as it only updates once per system per frame,
	// not once per entity component per system per frame
	virtual void FrameBegin(const float& dt) override
	{
		JZEngine::Log::Info("Main", "Count2: {}", count);
		count = 0;
	}

	// take note here if 2 or more entities contain TestComponent and TestComponent3,
	// this will be run twice, whereas FrameBegin will run once no matter how many entities
	virtual void Update(const float& dt) override
	{
		++count;
	}
};
