#pragma once

namespace JZEngine
{
	/*namespace Settings
	{
		constexpr const char*		engine_name		= "Jump Zero Engine";
		constexpr const double		version			= 1.0;
		constexpr unsigned int		window_width	= 1600;
		constexpr unsigned int		window_height	= 900;
		constexpr float				aspect_ratio	= static_cast<float>(window_width) / static_cast<float>(window_height);

		constexpr const int			max_fps			= 60;
		constexpr const double		min_tpf			= 1.0 / static_cast<double>(max_fps);

		constexpr const char*		logs_directory	= "Logs/";
		constexpr const char*		saves_directory	= "Saves/";
		constexpr const char*		saves_config	= "Saves/config.txt";
		constexpr const char*		scenes_dir		= "Scenes/";
		constexpr const char*		prefabs_dir		= "Prefabs/";
	}*/

	struct Settings
	{
		static std::string	engine_name;
		static float		version;
		static unsigned int	window_width;
		static unsigned int	window_height;
		static float		aspect_ratio;
		static unsigned int	max_fps;
		static double		min_tpf;

		static std::string logs_directory;
		static std::string saves_directory;
		//static std::string saves_config;
		static std::string scenes_directory;
		static std::string prefabs_directory;

		static void LoadFromConfigFile();
		static void SaveToConfigFile();
	};
}