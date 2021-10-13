#include <PCH.h>
#include "SceneLayerControl.h"

namespace JZEngine {
	SceneLayerControl::SceneLayerControl(float x, float y, float sx, float sy, int group)
		:
		ImGuiInterface(x, y, sx, sy, group)
	{
	}

	void SceneLayerControl::Render(float dt) 
	{
		ImGui::Begin("Scene Layer");
		ImGui::End();
	}
}