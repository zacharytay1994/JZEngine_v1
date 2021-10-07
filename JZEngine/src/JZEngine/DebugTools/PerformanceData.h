/*	__FILE HEADER__
*	File:		PerformanceData.h
	Primary:	Zachary Tay
	Secondary:
	Date:		07/10/2021
	Brief:
	To visualize the performance of the engine.
*/

#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include "../EngineConfig.h"

namespace JZEngine
{
	struct PerformanceData
	{
		enum class TimerType
		{
			DEFAULT,
			GLOBAL_SYSTEMS,
			ECS_SYSTEMS,
			OVERALL
		};

		struct Timer
		{
			std::string name_{ "default" };
			std::chrono::steady_clock::time_point start_time_;
			std::chrono::steady_clock::time_point end_time_;
			float delta_time_{ 1.0f };							// in seconds
			float display_delta_time_{ 0.0f };					// 
			float accumulated_delta_time_{ 1.0f };				// in seconds
			float average_delta_time_{ 0.0f };					// in seconds
			float elapsed_time_{ 0.0f };						// in milliseconds
		};

		static float time_quantum_;
		static std::chrono::steady_clock::time_point current_time_;

		static unsigned long long frame_count_;
		static unsigned long long accumulated_frames_;

		static double actual_time_per_frame_;
		static double capped_time_per_frame_;

		static std::chrono::steady_clock::time_point frame_time_;
		static unsigned int actual_fps_;
		static unsigned int capped_fps_;
		static unsigned int accumulated_fps_;
		static unsigned int average_fps_;

		static unsigned int app_fps_;
		static unsigned int average_app_fps_;
		static unsigned int accumulated_app_fps_;

		static std::unordered_map<std::string, Timer> global_system_timers_;
		static std::unordered_map<std::string, Timer> ecs_system_timers_;
		static std::unordered_map<std::string, Timer> default_timers_;

		static void Init(); 

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
		static void StartMark(const std::string& name, TimerType type = TimerType::DEFAULT);

		/*!
		 * @brief ___JZEngine::PerformanceData::StartMark()___
		 * ****************************************************************************************************
		 * Starts the timer for the specified datum.
		 * ****************************************************************************************************
		 * @param name
		 * : Datum name of timer.
		 * ****************************************************************************************************
		*/
		static void EndMark(const std::string& name, TimerType type = TimerType::DEFAULT);
	};
}