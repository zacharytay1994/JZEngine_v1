
#include "PCH.h"
#include "Log.h" 

//std::shared_ptr <spdlog::logger> JZEngine::Log::s_ClientLogger;
//std::shared_ptr<spdlog::logger> JZEngine::Log::s_CoreLogger;
#include "../EngineGUI/Console.h"

namespace JZEngine
{
		
	//void Log::Init ()
	//{

	//	// change log pattern
	//	spdlog::set_pattern ( "%^[%T] %n: %v%$" );

	//	s_CoreLogger = spdlog::stdout_color_mt ( "JZEngine" );
	//	s_CoreLogger->set_level ( spdlog::level::trace );

	//	s_ClientLogger = spdlog::stdout_color_mt ( "App" );
	//	s_ClientLogger->set_level ( spdlog::level::trace );
	//}
	Log::Log()
	{
        osloggers_ = new std::unordered_map<std::string, OSLogger>();
        spdlog::info("Welcome to spdlog!");
        spdlog::error("Some error message with arg: {}", 1);

        spdlog::warn("Easy padding in numbers like {:08d}", 12);
        spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        spdlog::info("Support for floats {:03.2f}", 1.23456);
        spdlog::info("Positional args are {1} {0}..", "too", "supported");
        spdlog::info("{:<30}", "left aligned");

        spdlog::set_level(spdlog::level::debug); // Set global log level to debug
        spdlog::debug("This message should be displayed..");

        // change log pattern
        spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

        /*try
        {
            auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
            my_logger->critical("something");
        }
        catch (const spdlog::spdlog_ex& ex) {
            std::cout << "log failed" << ex.what() << std::endl;
        }*/
        /*std::ostringstream oss;
        auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss);
        auto logger = std::make_shared<spdlog::logger>("my_logger", ostream_sink);
        logger->info("test ostream logger");
        std::cout << oss.str() << std::endl;*/
        for (int i = 0; i < 200; ++i)
        {
            OSLog("Console")->info("test os logger {}", i);
        }

        // Compile time log levels
        // define SPDLOG_ACTIVE_LEVEL to desired level
        SPDLOG_TRACE("Some trace message with param {}", 42);
        SPDLOG_DEBUG("Some debug message");
	}

    Log::~Log()
    {
        delete osloggers_;
    }

    Log::OSLogger::OSLogger(const std::string& name)
        :
        name_(name),
        os_sink_(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss)),
        logger_(std::make_shared<spdlog::logger>(name_, os_sink_))
    {

    }

    Log::OSLogger::OSLogger(const OSLogger& logger)
        :
        name_(logger.name_),
        os_sink_(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss)),
        logger_(std::make_shared<spdlog::logger>(name_, os_sink_))
    {

    }

    Log::OSLogger& Log::OSLogger::operator=(const OSLogger& logger)
    {
        name_ = logger.name_;
        os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss);
        logger_ = std::make_shared<spdlog::logger>(name_, os_sink_);
        return *this;
    }

    Log& Log::Instance()
    {
        static Log instance;
        return instance;
    }

    Log::OSLogger& Log::GetOSLogger(const std::string& name)
    {
        if (osloggers_->find(name) == osloggers_->end())
        {
            (*osloggers_)[name] = OSLogger(name);
        }
        return (*osloggers_)[name];
    }

    std::shared_ptr<spdlog::logger>& Log::OSLog(const std::string& name)
    {
        return GetOSLogger(name).logger_;
    }
}