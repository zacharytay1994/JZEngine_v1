/*	__FILE HEADER__
*	File:	Inspector.h
	Author: JZ
	Date:	26/08/21
	Brief:	Renders all components of a selected entity
			in the engine GUI with ImGui.
*/

#pragma once

#include <tuple>

#include "../BuildDefinitions.h"
#include "../ImGui/imgui.h"

#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::Inspector___
	 * ****************************************************************************************************
	 * Renders the components of a selected entity.
	 * Able to add and remove entities from the selected entity.
	 * ****************************************************************************************************
	*/
	struct JZENGINE_API Inspector
	{
		ECS::ECSInstance* const ecs_instance_;
		float x_, y_, sx_, sy_;		/*!< position and scale of the ImGui window */

		Inspector(float x, float y, float sx, float sy, ECS::ECSInstance* ecs);

		/*!
		 * @brief ___JZEngine::ToolsGUI::RenderInspector()___
		 * ****************************************************************************************************
		 * ImGUI window for the inspector, entity details.
		 * ****************************************************************************************************
		 * @param entity
		 * : The entity of which to display the details.
		 * ****************************************************************************************************
		*/
		void Render(ECS::Entity* const entity = nullptr);

		/*!
		 * @brief ___JZEngine::ToolsGUI::TreeNodeComponentAndSystems()___
		 * ****************************************************************************************************
		 * Creates an ImGUI tree node of all registered
		 * components and systems in the engine. Called
		 * in RenderInspector. It is part of the inspector
		 * display.
		 * ****************************************************************************************************
		*/
		void TreeNodeComponentsAndSystems(ECS::Entity* const entity);

		/* ____________________________________________________________________________________________________
		*	CUSTOM COMPONENT IMGUI LAYOUTS
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::Inspector::RenderComponent()___
		 * ****************************************************************************************************
		 * Default template for a component to be rendered using ImGui.
		 * ****************************************************************************************************
		 * @tparam COMPONENT 
		 * : Specialization to choose a function.
		 * @param component 
		 * : The component reference to inspect component values from.
		 * ****************************************************************************************************
		*/
		template <typename COMPONENT>
		void RenderComponent(COMPONENT& component)
		{
			ImGui::Text("Oops nothing here...");
		}

		template <>
		void RenderComponent(TestComponent& component)
		{
			ImGui::SliderInt("x", &component.x, -180, 180);
			ImGui::SliderInt("y", &component.y, -180, 180);
		}

		template <>
		void RenderComponent(Transform& component)
		{
			ImGui::SliderFloat("x", &component.x, 0, 1000);
			ImGui::SliderFloat("y", &component.y, 0, 1000);
			ImGui::SliderFloat("theta", &component.theta, -360.0f, 360.0f);
			ImGui::SliderFloat("sx", &component.sx, 0, 1000);
			ImGui::SliderFloat("sy", &component.sy, 0, 1000);
		}

		template <>
		void RenderComponent(MyNewComponent& component)
		{
			ImGui::SliderInt("x", &component.not_a_component.im_another_component_.x, -3000, 1000);
			ImGui::SliderInt("y", &component.not_a_component.im_another_component_.y, -2000, 1000);
			ImGui::SliderFloat("a float", &component.not_a_component.im_a_float_, -300, 300);
			ImGui::Text("this is a %c", component.nomal_data_);
		}

		/*!
		 * @brief ___JZEngine::LoopTupleRender___
		 * ****************************************************************************************************
		 * Loops through a ECS::ECSConfig::Component to get a 
		 * Component type to call the template specialization
		 * defined above.
		 * ****************************************************************************************************
		 * @param i 
		 * : The index of the Component type into the tuple.
		 * @param entity 
		 * : The entity to get the component from.
		 * ****************************************************************************************************
		*/
		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if<I == sizeof...(TUPLE), void>::type
			LoopTupleRender(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			std::cout << "LoopTupleRender::tuple size exceeded." << std::endl;
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if < I < sizeof...(TUPLE), void>::type
			LoopTupleRender(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			if (I == i)
			{
				using COMPONENT = decltype(std::get<I>(t));
				if (ImGui::TreeNodeEx(typeid(COMPONENT).name(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |ImGuiTreeNodeFlags_Framed))
				{
					RenderComponent(entity.GetComponent<std::remove_reference_t<COMPONENT>>());
					ImGui::TreePop();
				}
				return;
			}
			LoopTupleRender<I + 1>(t, i, entity);
		}
	};
}