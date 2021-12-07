/*	__FILE HEADER__
*	File:		ImGuiInterface.h
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Virtual class to be inherited by any
				imgui interface and added to the enginegui.
*/

#pragma once

#include <memory>
#include "../ImGui/imgui.h"
#include "ImGuiInterface.h"
#include "EngineGUI.h"

namespace JZEngine 
{
	struct EngineGUI;
	struct ImGuiInterface
	{
		int group_{ -1 };
		bool active_{ true };
		float gui_alpha_{ 0.8f };
		float x_, y_, sx_, sy_;		/*!< position and scale of the ImGui interface */

		ImGuiInterface(float x, float y, float sx, float sy, int group = -1);
		virtual ~ImGuiInterface() = default;

		void RenderInterface(float dt);

		void SetNextWindowDimensions(float start_x, float start_y, float width, float height);

		virtual void Render(float dt) { UNREFERENCED_PARAMETER(dt); };

		virtual void CloseAction() {};

		void SetEngineGUI(EngineGUI* enginegui);

		void ToggleOnOff();

		void CloseButtonMenuBar();

	protected:
		template <typename INTERFACE>
		std::shared_ptr<INTERFACE> GetInterface() {
			return engine_gui_->GetInterface<INTERFACE>();
		}

		EngineGUI* engine_gui_{ nullptr };
	};
}