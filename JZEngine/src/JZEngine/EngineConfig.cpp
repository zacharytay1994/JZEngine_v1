/*	__FILE HEADER__
*	File:		EngineCofig.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Engine settings.
*/

#include <PCH.h>
#include "EngineConfig.h"
#include "JZGL/JZ_GL.h"

namespace JZEngine
{
	std::string		Settings::engine_name{ "Jump Zero Engine" };
	float			Settings::version{ 1.0 };
	int				Settings::window_x{ 100 };
	int				Settings::window_y{ 100 };
	int				Settings::camera_width{ 1920 };
	int				Settings::camera_height{ 1080 };
	int				Settings::original_camera_width { 1920 };
	int				Settings::original_camera_height { 1080 };
	unsigned int	Settings::window_width{ 1600 };
	unsigned int	Settings::window_height{ 900 };
	float			Settings::aspect_ratio;
	unsigned int	Settings::max_fps{ 60 };
	double			Settings::min_tpf;
	std::string		Settings::logs_directory{ "Logs/" };
	std::string		Settings::saves_directory{ "Saves/" };
	std::string		Settings::scenes_directory{ "Scenes/" };
	std::string		Settings::prefabs_directory{ "Prefabs/" };

	void Settings::LoadFromConfigFile()
	{
		std::string folder_path = "Saves/";
		std::string config_file = "config.txt";
		// create config folder
		if (!std::filesystem::is_directory(folder_path))
		{
			std::filesystem::create_directory(folder_path);
		}

		std::stringstream ss;
		ss << folder_path << config_file;

		// try to open file, if no file exists create it
		std::fstream file(ss.str(), std::ios::in);
		if (file.is_open())
		{
			// read all variables inside
			file >> version;
			file >> window_x;
			file >> window_y;
			file >> window_width;
			file >> window_height;
			file >> max_fps;
			file >> logs_directory;
			file >> saves_directory;
			//file >> saves_config;
			file >> scenes_directory;
			file >> prefabs_directory;
		}
		min_tpf = 1.0 / static_cast<double>(max_fps);
		aspect_ratio = static_cast<float>(window_height) / static_cast<float>(window_width);
	}

	void Settings::SaveToConfigFile()
	{
		if ( !Settings::GAME_BUILD )
		{
			std::string folder_path = "Saves/";
			std::string config_file = "config.txt";
			// create config folder
			if ( !std::filesystem::is_directory ( folder_path ) )
			{
				std::filesystem::create_directory ( folder_path );
			}

			std::stringstream ss;
			ss << folder_path << config_file;

			// try to open file, if no file exists create it
			std::fstream file ( ss.str () , std::ios::out );

			if ( file.is_open () )
			{
				GLFW_Instance::GetWindowPos ( window_x , window_y );

				// write all variables inside
				file << version << "\n";
				file << window_x << "\n";
				file << window_y << "\n";
				file << window_width << "\n";
				file << window_height << "\n";
				file << max_fps << "\n";
				file << logs_directory << "\n";
				file << saves_directory << "\n";
				//file << saves_config << "\n";
				file << scenes_directory << "\n";
				file << prefabs_directory << "\n";
			}
		}
	}
}