#include "PCH.h"
#include "ExampleSplitHeaderSource.h"

MyNewSystem::MyNewSystem()
{
	RegisterComponents<MyNewComponent, TestComponent>();
}

void MyNewSystem::FrameBegin(const float& dt)
{

}

void MyNewSystem::Update(const float& dt)
{
	// see the changes in the editor
	// when an entity both MyNewComponent and TestComponent
	GetComponent<MyNewComponent>().not_a_component.im_a_float_ -= 0.001f;
	GetComponent<TestComponent>().y += 1;
}