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
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New"))
				{
					//Do something
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("DebugInformation", "[TAB]"))
				{
					GetInterface<DebugInformation>()->active_ = !GetInterface<DebugInformation>()->active_;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	} 
}