#pragma once

namespace JZEngine
{
	struct DebugInformation
	{
		float x_, y_, sx_, sy_;		/*!< position and scale of the ImGui window */

		DebugInformation(float x, float y, float sx, float sy);

		void Render();
	};
}