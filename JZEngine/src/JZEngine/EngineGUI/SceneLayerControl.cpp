#include <PCH.h>
#include "SceneLayerControl.h"
#include "../GraphicRendering/Renderers/RenderQueue.h"
#include "../Resource/ResourceManager.h"

//namespace JZEngine {
//	SceneLayerControl::SceneLayerControl(float x, float y, float sx, float sy, int group)
//		:
//		ImGuiInterface(x, y, sx, sy, group)
//	{
//	}
//
//	bool CompareLayerPointer(RenderQueue::LayerData a, RenderQueue::LayerData b) { return (*a.layer_ < *b.layer_); }
//
//	void SceneLayerControl::Render(float dt) 
//	{
//		ImGui::SetNextWindowBgAlpha(1.0f);
//		ImGui::Begin("Scene Layer");
//		//float width = ImGui::GetWindowWidth();
//		ImGui::Text("Back");
//		ImGui::Separator();
//		std::stringstream ss;
//		std::sort(RenderQueue::layers_.begin(), RenderQueue::layers_.end(), CompareLayerPointer);
//		int i = std::numeric_limits<int>::min();
//		int uid = 0;
//		for (auto& layer : RenderQueue::layers_) {
//			if (*layer.layer_ > i)
//			{
//				i = *layer.layer_;
//				ImGui::Text("Layer %d", *layer.layer_);
//				ImGui::Separator();
//			}
//			ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(layer.texture_id_)->GetRendererID()), { 50.0f, 50.0f }, {0,1}, {1,0});
//			ImGui::SameLine();
//			ss.str("");
//			ss << "##layer" << uid++;
//			ImGui::InputInt(ss.str().c_str(), &*layer.layer_, 0);
//		}
//		ImGui::Separator();
//		ImGui::Text("Front");
//		ImGui::Separator();
//		ImGui::End();
//	}
//}