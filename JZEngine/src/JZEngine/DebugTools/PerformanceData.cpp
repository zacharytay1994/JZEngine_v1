#include <PCH.h>
#include "PerformanceData.h"

namespace JZEngine
{
	unsigned long long PerformanceData::frame_count{ 0 };

	double PerformanceData::actual_time_per_frame_;
	double PerformanceData::capped_time_per_frame_;

	unsigned int PerformanceData::actual_fps_;
	unsigned int PerformanceData::capped_fps_;

	std::unordered_map<std::string, PerformanceData::Timer> PerformanceData::timers_;

	void PerformanceData::FrameStart()
	{
	}

	void PerformanceData::FrameEnd()
	{
		// calculate delta time of all timers
		for (auto& t : timers_)
		{
			t.second.delta_time_ = std::chrono::duration<float, std::milli>(t.second.end_time_ - t.second.start_time_).count() / 1000.0f;
		}
		++frame_count;
	}

	void PerformanceData::StartMark(const std::string& name)
	{
		timers_[name].start_time_ = std::chrono::high_resolution_clock::now();
	}

	void PerformanceData::EndMark(const std::string& name)
	{
		timers_[name].end_time_ = std::chrono::high_resolution_clock::now();
	}
}