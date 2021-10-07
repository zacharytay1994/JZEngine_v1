/*	__FILE HEADER__
*	File:		EngineSettings.h
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders the interface that allows the user to
				modify the engine settings.
*/

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