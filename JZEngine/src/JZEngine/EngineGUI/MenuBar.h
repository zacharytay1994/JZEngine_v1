#pragma once

#include "ImGuiInterface.h"

namespace JZEngine {
	struct MenuBar : public ImGuiInterface {
		MenuBar(float x, float y, float sx, float sy);
		virtual void Render(float dt) override;
	};
}