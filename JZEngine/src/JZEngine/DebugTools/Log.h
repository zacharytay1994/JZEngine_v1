/*	__FILE HEADER__
*	File:	Log.h
	Author: JZ
	Date:	01/09/21
	Brief:	Logging functionality. Uses spdlog.
*/

#pragma once

#include "../BuildDefinitions.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/fmt/ostr.h>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ostream_sink.h"

#include <unordered_map>
#include <string>
#include <sstream>

namespace JZEngine
{
	struct Console;
	/*!
	 * @brief ___JZEngine::Log___
	 * ****************************************************************************************************
	 * The logging class of the engine. Uses spdlog to log to
	 * ostringstream and file.
	 * ****************************************************************************************************
	*/
	struct JZENGINE_API Log
	{
		~Log();

		/*!
		 * @brief ___JZEngine::Log::OSLogger___
		 * ****************************************************************************************************
		 * Encapsulates all spdlog objects needed to log
		 * to ostringstream and files.
		 * ****************************************************************************************************
		*/
		struct OSLogger
		{
			OSLogger(const std::string& name = "");
			//OSLogger& operator=(const OSLogger& logger);

			void Initialize(const std::string& name);

			std::string					name_;												/*!< name of the console/file to log to */
			unsigned int				line_count_{ 0 };									/*!< line count */
			std::vector<unsigned int>	lineoffset_;										/*!< size per line, for ImGui console filter */
			std::vector<unsigned int>	stripped_lineoffset_;								/*!< size per line, for ImGui console filter */

			std::shared_ptr<spdlog::logger>					file_logger_{ nullptr };		/*!< logger used to log to file */

			std::shared_ptr<spdlog::sinks::ostream_sink_mt> os_sink_{ nullptr };			/*!< initialized before logger */
			std::shared_ptr<spdlog::logger>					logger_{ nullptr };				/*!< logger to log info packed text to oss */
			std::ostringstream								oss_;							/*!< log data */

			std::shared_ptr<spdlog::sinks::ostream_sink_mt> stripped_os_sink_{ nullptr };	/*!< initialized before logger */
			std::shared_ptr<spdlog::logger>					stripped_logger_{ nullptr };	/*!< logger to log info stripped text to oss, i.e. raw text */
			std::ostringstream								stripped_oss_;					/*!< log data */
		};

		/*!
		 * @brief ___JZEngine::Log::Instance()___
		 * ****************************************************************************************************
		 * Singleton instance.
		 * ****************************************************************************************************
		 * @return 
		 * : Singleton instance.
		*/
		static Log& Instance();

		void Initialize(Console* console);

		void Free();

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
		OSLogger& GetOSLogger(const std::string& name);

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
		unsigned int GetLogLineCount(const std::string& name);

		/*!
		 * @brief ___JZEngine::Log::Info()___
		 * ****************************************************************************************************
		 * Static function to wrapping spdlog::logger->info(),
		 * of a specified OSLogger specified by name.
		 * Also calculates size per line logged.
		 * ****************************************************************************************************
		 * @tparam ...ARGS 
		 * : spdlog args...
		 * @param name 
		 * : Name of the OSLogger to write to.
		 * @param msg 
		 * : The msg to log.
		 * @param ...args 
		 * : spdlog args...
		 * ****************************************************************************************************
		*/
		template<typename...ARGS>
		static void Info(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			if (!initialized_)
			{
				return;
			}

			// for the msg with the line number
			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			// logs to file
			logger.file_logger_->info(msg, args...);

			// calculate line size and log to stream
			auto initial_pos = logger.oss_.tellp();
			logger.logger_->info(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			// calculate line size and log to stream
			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->info(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}


		/*!
		 * @brief ___JZEngine::Log::Warn()___
		 * ****************************************************************************************************
		 * Static function to wrapping spdlog::logger->Warn(),
		 * of a specified OSLogger specified by name.
		 * Also calculates size per line logged.
		 * ****************************************************************************************************
		 * @tparam ...ARGS
		 * : spdlog args...
		 * @param name
		 * : Name of the OSLogger to write to.
		 * @param msg
		 * : The msg to log.
		 * @param ...args
		 * : spdlog args...
		 * ****************************************************************************************************
		*/
		template<typename...ARGS>
		static void Warning(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			if (!initialized_)
			{
				return;
			}

			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->warn(msg, args...);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->warn(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->warn(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}


		/*!
		 * @brief ___JZEngine::Log::Error()___
		 * ****************************************************************************************************
		 * Static function to wrapping spdlog::logger->error(),
		 * of a specified OSLogger specified by name.
		 * Also calculates size per line logged.
		 * ****************************************************************************************************
		 * @tparam ...ARGS
		 * : spdlog args...
		 * @param name
		 * : Name of the OSLogger to write to.
		 * @param msg
		 * : The msg to log.
		 * @param ...args
		 * : spdlog args...
		 * ****************************************************************************************************
		*/
		template<typename...ARGS>
		static void Error(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			if (!initialized_)
			{
				return;
			}

			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->error(msg, args...);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->error(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->error(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}


		/*!
		 * @brief ___JZEngine::Log::Critical()___
		 * ****************************************************************************************************
		 * Static function to wrapping spdlog::logger->critical(),
		 * of a specified OSLogger specified by name.
		 * Also calculates size per line logged.
		 * ****************************************************************************************************
		 * @tparam ...ARGS
		 * : spdlog args...
		 * @param name
		 * : Name of the OSLogger to write to.
		 * @param msg
		 * : The msg to log.
		 * @param ...args
		 * : spdlog args...
		 * ****************************************************************************************************
		*/
		template<typename...ARGS>
		static void Critical(const std::string& name, const std::string& msg, ARGS&&... args)
		{
			if (!initialized_)
			{
				return;
			}

			std::string s = std::to_string(Instance().GetLogLineCount(name)) + ". " + msg;
			OSLogger& logger = Instance().GetOSLogger(name);

			logger.file_logger_->critical(msg, args...);

			auto initial_pos = logger.oss_.tellp();
			logger.logger_->critical(s, args...);
			logger.lineoffset_.push_back(logger.lineoffset_.back() + static_cast<unsigned int>(logger.oss_.tellp() - initial_pos));

			initial_pos = logger.stripped_oss_.tellp();
			logger.stripped_logger_->critical(s, args...);
			logger.stripped_lineoffset_.push_back(logger.stripped_lineoffset_.back() + static_cast<unsigned int>(logger.stripped_oss_.tellp() - initial_pos));
		}

	private:
		static bool initialized_;
		Console* console_{ nullptr };
		std::unordered_map<std::string, OSLogger>* osloggers_;	/*!< all the OSLogger instances mapped by name */
		Log();
	};
}
