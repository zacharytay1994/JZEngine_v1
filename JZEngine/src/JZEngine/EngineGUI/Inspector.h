#pragma once

#include <tuple>

#include "../ImGui/imgui.h"

#include "../ECS/ECS.h"
#include "../ECS/testecs.h"

namespace JZEngine
{
	struct Inspector
	{
		float x_, y_, sx_, sy_;

		Inspector(float x, float y, float sx, float sy);

		/*!
		 * @brief ___JZEngine::ToolsGUI::RenderInspector()___
		 * ****************************************************************************************************
		 * ImGUI window for the inspector, entity details.
		 * ****************************************************************************************************
		 * @param entity
		 * : The entity of which to display the details.
		 * ****************************************************************************************************
		*/
		void Render(ECS::Entity& entity);

		/*!
		 * @brief ___JZEngine::ToolsGUI::TreeNodeComponentAndSystems()___
		 * ****************************************************************************************************
		 * Creates an ImGUI tree node of all registered
		 * components and systems in the engine. Called
		 * in RenderInspector. It is part of the inspector
		 * display.
		 * ****************************************************************************************************
		*/
		void TreeNodeComponentsAndSystems(ECS::Entity& entity);

		/* ____________________________________________________________________________________________________
		*	CUSTOM COMPONENT IMGUI LAYOUTS
		   ____________________________________________________________________________________________________*/

		template <typename COMPONENT>
		void RenderComponent(COMPONENT& component)
		{
			ImGui::Text("Oops nothing here...");
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
		void RenderComponent(TestComponent& component)
		{
			ImGui::SliderInt("x", &component.x, -180, 180);
			ImGui::SliderInt("y", &component.y, -180, 180);
		}

		template <>
		void RenderComponent(TestComponent2& component)
		{
		}

		template <>
		void RenderComponent(TestComponent3& component)
		{
		}

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
				if (ImGui::TreeNode(typeid(COMPONENT).name()))
				{
					RenderComponent(entity.GetComponent<std::remove_reference_t<COMPONENT>>());
					ImGui::TreePop();
				}
				return;
			}
			LoopTupleRender<I + 1>(t, i, entity);
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if<I == sizeof...(TUPLE), void>::type
			LoopTupleAddComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			std::cout << "LoopTupleAddComponent::tuple size exceeded." << std::endl;
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if < I < sizeof...(TUPLE), void>::type
			LoopTupleAddComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			if (I == i)
			{
				using COMPONENT = decltype(std::get<I>(t));
				entity.AddComponent<std::remove_reference_t<COMPONENT>>();
				return;
			}
			LoopTupleAddComponent<I + 1>(t, i, entity);
		}

		/*template <size_t I = 0, typename...TUPLE>
		typename std::enable_if<I == sizeof...(TUPLE), void>::type
			LoopTupleRemoveComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			std::cout << "LoopTupleAddComponent::tuple size exceeded." << std::endl;
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if < I < sizeof...(TUPLE), void>::type
			LoopTupleRemoveComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			if (I == i)
			{
				using COMPONENT = decltype(std::get<I>(t));
				entity.ReComponent<std::remove_reference_t<COMPONENT>>();
				return;
			}
			LoopTupleAddComponent<I + 1>(t, i, entity);
		}*/
	};
}