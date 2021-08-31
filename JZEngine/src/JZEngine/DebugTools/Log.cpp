
#include "PCH.h"
#include "Log.h" 

#include <filesystem>

#include "../EngineConfig.h"
#include "../EngineGUI/Console.h"

namespace JZEngine
{
	Log::Log()
	{
        osloggers_ = new std::unordered_map<std::string, OSLogger>();

        if (std::filesystem::is_directory(Settings::logs_directory))
        {
            std::filesystem::create_directory(Settings::logs_directory);
        }
	}

    Log::~Log()
    {
        delete osloggers_;
    }

    Log::OSLogger::OSLogger(const std::string& name)
        :
        name_(name),
        file_logger_(spdlog::basic_logger_mt(name, "Logs/" + name + ".txt")),
        os_sink_(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss_)),
        logger_(std::make_shared<spdlog::logger>(name_, os_sink_)),
        stripped_os_sink_(std::make_shared<spdlog::sinks::ostream_sink_mt>(stripped_oss_)),
        stripped_logger_(std::make_shared<spdlog::logger>(name_, stripped_os_sink_))
    {
        logger_->set_pattern("[ %-8l ] %-64v [ Time Elapsed: %-3i]");
        stripped_logger_->set_pattern("%v");
        lineoffset_.push_back(0);
        stripped_lineoffset_.push_back(0);
        file_logger_->set_pattern("%v");
        file_logger_->info("___________________________________________________________________________________________________");
        file_logger_->set_pattern("%+");
    }

    Log::OSLogger::OSLogger(const OSLogger& logger)
        :
        name_(logger.name_),
        file_logger_(logger.file_logger_),
        os_sink_(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss_)),
        logger_(std::make_shared<spdlog::logger>(name_, os_sink_)),
        stripped_os_sink_(std::make_shared<spdlog::sinks::ostream_sink_mt>(stripped_oss_)),
        stripped_logger_(std::make_shared<spdlog::logger>(name_, stripped_os_sink_))
    {
        logger_->set_pattern("[ %-8l ] %-64v [ Time Elapsed: %-3i]");
        stripped_logger_->set_pattern("%v");
        lineoffset_.push_back(0);
        stripped_lineoffset_.push_back(0);
    }

    Log::OSLogger& Log::OSLogger::operator=(const OSLogger& logger)
    {
        name_ = logger.name_;
        file_logger_ = logger.file_logger_;
        os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss_);
        logger_ = std::make_shared<spdlog::logger>(name_, os_sink_);
        stripped_os_sink_ = std::make_shared<spdlog::sinks::ostream_sink_mt>(stripped_oss_);
        stripped_logger_ = std::make_shared<spdlog::logger>(name_, stripped_os_sink_);
        logger_->set_pattern("[ %-8l ] %-64v [ Time Elapsed: %-3i]");
        stripped_logger_->set_pattern("%v");
        lineoffset_.push_back(0);
        stripped_lineoffset_.push_back(0);
        return *this;
    }

    Log& Log::Instance()
    {
        static Log instance;
        return instance;
    }

    Log::OSLogger& Log::GetOSLogger(const std::string& name)
    {
        Console::ExistConsoleLog(name);
        auto iterator = osloggers_->find(name);
        if (iterator != osloggers_->end())
        {
            return iterator->second;
        }
        return (*osloggers_)[name] = OSLogger(name);
    }

    std::shared_ptr<spdlog::logger> Log::OSLog(const std::string& name)
    {
        return GetOSLogger(name).logger_;
    }

    unsigned int Log::GetLogLineCount(const std::string& name)
    {
        return ++GetOSLogger(name).line_count_;
    }
}