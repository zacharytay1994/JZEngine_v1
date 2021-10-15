/*	__FILE HEADER__
*	File:		Serialize.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Serializes components.
*/

#include <PCH.h>

#include "Serialize.h"
#include "../ECS/ECS.h"
#include "../EngineConfig.h"
#include "../DebugTools/Log.h"

namespace JZEngine
{
	std::unordered_map<std::string, std::string> Serialize::entities_;
	std::unordered_map<std::string, bool> Serialize::scenes_;

	void Serialize::Load()
	{
		// create save folder
		if (!std::filesystem::is_directory(Settings::saves_directory))
		{
			std::filesystem::create_directory(Settings::saves_directory);
		}
		// open config file and load all entity names in it
		/*std::ifstream config(Settings::saves_config);
		if (config.is_open())
		{
			Log::Info("Serialize", "\nLoading the following resources:");
			std::string line;
			while (std::getline(config, line))
			{
				if (DeserializeEntityFromFile(line))
				{
					Log::Info("Serialize", "- [Success] {}", line);
				}
				else
				{
					Log::Info("Serialize", "- [Failed] {}", line);
				}
			}
		}
		else
		{
			Log::Error("Serialize", "Unable to open and load saves from config file.");
			return;
		}
		Log::Info("Serialize", "- Serialized resources finished loading.");*/
		ListAllPrefabFiles();
		ListAllSceneFiles();
	}

	void Serialize::Save()
	{
		// open config file and save all entity names in it
		/*std::ofstream config(Settings::saves_config);
		if (config.is_open())
		{
			for (auto& entity : entities_)
			{
				config << entity.first << '\n';
			}
			config.close();
		}
		else
		{
			Log::Error("Serialize", "Unable to open and save to config file.");
		}*/
	}



	bool Serialize::SerializeEntity(ECS::ECSInstance* ecs, ECS::Entity& entity)
	{
		// create the saves directory if it isn't there
		std::stringstream folder_path;
		folder_path << Settings::saves_directory << Settings::prefabs_directory;
		if (!std::filesystem::is_directory(folder_path.str()))
		{
			std::filesystem::create_directory(folder_path.str());
		}

		Log::Info("Serialize", "\nTrying to serialize {}.", entity.name_);

		/*std::stringstream ss;
		ss << Settings::saves_directory << Settings::prefabs_dir << entity.name_ << ".txt";*/
		folder_path << entity.name_ << ".txt";
		// create file
		std::ofstream openfile(folder_path.str());
		if (openfile.is_open())
		{
			openfile.close();
		}
		// open file
		std::ofstream file;
		file.open(folder_path.str());
		if (!file.is_open())
		{
			Log::Info("Serialize", "- Unable to open {}, to serialize {}", folder_path.str(), entity.name_);
			return false;
		}
		else
		{
			SerializeAllChildEntities(ecs, file, entity);
			file.close();
			Log::Info("Serialize", "- Successfully serialized entity {} as {}.", entity.name_, entity.name_);
			DeserializeEntityFromFile(entity.name_);
		}
		return true;
	}

	int Serialize::LoadEntity(ECS::ECSInstance* ecs, const std::string& name)
	{
		if (entities_.find(name) == entities_.end())
		{
			Log::Warning("Serialize", "Tried to load entity {} that does not exist.", name);
			return -1;
		}
		std::stringstream file;
		std::stringstream ss;
		file << entities_[name];
		std::string line;
		std::getline(file, line);
		ss << line;
		return DeSerializeAllChildEntities(ecs, file, ss);
	}

	bool Serialize::DeserializeEntityFromFile(const std::string& name)
	{
		// open file
		std::stringstream ss;
		ss << Settings::saves_directory << Settings::prefabs_directory << name << ".txt";
		std::fstream file(ss.str());
		if (file.is_open())
		{
			ss.str("");
			ss << file.rdbuf();
			entities_[name] = ss.str();
			file.close();
		}
		else
		{
			Log::Warning("Serialize", "- Trying to load entity [{}] from file [{}] that does not exist", name, ss.str());
			return false;
		}
		return true;
	}

	void Serialize::ListAllSceneFiles()
	{
		std::stringstream ss;
		ss << Settings::saves_directory << Settings::scenes_directory;
		// create the log directory if it isn't there
		if (!std::filesystem::is_directory(ss.str()))
		{
			std::filesystem::create_directory(ss.str());
		}
		Log::Info("Serialize", "\nReading scenes from {}", ss.str());
		std::string path;
		std::string scene_name;
		size_t dash;
		for (const auto& file : std::filesystem::directory_iterator(ss.str()))
		{
			path = file.path().string();
			dash = path.find_last_of('/');
			scene_name = path.substr(dash+1, path.find_last_of('.') - dash - 1);
			scenes_[scene_name];
			Log::Info("Serialize", "- [{}] read.", scene_name);
		}
	}

	void Serialize::DeserializeScene(ECS::ECSInstance* ecs, const std::string& name)
	{
		// open file
		std::stringstream ss;
		ss << Settings::saves_directory << Settings::scenes_directory << name << ".txt";
		std::ifstream file(ss.str());

		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss_line;
			ss_line << line;
			DeSerializeAllChildEntities(ecs, file, ss_line);
		}
		file.close();
	}

	void Serialize::SerializeAllChildEntities(ECS::ECSInstance* ecs, std::ofstream& file, ECS::Entity& entity)
	{
		file << entity.name_ << " " << entity.children_count_ << " ";
		if (entity.owning_chunk_)
		{
			auto& mask = entity.owning_chunk_->owning_archetype_->mask_;
			// serialize all components
			std::stringstream ss;
			for (int i = 0; i < mask.size(); ++i)
			{
				// if has that component
				if (mask[i])
				{
					ss << "c " << i << " ";
					SerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, ss);
				}
			}
			file << ss.str();
		}
		file << '\n';
		for (auto& child : entity.children_)
		{
			if (child != -1)
			{
				SerializeAllChildEntities(ecs, file, ecs->entity_manager_.GetEntity(child));
			}
		}
		return;
	}

	bool Serialize::SerializeScene(ECS::ECSInstance* ecs, const std::string& name)
	{
		// open file
		std::stringstream ss;
		ss << Settings::saves_directory << Settings::scenes_directory;

		// create the log directory if it isn't there
		if (!std::filesystem::is_directory(ss.str()))
		{
			std::filesystem::create_directory(ss.str());
		}

		ss << name << ".txt";
		std::ofstream file(ss.str());

		if (file.is_open())
		{
			for (auto& id : ecs->entity_manager_.root_ids_)
			{
				if (id != -1 && ecs->entity_manager_.GetEntity(id).persistant_)
				{
					// count number of children
					// recursively render all children of a root entity
					ECS::Entity& entity = ecs->entity_manager_.GetEntity(id);
					SerializeAllChildEntities(ecs, file, entity);
				}
			}
			file.close();
		}
		else
		{
			Log::Error("Serialize", "Unable to open {} to save Scene [{}].", ss.str(), name);
			return false;
		}
		return true;
	}

	void Serialize::ListAllPrefabFiles()
	{
		std::stringstream ss;
		ss << Settings::saves_directory << Settings::prefabs_directory;
		// create the log directory if it isn't there
		if (!std::filesystem::is_directory(ss.str()))
		{
			std::filesystem::create_directory(ss.str());
		}
		Log::Info("Serialize", "\nReading prefabs from {}", ss.str());
		std::string path;
		std::string prefab_name;
		size_t dash;
		for (const auto& file : std::filesystem::directory_iterator(ss.str()))
		{
			path = file.path().string();
			dash = path.find_last_of('/');
			prefab_name = path.substr(dash + 1, path.find_last_of('.') - dash - 1);
			if (DeserializeEntityFromFile(prefab_name))
			{
				Log::Info("Serialize", "- [Success] {}", prefab_name);
			}
			else
			{
				Log::Info("Serialize", "- [Failed] {}", prefab_name);
			}
		}
	}
}