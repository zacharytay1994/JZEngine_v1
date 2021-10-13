#pragma once

#include "ImGuiInterface.h"

namespace JZEngine {

	struct SceneLayerControl : public ImGuiInterface {
		SceneLayerControl(float x, float y, float sx, float sy, int group);
		virtual void Render(float dt) override;
	};

}