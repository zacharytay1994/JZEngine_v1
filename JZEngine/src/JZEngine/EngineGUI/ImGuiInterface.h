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
		bool active_{ true };
		float x_, y_, sx_, sy_;		/*!< position and scale of the ImGui interface */

		ImGuiInterface(float x, float y, float sx, float sy);
		virtual ~ImGuiInterface() = default;

		void RenderInterface(float dt);

		virtual void Render(float dt) {};

		void SetEngineGUI(EngineGUI* enginegui);

	protected:
		template <typename INTERFACE>
		std::shared_ptr<INTERFACE> GetInterface() {
			return engine_gui_->GetInterface<INTERFACE>();
		}
	private:
		EngineGUI* engine_gui_{ nullptr };
	};
}