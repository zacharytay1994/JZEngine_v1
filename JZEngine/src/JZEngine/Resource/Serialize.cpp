#include <PCH.h>

#include "Serialize.h"
#include "../ECS/ECS.h"
#include "../EngineConfig.h"

namespace JZEngine
{
	bool Serialize::SerializeEntity(ECS::Entity& entity)
	{
		// create the log directory if it isn't there
		if (!std::filesystem::is_directory(Settings::obj_directory))
		{
			std::filesystem::create_directory(Settings::obj_directory);
		}

		auto& mask = entity.owning_chunk_->owning_archetype_->mask_;

		// open file
		std::stringstream ss;
		ss << Settings::obj_directory << entity.name_ << ".txt";
		std::ofstream file;
		file.open(ss.str());
		if (!file.is_open())
		{
			return false;
		}
		else
		{
			// write components
			for (int i = 0; i < mask.size(); ++i)
			{
				// if has that component
				if (mask[i])
				{
					file << "c " << i << " ";
					SerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, file);
				}
			}
		}
		file.close();
		return true;
	}

	bool Serialize::DeserializeEntity(ECS::Entity& entity)
	{
		// open file
 		std::stringstream ss;
		ss << Settings::obj_directory << entity.name_ << ".txt";
		std::ifstream file;
		file.open(ss.str());
		if (!file.is_open())
		{
			return false;
		}
		else
		{
			char c;
			while (file >> c)
			{
				switch (c)
				{
				case 'c':
					int i;
					file >> i;
					entity.AddComponent(i);
					break;
				}
			}
			
		}
		file.close();
		return true;
	}
}