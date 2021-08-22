#include "PCH.h"
#include "Inspector.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"

namespace JZEngine
{
	Inspector::Inspector(float x, float y, float sx, float sy)
		:
		x_(x), y_(y), sx_(sx), sy_(sy)
	{

	}

	/*!
	 * @brief ___JZEngine::ToolsGUI::RenderInspector()___
	 * ****************************************************************************************************
	 * ImGUI window for the inspector, entity details.
	 * ****************************************************************************************************
	 * @param entity
	 * : The entity of which to display the details.
	 * ****************************************************************************************************
	*/
	void Inspector::Render(ECS::Entity& entity)
	{
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(window_width) * x_, static_cast<float>(window_height) * y_ }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(window_width) * sx_, static_cast<float>(window_height) * sy_ }, ImGuiCond_Once);
		ImGui::Begin("Inspector");
		TreeNodeComponentsAndSystems(entity);
		ImGui::Text("______________________________");
		ImGui::Text("Entity (ID: %d) Components:", entity.ecs_id_);
		ImGui::Text(" ");
		if (entity.owning_chunk_)
		{
			for (int i = 0; i < ECS::MAX_COMPONENTS; ++i)
			{
				if (entity.owning_chunk_->owning_archetype_->mask_[i])
				{
					ImGui::SetNextItemOpen(true, ImGuiCond_Once);
					LoopTupleRender(ECS::ECSConfig::Component(), i, entity);
				}
			}
		}
		/*std::vector<std::string> names = { "name1", "name2", "name3", "name4" };
		ImGui::BeginListBox("", {0.0f, 50.0f});
		for (auto& i : names)
		{
			if (ImGui::Selectable(i.c_str(), true))
			{
				Console::Log(i.c_str());
			}
		}*/
		//ImGui::EndListBox();
		ImGui::End();
	}

	/*!
	 * @brief ___JZEngine::ToolsGUI::TreeNodeComponentAndSystems()___
	 * ****************************************************************************************************
	 * Creates an ImGUI tree node of all registered
	 * components and systems in the engine. Called
	 * in RenderInspector. It is part of the inspector
	 * display.
	 * ****************************************************************************************************
	*/
	void Inspector::TreeNodeComponentsAndSystems(ECS::Entity& entity)
	{
		if (ImGui::TreeNode("Engine Components and Systems"))
		{
			ImGui::Text("______________________________");
			ImGui::Text("Components:");
			ImGui::BeginListBox("[Com]", { 0.0f, 100.0f });
			bool has_component_ = false;
			for (auto& c : ECS::ECSInstance::Instance().component_manager_.registered_components_)
			{
				if (entity.HasComponent(c.bit_))
				{
					has_component_ = true;
					ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f,1.0f,0.0f,1.0f });
				}
				if (ImGui::Selectable(c.name_.c_str(), true) && !has_component_)
				{
					if (!has_component_)
					{
						LoopTupleAddComponent(ECS::ECSConfig::Component(), c.bit_, entity);
						std::stringstream ss;
						ss << "Added component [" << c.name_ << "]";
						Console::Log(ss.str().c_str());
					}
					else
					{

					}
				}
				if (has_component_)
				{
					has_component_ = false;
					ImGui::PopStyleColor(1);
				}
			}
			ImGui::EndListBox();

			ImGui::Text("______________________________");
			ImGui::Text("Systems:");
			ImGui::BeginListBox("[Sys]", { 0.0f, 100.0f });
			for (auto& s : ECS::ECSInstance::Instance().system_manager_.registered_systems_)
			{
				if (ImGui::Selectable(s.c_str(), true))
				{
					Console::Log(s.c_str());
				}
			}
			ImGui::EndListBox();
			ImGui::TreePop();
		}
	}
}