#pragma once

#include "../BuildDefinitions.h"

#include <sstream>
#include <iomanip>

namespace JZEngine
{
	struct JZENGINE_API Console
	{
		float x_, y_, sx_, sy_;

		Console(float x, float y, float sx, float sy);

		template <typename...T>
		static void Log(const char* string, T... args)
		{
			char buffer[100];
			sprintf_s(buffer, string, args...);
			console_stream_ << "\n" << std::setw(4) << console_line_number_++ << ": " << buffer;
		}

		void Render();

	private:
		static unsigned int console_line_number_;
		static std::stringstream console_stream_;
	};
}