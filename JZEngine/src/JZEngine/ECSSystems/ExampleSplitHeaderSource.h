/*	__FILE HEADER__
*	File:		ExampleSplitHeaderSource.h
	Primary:	Zachary Tay
	Secondary:	
	Date:		07/10/2021
	Brief:		
	Examples of creating ECS components and systems.
*/

#pragma once

#include "../ECS/ECS.h"
#include "ExampleSplitHeaderSource.h"
#include "ExampleSingleHeader.h"

// some random custom struct
struct InnerStruct
{
	float			im_a_float_{ 38.0812f };
	// you struct can contain other components, but its not recommended as a design flaw
	TestComponent	im_another_component_;
};

struct MyNewComponent
{
	char			nomal_data_{ 'z' };
	// take note that InnerStruct is not registered as a component, showing that any struct
	// can be a member data of a component
	InnerStruct		not_a_component;
};

struct MyNewSystem : public JZEngine::ECS::System
{
	int z{ 0 };

	MyNewSystem();

	virtual void FrameBegin(const float& dt) override;

	virtual void Update(const float& dt) override;
};