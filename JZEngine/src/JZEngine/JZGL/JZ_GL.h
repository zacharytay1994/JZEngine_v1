/*	__FILE HEADER__
*	File:		JZ_GL.h
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Encapsulates all OpenGL initializations
				and updates using GLFW and glad.
*/

#pragma once

#include "../BuildDefinitions.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../GlobalSystems.h"


namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::GLFW_Instance___
	 *
	 * An OpenGL instance created using GLFW and glad.
	*/
	struct GLFW_Instance : public GlobalSystem
	{
		static GLFWwindow*		window_;		/*!< handle to the window created using GLFW */
		int				window_width_{ 0 };		/*!< width of the GLFWwindow created and updated from resizing */
		int				window_height_{ 0 };	/*!< height of the GLFWwindow created and updated from resizing */

		static bool focused_;

		GLFW_Instance ( int width , int height );
		~GLFW_Instance ();

		virtual void Init () override;

		/*!
		 * @brief ___JZEngine::GLFW_Instance::FrameStart()___
		 *
		 * Called at the start of every frame, i.e. the update loop in
		 * JZEngine::Application::Update() defined in Application.cpp.
		*/
		void FrameStart ();

		/*!
		 * @brief ___JZEngine::GLFW_Instance::FrameEnd()___
		 *
		 * Called at the end of every frame, i.e. the update loop in
		 * JZEngine::Application::Update() defined in Application.cpp.
		*/
		void FrameEnd ();

		/*!
		 * @brief ___JZEngine::GLFW_Instance::Active()___
		 *
		 * Calls GLFWWindowShouldClose() to see if the update loop in
		 * Application.cpp should continue.
		*/
		bool Active ();

		static bool dimensions_updated;
		static void UpdateViewportDimensions();

		static void ResizeWindow(int width, int height);
		static void GetWindowPos(int& x, int& y);
		static void SetWindowPos(int x, int y);

	private:
		/*!
		 * @brief ___JZEngine::GLFW_Instance::Initialize()___
		 *
		 * Sets up the OpenGL instance using GLFW, and loads glad.
		*/
		void Initialize ();

		void HideConsole ();

		bool mouse_settings_ { false };
	};

	/*!
	 * @brief ___JZEngine::GLFW_Instance::FramebufferSizeCallback___
	 *
	 * Callback function passed to GLFW when resizing the window.
	 *
	 * @param window	: pointer to the window created after calling GLFWCreateWindow()
	 * @param width		: width of the window to resize to
	 * @param height	: height of the window to resize to
	*/
	void FramebufferSizeCallback ( GLFWwindow* window , int width , int height );
}