#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include "../EngineConfig.h"

namespace JZEngine
{
	struct PerformanceData
	{
		struct Timer
		{
			std::chrono::steady_clock::time_point start_time_;
			std::chrono::steady_clock::time_point end_time_;
			float delta_time_;
			float accumulated_delta_time_;
		};

		static unsigned long long frame_count;

		static double actual_time_per_frame_;
		static double capped_time_per_frame_;

		static unsigned int actual_fps_;
		static unsigned int capped_fps_;

		static std::unordered_map<std::string, Timer> timers_;

		static void FrameStart();

		static void FrameEnd();

		/*!
		 * @brief ___JZEngine::PerformanceData::StartMark()___
		 * ****************************************************************************************************
		 * Starts the timer for the specified datum.
		 * ****************************************************************************************************
		 * @param name 
		 * : Datum name of timer.
		 * ****************************************************************************************************
		*/
		static void StartMark(const std::string& name);

		/*!
		 * @brief ___JZEngine::PerformanceData::StartMark()___
		 * ****************************************************************************************************
		 * Starts the timer for the specified datum.
		 * ****************************************************************************************************
		 * @param name
		 * : Datum name of timer.
		 * ****************************************************************************************************
		*/
		static void EndMark(const std::string& name);
	};
}