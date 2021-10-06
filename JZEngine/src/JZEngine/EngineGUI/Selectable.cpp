#include <PCH.h>
#include "Selectable.h"
#include "../ECS/ECSConfig.h"
#include "../EngineGUI/EngineGUI.h"

namespace JZEngine
{
	//SelectableSystem::SelectableSystem()
	//{
	//	RegisterComponents<Transform, Selectable>();
	//}

	//void SelectableSystem::Update(const float& dt)
	//{
	//	Transform& transform = GetComponent<Transform>();
	//	Selectable& selectable = GetComponent<Selectable>();
	//	Vec2f mouse_world = EngineGUI::GetWorldMousePosition();
	//	float half_width = ((transform.scale_.x * transform.size_.x) / 2.0f);
	//	float half_height = ((transform.scale_.y * transform.size_.y) / 2.0f);
	//	int left = transform.position_.x - half_width;
	//	int right = transform.position_.x + half_width;
	//	int top = transform.position_.y + half_height;
	//	int bottom = transform.position_.y - half_height;
	//	// check if mouse point within it
	//	if (mouse_world.x < left || mouse_world.x > right || mouse_world.y > top || mouse_world.y < bottom)
	//	{
	//		selectable.selected = false;
	//		return;
	//	}
	//	selectable.selected = true;
	//}
}