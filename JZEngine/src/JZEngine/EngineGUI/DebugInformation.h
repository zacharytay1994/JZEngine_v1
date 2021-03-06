/*	__FILE HEADER__
*	File:		DebugInformation.h
	Primary:	Zachary Tay
	Secondary:
	Date:		07/10/2021
	Brief:
	Handles the rendering of all debug information.
	Data that the performance visualizer calculates.
*/

#pragma once

#include "ImGuiInterface.h"

namespace JZEngine
{
	struct DebugInformation : public ImGuiInterface
	{
		float time_quantum_{ 1.0f };
		int target_fps_{ 60 };
		//float x_{ 0.0f }, y_{ 0.0f }, sx_{ 10.0f }, sy_{ 10.0f };		/*!< position and scale of the ImGui window */

		DebugInformation(float x, float y, float sx, float sy, int group);

		virtual void Render(float dt) override;
	};
}