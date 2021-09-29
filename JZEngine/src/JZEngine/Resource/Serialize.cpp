#include <PCH.h>

#include "Serialize.h"
#include "../ECS/ECS.h"
#include "../EngineConfig.h"
#include "../DebugTools/Log.h"

namespace JZEngine
{
	std::unordered_map<std::string, std::string> Serialize::entities_;
	std::vector<std::string> Serialize::scenes_;

	void Serialize::Load()
	{
		// open config file and load all entity names in it
		std::ifstream config(Settings::saves_config);
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
		Log::Info("Serialize", "- Serialized resources finished loading.");

		ListAllSceneFiles();
	}

	void Serialize::Save()
	{
		// open config file and save all entity names in it
		std::ofstream config(Settings::saves_config);
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
		}
	}

	bool Serialize::SerializeEntity(ECS::Entity& entity)
	{
		// create the saves directory if it isn't there
		if (!std::filesystem::is_directory(Settings::saves_directory))
		{
			std::filesystem::create_directory(Settings::saves_directory);
		}

		Log::Info("Serialize", "\nTrying to serialize {}.", entity.name_);

		auto& mask = entity.owning_chunk_->owning_archetype_->mask_;

		std::stringstream ss;
		ss << Settings::saves_directory << entity.name_ << ".txt";
		// create file
		std::ofstream openfile(ss.str());
		if (openfile.is_open())
		{
			openfile.close();
		}
		// open file
		std::fstream file;
		file.open(ss.str());
		if (!file.is_open())
		{
			Log::Info("Serialize", "- Unable to open {}, to serialize {}", ss.str(), entity.name_);
			return false;
		}
		else
		{
			std::stringstream ss;
			// write components
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
			file.close();

			entities_[entity.name_] = ss.str();

			Log::Info("Serialize", "- Successfully serialized entity {} as {}.", entity.name_, entity.name_);
		}
		return true;
	}

	//bool Serialize::DeserializeEntity(ECS::Entity& entity, const std::string& name)
	//{
	//	// open file
 //		std::stringstream ss;
	//	ss << Settings::saves_directory << name << ".txt";
	//	std::fstream file;
	//	file.open(ss.str());
	//	if (!file.is_open())
	//	{
	//		return false;
	//	}
	//	else
	//	{
	//		std::stringstream ss;
	//		ss << file.rdbuf();
	//		file.close();
	//		char c;
	//		while (ss >> c)
	//		{
	//			switch (c)
	//			{
	//			case 'c':
	//				int i;
	//				ss >> i;
	//				entity.AddComponent(i);
	//				DeSerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, ss);
	//				break;
	//			}
	//		}
	//	}
	//	return true;
	//}

	bool Serialize::LoadEntity(ECS::Entity& entity, const std::string& name)
	{
		if (entities_.find(name) == entities_.end())
		{
			Log::Warning("Serialize", "Tried to load entity {} that does not exist into {}.", name, entity.name_);
			return false;
		}
		std::stringstream ss;
		ss << entities_[name];

		char c;
		while (ss >> c)
		{
			switch (c)
			{
			case 'c':
				int i;
				ss >> i;
				entity.AddComponent(i);
				DeSerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, ss);
				break;
			}
		}
		return true;
	}

	bool Serialize::DeserializeEntityFromFile(const std::string& name)
	{
		// open file
		std::stringstream ss;
		ss << Settings::saves_directory << name << ".txt";
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
		ss << Settings::saves_directory << Settings::scenes_dir;
		Log::Info("Serialize", "\nReading scenes from {}", ss.str());
		std::string path;
		std::string scene_name;
		size_t dash;
		for (const auto& file : std::filesystem::directory_iterator(ss.str()))
		{
			path = file.path().string();
			dash = path.find_last_of('/');
			scene_name = path.substr(dash+1, path.find_last_of('.') - dash - 1);
			scenes_.push_back(scene_name);
			Log::Info("Serialize", "- [{}] read.", scene_name);
		}
	}

	void Serialize::DeSerializeAllChildEntities(ECS::ECSInstance* ecs, std::ifstream& file, std::stringstream& ss, unsigned int parent)
	{
		// read line of file
		// if no parent
		int id;
		if (parent == -1)
		{
			id = ecs->CreateEntity();
		}
		else // else create with parent
		{
			id = ecs->CreateEntity(parent);
		}
		ECS::Entity& entity = ecs->entity_manager_.GetEntity(id);
		// read data and load entity
		ss >> entity.name_;
		int children;
		ss >> children;

		// deserialize all components
		char c;
		while (ss >> c)
		{
			switch (c)
			{
			case 'c':
				int i;
				ss >> i;
				entity.AddComponent(i);
				DeSerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, ss);
				break;
			}
		}

		// deserialize all children
		for (int i = 0; i < children; ++i)
		{
			std::string line;
			std::getline(file, line);
			std::stringstream next_ss;
			next_ss << line;
			DeSerializeAllChildEntities(ecs, file, next_ss, id);
		}
	}

	void Serialize::DeserializeScene(ECS::ECSInstance* ecs, const std::string& name)
	{
		// open file
		std::stringstream ss;
		ss << Settings::saves_directory << Settings::scenes_dir << name << ".txt";
		std::ifstream file(ss.str());

		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss;
			ss << line;
			DeSerializeAllChildEntities(ecs, file, ss);
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
		// for all its children call this serialize and increment number
		/*int number_of_children{ 0 }; 
		for (auto& child : entity.children_)
		{
			if (child != -1)
			{
				++number_of_children;
			}
		}*/
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
		ss << Settings::saves_directory << Settings::scenes_dir;

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
				if (id != -1)
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
	}
}