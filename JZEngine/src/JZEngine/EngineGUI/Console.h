/*	__FILE HEADER__
*	File:	Console.h
	Author: JZ
	Date:	26/08/21
	Brief:	Engine console system. Able to write to console
			through a static function Console::Log(const char*).
*/

#pragma once

#include "../BuildDefinitions.h"

#include <string>
#include <unordered_map>

//#include "ImGuiInterface.h"

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::Console___
	 * ****************************************************************************************************
	 * The engine GUI console. Exposes static functions
	 * Log::Info/Warning/Error/Critical that writes to the 
	 * specified ImGui console.
	 * Keeps tracks of console line numbers.
	 * ****************************************************************************************************
	*/
	struct ConsoleLog;
	struct JZENGINE_API Console
	{
		float x_, y_, sx_, sy_;		/*! position and scale */

		Console(float x, float y, float sx, float sy);
		~Console();

		/*!
		 * @brief ___JZEngine::Console::Render()___
		 * ****************************************************************************************************
		 * Renders the console.
		 * ****************************************************************************************************
		*/
		void Render();

		/*!
		 * @brief ___JZEngine::Console::ExistConsoleLog()___
		 * ****************************************************************************************************
		 * Checks if the console log already exist in the 
		 * map, else creates it.
		 * ****************************************************************************************************
		 * @param name 
		 * : The name of the console log.
		 * ****************************************************************************************************
		*/
		void ExistConsoleLog(const std::string& name);

		/*!
		 * @brief ___JZEngine::Console::SetConsole()___
		 * ****************************************************************************************************
		 * Sets the currently displayed console.
		 * ****************************************************************************************************
		 * @param name 
		 * : The console to display.
		 * ****************************************************************************************************
		*/
		void SetConsole(const std::string& name);

		friend struct ConsoleLog;
	private:

		std::string*									currently_selected_console_;	/*!< the currently displayed console */
		std::unordered_map<std::string, unsigned char>*	console_log_names_;				/*!< all consoles */
		ConsoleLog*										console_log_{ nullptr };		/*!< console log object, imgui stuff */
		bool											more_info_{ false };			/*!< if log information is more/less */
	};
}