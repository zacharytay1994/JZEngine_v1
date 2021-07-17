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


//// Core log macros
//#define HZ_CORE_TRACE	(...) ::JZEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
//#define HZ_CORE_INFO	(...) ::JZEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
//#define HZ_CORE_WARN	(...) ::JZEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
//#define HZ_CORE_ERROR	(...) ::JZEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define HZ_CORE_CRITICAL(...) ::JZEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
//
//
//// Client log macros
//#define HZ_TRACE		(...) ::JZEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
//#define HZ_INFO			(...) ::JZEngine::Log::GetClientLogger()->info(__VA_ARGS__)
//#define HZ_WARN			(...) ::JZEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
//#define HZ_ERROR		(...) ::JZEngine::Log::GetClientLogger()->error(__VA_ARGS__)
//#define HZ_CRITICAL		(...) ::JZEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
