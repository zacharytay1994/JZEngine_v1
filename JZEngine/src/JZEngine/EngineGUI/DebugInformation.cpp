#include <PCH.h>
#include "DebugInformation.h"

namespace JZEngine 
{
	DebugInformation::DebugInformation(float x, float y, float sx, float sy) 
		:
		ImGuiInterface(x, y, sx, sy)
	{

	}

	void DebugInformation::Render() 
	{
		ImGui::Begin("Debug Information");
		ImGui::End();
	}
}