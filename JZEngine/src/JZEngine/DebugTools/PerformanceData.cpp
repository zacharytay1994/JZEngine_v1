#include <PCH.h>
#include "PerformanceData.h"

namespace JZEngine
{
	float PerformanceData::time_quantum_{ 1.0f }; 
	std::chrono::steady_clock::time_point PerformanceData::current_time_;

	unsigned long long PerformanceData::frame_count_{ 0 };
	unsigned long long PerformanceData::accumulated_frames_{ 0 };

	double PerformanceData::actual_time_per_frame_;
	double PerformanceData::capped_time_per_frame_;

	std::chrono::steady_clock::time_point PerformanceData::frame_time_;
	unsigned int PerformanceData::actual_fps_;
	unsigned int PerformanceData::capped_fps_;
	unsigned int PerformanceData::accumulated_fps_;
	unsigned int PerformanceData::average_fps_;

	unsigned int PerformanceData::app_fps_;
	unsigned int PerformanceData::average_app_fps_;
	unsigned int PerformanceData::accumulated_app_fps_;

	std::unordered_map<std::string, PerformanceData::Timer> PerformanceData::default_timers_;
	std::unordered_map<std::string, PerformanceData::Timer> PerformanceData::global_system_timers_;
	std::unordered_map<std::string, PerformanceData::Timer> PerformanceData::ecs_system_timers_;

	void PerformanceData::Init()
	{
		current_time_ = std::chrono::high_resolution_clock::now();
	}

	void PerformanceData::FrameStart()
	{
		frame_time_ = std::chrono::high_resolution_clock::now();
	}

	void PerformanceData::FrameEnd()
	{
		actual_time_per_frame_ = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - frame_time_).count() / 1000.0f;
		actual_fps_ = static_cast<unsigned int>(1.0f / actual_time_per_frame_);
		accumulated_app_fps_ += app_fps_;

		// calculate delta time of all timers
		for (auto& t : default_timers_)
		{
			t.second.delta_time_ = t.second.elapsed_time_ / 1000.0f;
			t.second.accumulated_delta_time_ += t.second.delta_time_;
		}
		for (auto& t : global_system_timers_)
		{
			t.second.delta_time_ = t.second.elapsed_time_ / 1000.0f;
			t.second.accumulated_delta_time_ += t.second.delta_time_;
		}
		for (auto& t : ecs_system_timers_)
		{
			t.second.delta_time_ = t.second.elapsed_time_ / 1000.0f;
			t.second.accumulated_delta_time_ += t.second.delta_time_;
		}

		// check if exceed time quantum, i.e. update per quantum
		if (std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - current_time_).count() / 1000.0f > time_quantum_)
		{
			// calculate accumulated delta times
			for (auto& t : default_timers_)
			{
				t.second.average_delta_time_ = t.second.accumulated_delta_time_ / accumulated_frames_;
				t.second.accumulated_delta_time_ = 0.0f;
			}
			for (auto& t : global_system_timers_)
			{
				t.second.average_delta_time_ = t.second.accumulated_delta_time_ / accumulated_frames_;
				t.second.accumulated_delta_time_ = 0.0f;
			}
			for (auto& t : ecs_system_timers_)
			{
				t.second.average_delta_time_ = t.second.accumulated_delta_time_ / accumulated_frames_;
				t.second.accumulated_delta_time_ = 0.0f;
			}

			average_fps_ = accumulated_fps_ / accumulated_frames_;
			average_app_fps_ = accumulated_app_fps_ / accumulated_frames_;

			current_time_ = std::chrono::high_resolution_clock::now();
			accumulated_fps_ = 0;
			accumulated_frames_ = 0;
			accumulated_app_fps_ = 0;
		}

		// reset all marks in preperation for new frame
		for (auto& t : default_timers_)
		{
			t.second.elapsed_time_ = 0.0f;
		}
		for (auto& t : global_system_timers_)
		{
			t.second.elapsed_time_ = 0.0f;
		}
		for (auto& t : ecs_system_timers_)
		{
			t.second.elapsed_time_ = 0.0f;
		}

		++accumulated_frames_;
		++frame_count_;

		// accumulate fps
		accumulated_fps_ += actual_fps_;
	}

	void PerformanceData::StartMark(const std::string& name, TimerType type)
	{
		switch (type)
		{
		case TimerType::DEFAULT:
			default_timers_[name].start_time_ = std::chrono::high_resolution_clock::now();
			break;
		case TimerType::GLOBAL_SYSTEMS:
			global_system_timers_[name].start_time_ = std::chrono::high_resolution_clock::now();
			break;
		case TimerType::ECS_SYSTEMS:
			ecs_system_timers_[name].start_time_ = std::chrono::high_resolution_clock::now();
			break;
		}
	}

	void PerformanceData::EndMark(const std::string& name, TimerType type)
	{
		switch (type)
		{
		case TimerType::DEFAULT:
			default_timers_[name].elapsed_time_ += std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - default_timers_[name].start_time_).count();
			break;
		case TimerType::GLOBAL_SYSTEMS:
			global_system_timers_[name].elapsed_time_ += std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - global_system_timers_[name].start_time_).count();
			break;
		case TimerType::ECS_SYSTEMS:
			ecs_system_timers_[name].elapsed_time_ += std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - ecs_system_timers_[name].start_time_).count();
			break;
		}
	}
}