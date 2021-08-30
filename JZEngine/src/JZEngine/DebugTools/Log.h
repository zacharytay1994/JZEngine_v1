#pragma once

#include "../BuildDefinitions.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/fmt/ostr.h>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ostream_sink.h"

#include <unordered_map>
#include <string>

namespace JZEngine
{
	class JZENGINE_API Log
	{
	/*public:
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
		static std::shared_ptr<spdlog::logger> s_ClientLogger;*/

		Log();
		~Log();

		struct OSLogger
		{
			OSLogger() = default;
			OSLogger(const std::string& name);
			OSLogger(const OSLogger& logger);
			OSLogger& operator=(const OSLogger& logger);
			std::string name_;
			unsigned int line_count_{ 0 };

			std::shared_ptr<spdlog::sinks::ostream_sink_mt> os_sink_{ nullptr };			/*!< initialized before logger */
			std::shared_ptr<spdlog::logger> logger_{ nullptr };
			std::ostringstream oss_;

			std::shared_ptr<spdlog::sinks::ostream_sink_mt> stripped_os_sink_{ nullptr };	/*!< initialized before logger */
			std::shared_ptr<spdlog::logger> stripped_logger_{ nullptr };
			std::ostringstream stripped_oss_;
		};

		std::unordered_map<std::string, OSLogger>* osloggers_;

	public:
		static Log& Instance();

		OSLogger& GetOSLogger(const std::string& name);
		std::shared_ptr<spdlog::logger> OSLog(const std::string& name);
		unsigned int GetLogLineCount(const std::string& name);

		template<typename...ARGS>
		static void Info(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string i = std::to_string(Instance().GetLogLineCount(name));
			Instance().GetOSLogger(name).logger_->info(i + ". " + msg, args...);
			Instance().GetOSLogger(name).stripped_logger_->info(i + ". " + msg, args...);
		}

		template<typename...ARGS>
		static void Warning(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string i = std::to_string(Instance().GetLogLineCount(name));
			Instance().GetOSLogger(name).logger_->warn(i + ". " + msg, args...);
			Instance().GetOSLogger(name).stripped_logger_->warn(i + ". " + msg, args...);
		}

		template<typename...ARGS>
		static void Error(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string i = std::to_string(Instance().GetLogLineCount(name));
			Instance().GetOSLogger(name).logger_->error(i + ". " + msg, args...);
			Instance().GetOSLogger(name).stripped_logger_->error(i + ". " + msg, args...);
		}

		template<typename...ARGS>
		static void Critical(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string i = std::to_string(Instance().GetLogLineCount(name));
			Instance().GetOSLogger(name).logger_->critical(i + ". " + msg, args...);
			Instance().GetOSLogger(name).stripped_logger_->critical(i + ". " + msg, args...);
		}
	};
}
