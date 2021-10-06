#pragma once
#include "ImGuiInterface.h"

namespace JZEngine
{
	struct EngineSettings : public ImGuiInterface
	{
		EngineSettings(float x, float y, float sx, float sy, int group);

		virtual void Render(float dt) override;

	private:
		int temp_width_;
		int temp_height_;
		int temp_cam_x;
		int temp_cam_y;
	};
}