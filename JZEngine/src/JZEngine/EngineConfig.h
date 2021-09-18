#pragma once

namespace JZEngine
{
	namespace Settings
	{
		constexpr const char*		engine_name		= "Jump Zero Engine";
		constexpr const double		version			= 1.0;
		constexpr unsigned int		window_width	= 1600;
		constexpr unsigned int		window_height	= 900;
		constexpr float				aspect_ratio	= static_cast<float>(window_width) / static_cast<float>(window_height);

		constexpr const char*		logs_directory	= "Log/";
	}
}