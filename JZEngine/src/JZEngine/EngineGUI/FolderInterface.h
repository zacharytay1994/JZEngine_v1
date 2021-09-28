#pragma once
#include "ImGuiInterface.h"

namespace JZEngine
{
	namespace ECS
	{
		struct ECSInstance;
	}
	struct FolderInterface : public ImGuiInterface
	{
		enum class DISPLAY
		{
			SCENES,
			PREFAB
		};

		ECS::ECSInstance* ecs_instance_{ nullptr };
		static constexpr unsigned int display_columns_{ 5 };

		FolderInterface(float x, float y, float sx, float sy);
		virtual void Render(float dt) override;

		void RenderPrefabs();

	private:
		DISPLAY mode{ DISPLAY::PREFAB };
	};
}