/*	__FILE HEADER__
*	File:	Console.h
	Author: JZ
	Date:	26/08/21
	Brief:	Engine console system. Able to write to console
			through a static function Console::Log(const char*).
*/

#pragma once

#include "../BuildDefinitions.h"

#include <sstream>
#include <iomanip>
#include <unordered_map>

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::Console___
	 * ****************************************************************************************************
	 * The engine GUI console. Exposes a static function
	 * Console::Log(const char*) that writes to the console.
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
		 * @brief ___JZEngine::Console::Log()___
		 * ****************************************************************************************************
		 * Logs a c string into the engine console.
		 * ****************************************************************************************************
		 * @tparam ...T 
		 * : Formatted arguments to fill in the c string.
		 * @param string 
		 * : The c string.
		 * @param ...args 
		 * : Formatted arguments to fill in the c string.
		 * ****************************************************************************************************
		*/
		template <typename...T>
		static void Log(const char* string, T... args)
		{
			/*char buffer[100];
			sprintf_s(buffer, string, args...);
			console_stream_ << "\n" << std::setw(4) << console_line_number_++ << ": " << buffer;*/
		}

		/*!
		 * @brief ___JZEngine::Console::Render()___
		 * ****************************************************************************************************
		 * Renders the console.
		 * ****************************************************************************************************
		*/
		void Render();

		static void ExistConsoleLog(const std::string& name);

		static void SetConsole(const std::string& name);

		static std::string* currently_selected_console_;
		static std::unordered_map<std::string, unsigned char>* console_log_names_;
		ConsoleLog* console_log_{ nullptr };
		static bool more_info_;

	private:
		static unsigned int console_line_number_;	/*!< the amount of lines currently in the console */
	};
}