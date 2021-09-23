#pragma once

struct ImGuiInterface
{
	float x_, y_, sx_, sy_;		/*!< position and scale of the ImGui interface */

	ImGuiInterface();
	virtual ~ImGuiInterface() = default;

	void RenderInterface();
};