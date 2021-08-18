#pragma once

#include "../BuildDefinitions.h"

#include <tuple>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../ECS/ECS.h"
#include "../ECS/testecs.h"

namespace JZEngine
{
	struct JZENGINE_API ToolsGUI
	{
		ToolsGUI(GLFWwindow*& glfwwindow);
		~ToolsGUI();

		void Update(ECS::Entity& entity);
	private:
		void InitializeWithGLFW(GLFWwindow*& glfwwindow);
		void RenderInspector(ECS::Entity& entity);

		template <typename COMPONENT>
		void RenderComponent(COMPONENT& component);

		template <>
		void RenderComponent(TestComponent& component)
		{
			std::cout << "inspector (TestComponent): ";
			std::cout << component.x << "," << component.y << std::endl;
		}

		template <>
		void RenderComponent(TestComponent2& component)
		{
			std::cout << "inspector (TestComponent2): ";
			std::cout << component.x << "," << component.d << std::endl;
		}

		template <>
		void RenderComponent(TestComponent3& component)
		{
			std::cout << "inspector (TestComponent3): ";
			std::cout << component.x << "," << component.y << std::endl;
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if<I == sizeof...(TUPLE), void>::type
			LoopTuple(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			std::cout << "tuple size exceeded." << std::endl;
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if < I < sizeof...(TUPLE), void>::type
			LoopTuple(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity)
		{
			if (I == i)
			{
				//std::cout << entity.GetComponent<decltype(std::get<I>(t))>().x << std::endl;
				using COMPONENT = decltype(std::get<I>(t));
				//entity.GetComponent<std::remove_reference_t<COMPONENT>>();
				RenderComponent(entity.GetComponent<std::remove_reference_t<COMPONENT>>());
				std::cout << "looptuple:: " << typeid(COMPONENT).name() << std::endl;
				return;
			}
			LoopTuple<I + 1>(t, i, entity);
		}
	};
}