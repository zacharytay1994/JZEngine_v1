#include <PCH.h>
#include "MenuBar.h"
#include "EngineGUI.h"

#include "DebugInformation.h"

namespace JZEngine {
	MenuBar::MenuBar(float x, float y, float sx, float sy) 
		:
		ImGuiInterface(x, y, sx, sy)
	{

	}

	void MenuBar::Render() {
		ImGui::Begin("Menu");
		if (ImGui::Button("DebugInformation")) {
			std::shared_ptr<DebugInformation> debug_information = GetInterface<DebugInformation>();
			debug_information->active_ = !debug_information->active_;
		}
		ImGui::End();
	} 
}