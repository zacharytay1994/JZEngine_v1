#include <PCH.h>
#include "SceneLayerControl.h"
#include "../GraphicRendering/RenderQueue.h"

namespace JZEngine {
	SceneLayerControl::SceneLayerControl(float x, float y, float sx, float sy, int group)
		:
		ImGuiInterface(x, y, sx, sy, group)
	{
	}

	void SceneLayerControl::Render(float dt) 
	{
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin("Scene Layer");
		ImGui::Text("Back");
		ImGui::Separator();
		std::stringstream ss;
		for (auto& layer : RenderQueue::layers_) {
			ss.str("");
			ss << "layer " << *layer;
			ImGui::InputInt(ss.str().c_str(), &*layer);
		}
		ImGui::Separator();
		ImGui::Text("Front");
		ImGui::End();
	}
}