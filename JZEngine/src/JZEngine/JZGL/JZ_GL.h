/*	__FILE HEADER__
*	File:	JZ_GL.h
	Author: JZ
	Date:	01/07/21
	Brief:	Encapsulates all OpenGL initializations
			and updates using GLFW and glad.
*/

#pragma once

#include "../BuildDefinitions.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::GLFW_Instance___
	 *
	 * An OpenGL instance created using GLFW and glad.
	*/
	struct JZENGINE_API GLFW_Instance
	{
		GLFWwindow* window_{ nullptr };	/*!< handle to the window created using GLFW */
		int				window_width_{ 0 };			/*!< width of the GLFWwindow created and updated from resizing */
		int				window_height_{ 0 };			/*!< height of the GLFWwindow created and updated from resizing */

		GLFW_Instance ( int width , int height );
		~GLFW_Instance ();


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

		void Draw ();

	private:
		/*!
		 * @brief ___JZEngine::GLFW_Instance::Initialize()___
		 *
		 * Sets up the OpenGL instance using GLFW, and loads glad.
		*/
		void Initialize ();
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