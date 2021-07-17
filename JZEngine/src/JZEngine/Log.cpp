
#include "PCH.h"
#include "Log.h" 


std::shared_ptr <spdlog::logger> JZEngine::Log::s_ClientLogger;
std::shared_ptr<spdlog::logger> JZEngine::Log::s_CoreLogger;


namespace JZEngine
{
		
	void Log::Init ()
	{

		// change log pattern
		spdlog::set_pattern ( "%^[%T] %n: %v%$" );

		s_CoreLogger = spdlog::stdout_color_mt ( "JZEngine" );
		s_CoreLogger->set_level ( spdlog::level::trace );

		s_ClientLogger = spdlog::stdout_color_mt ( "App" );
		s_ClientLogger->set_level ( spdlog::level::trace );
	}

}