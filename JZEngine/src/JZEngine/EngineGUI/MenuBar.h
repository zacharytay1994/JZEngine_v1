/*	__FILE HEADER__
*	File:		MenuBar.h
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders the menubar at the top of the engine.
*/

#pragma once

#include <string>
#include "ImGuiInterface.h"

namespace JZEngine {
	struct MenuBar : public ImGuiInterface {
		static bool play_;
		static float height_;
		static bool	light_theme_;
		bool more_info_{ false };
		MenuBar(float x, float y, float sx, float sy, int group);
		virtual void Render(float dt) override;
	private:
		std::string transform_mode_{"Transform Mode: TRANSLATE"};

		void ToggleButton(const char* str_id, bool* v);
	};
}