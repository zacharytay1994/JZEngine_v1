#include "PCH.h"
#include "Console.h"

#include "../ImGui/imgui.h"

#include "../EngineConfig.h"

namespace JZEngine
{
	unsigned int Console::console_line_number_{ 0 };
	std::stringstream Console::console_stream_;

	Console::Console(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{

	}

	void Console::Render()
	{
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(window_width) * x_, static_cast<float>(window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(window_width) * sx_, static_cast<float>(window_height) * sy_ }, ImGuiCond_Once);
		ImGui::Begin("Console");
		ImGui::Text(console_stream_.str().c_str());
		ImGui::End();
	}
}