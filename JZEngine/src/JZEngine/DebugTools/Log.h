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
	struct JZENGINE_API Log
	{
		~Log();

		struct OSLogger
		{
			OSLogger() = default;
			OSLogger(const std::string& name);
			OSLogger(const OSLogger& logger);
			OSLogger& operator=(const OSLogger& logger);
			std::string name_;
			unsigned int line_count_{ 0 };
			std::vector<unsigned int> lineoffset_;
			std::vector<unsigned int> stripped_lineoffset_;

			std::shared_ptr<spdlog::logger> file_logger_{ nullptr };

			std::shared_ptr<spdlog::sinks::ostream_sink_mt> os_sink_{ nullptr };			/*!< initialized before logger */
			std::shared_ptr<spdlog::logger> logger_{ nullptr };
			std::ostringstream oss_;

			std::shared_ptr<spdlog::sinks::ostream_sink_mt> stripped_os_sink_{ nullptr };	/*!< initialized before logger */
			std::shared_ptr<spdlog::logger> stripped_logger_{ nullptr };
			std::ostringstream stripped_oss_;
		};

		static Log& Instance();

		OSLogger& GetOSLogger(const std::string& name);
		std::shared_ptr<spdlog::logger> OSLog(const std::string& name);
		unsigned int GetLogLineCount(const std::string& name);

		template<typename...ARGS>
		static void Info(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->info(msg);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->info(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->info(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}

		template<typename...ARGS>
		static void Warning(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->warn(msg);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->warn(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->warn(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}

		template<typename...ARGS>
		static void Error(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->error(msg);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->error(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->error(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}

		template<typename...ARGS>
		static void Critical(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->critical(msg);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->critical(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->critical(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}

	private:
		std::unordered_map<std::string, OSLogger>* osloggers_;
		Log();
	};
}
