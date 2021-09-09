/*	__FILE HEADER__
*	File:	Log.cpp
    Author: JZ
    Date:	01/09/21
    Brief:	Logging functionality. Uses spdlog.
*/

#include "PCH.h"
#include "Log.h" 

#include <filesystem>

#include "../EngineConfig.h"
#include "../EngineGUI/Console.h"

namespace JZEngine
{
    bool Log::initialized_{ false };

	Log::Log()
	{
        osloggers_ = new std::unordered_map<std::string, OSLogger>();

        // create the log directory if it isn't there
        if (std::filesystem::is_directory(Settings::logs_directory))
        {
            std::filesystem::create_directory(Settings::logs_directory);
        }   
	}

    Log::~Log()
    {
    }

    void Log::Free()
    {
        delete osloggers_;
        spdlog::shutdown();
    }

    Log::OSLogger::OSLogger(const std::string& name)
    {
        if (!name.empty())
        {
            name_ = name;
            file_logger_ = spdlog::basic_logger_mt(name, "Logs/" + name + ".txt");
            os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss_);
            logger_ = std::make_shared<spdlog::logger>(name_, os_sink_);
            stripped_os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(stripped_oss_);
            stripped_logger_ = std::make_shared<spdlog::logger>(name_, stripped_os_sink_);

            // Sets the logging pattern for informative text
            logger_->set_pattern("[ %-8l ] %-64v [ Time Elapsed: %-3i]");

            // Sets the logging pattern for raw text
            stripped_logger_->set_pattern("%v");

            // ImGui filter
            lineoffset_.push_back(0);
            stripped_lineoffset_.push_back(0);

            // Set the logging pattern to default for file logger
            file_logger_->flush_on(spdlog::level::debug);
            file_logger_->set_pattern("%v");
            file_logger_->info("___________________________________________________________________________________________________");
            file_logger_->set_pattern("%+");
        }
    }

    void Log::OSLogger::Initialize(const std::string& name)
    {
        name_ = name;
        file_logger_ = spdlog::basic_logger_mt(name, "Logs/" + name + ".txt");
        os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss_);
        logger_ = std::make_shared<spdlog::logger>(name_, os_sink_);
        stripped_os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(stripped_oss_);
        stripped_logger_ = std::make_shared<spdlog::logger>(name_, stripped_os_sink_);

        // Sets the logging pattern for informative text
        logger_->set_pattern("[ %-8l ] %-64v [ Time Elapsed: %-3i]");

        // Sets the logging pattern for raw text
        stripped_logger_->set_pattern("%v");

        // ImGui filter
        lineoffset_.push_back(0);
        stripped_lineoffset_.push_back(0);

        // Set the logging pattern to default for file logger
        file_logger_->flush_on(spdlog::level::debug);
        file_logger_->set_pattern("%v");
        file_logger_->info("___________________________________________________________________________________________________");
        file_logger_->set_pattern("%+");
    }

    Log& Log::Instance()
    {
        static Log instance;
        return instance;
    }

    void Log::Initialize(Console* console)
    {
        console_ = console;
        initialized_ = true;
    }

    /*!
     * @brief ___JZEngine::Log::GetOSLogger()___
     * ****************************************************************************************************
     * Gets the OSLogger instance specified by name.
     * ****************************************************************************************************
     * @param name
     * : Name of the OSLogger.
     * @return OSLogger&
     * : Reference to the OSLogger.
     * ****************************************************************************************************
    */
    Log::OSLogger& Log::GetOSLogger(const std::string& name)
    {
        if (console_)
        {
            // if ImGui console exists, else creates it
            console_->ExistConsoleLog(name);
        }

        // return OSLogger if it exists
        auto iterator = osloggers_->find(name);
        if (iterator != osloggers_->end())
        {
            return iterator->second;
        }

        // else create it and return it
        (*osloggers_)[name].Initialize(name);
        return (*osloggers_)[name];
    }

    /*!
     * @brief ___JZEngine::Log::GetLogLineCount()___
     * ****************************************************************************************************
     * Increments the line count of the OSLogger and returns the count.
     * For appending line numbers in front of the log msg.
     * ****************************************************************************************************
     * @param name
     * : The name of the OSLogger.
     * @return
     * : Line count.
     * ****************************************************************************************************
    */
    unsigned int Log::GetLogLineCount(const std::string& name)
    {
        return ++GetOSLogger(name).line_count_;
    }
}