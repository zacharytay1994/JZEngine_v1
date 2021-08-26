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
	struct JZENGINE_API Console
	{
		float x_, y_, sx_, sy_;		/*! position and scale */

		Console(float x, float y, float sx, float sy);

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

	private:
		static unsigned int console_line_number_;	/*!< the amount of lines currently in the console */
		//static std::stringstream* console_stream_;	/*!< the stringstream storing all console text */
	};
}