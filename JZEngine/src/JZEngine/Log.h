#pragma once

#include "BuildDefinitions.h"

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)



namespace JZEngine
{
	class JZENGINE_API Log
	{
	public:
		static void Init () ;
		inline static std::shared_ptr <spdlog::logger>& GetCoreLogger ()
		{
			return s_CoreLogger;
		}
		inline static std::shared_ptr <spdlog::logger>& GetClientLogger ()
		{
			return s_ClientLogger;
		}

	private :
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

