#pragma once

#include <string>
#include "ImGuiInterface.h"

namespace JZEngine {
	struct MenuBar : public ImGuiInterface {
		static float height_;
		MenuBar(float x, float y, float sx, float sy, int group);
		virtual void Render(float dt) override;
	private:
		std::string transform_mode_{"Transform Mode: TRANSLATE"};
	};
}