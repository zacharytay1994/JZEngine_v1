#include <PCH.h>
#include "SceneLogic.h"
#include "../DebugTools/Log.h"
#include "../ECS/ECS.h"
#include "../Resource/Serialize.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Serialize.h"
#include "../EngineGUI/SceneTree.h"

namespace JZEngine
{
	SceneLogic::SceneLogic()
	{
		scene_to_change_to_ = new std::string("non");
		scene_inits_ = new std::unordered_map<std::string, fpSceneInit>();
		scene_updates_ = new std::unordered_map<std::string, fpSceneUpdate>();
		entity_map_ = new std::unordered_map<std::string, std::vector<ECS::Entity*>>();
		current_scene_name_ = new std::string("non");
	}

	SceneLogic::~SceneLogic()
	{
		if (scene_to_change_to_)
		{
			delete scene_to_change_to_;
		}
		if (scene_inits_)
		{
			delete scene_inits_;
		}
		if (scene_updates_)
		{
			delete scene_updates_;
		}
		if (entity_map_)
		{
			delete entity_map_;
		}
		if (current_scene_name_)
		{
			delete current_scene_name_;
		}
	}

	void SceneLogic::AddPrefab(const std::string& name, const std::string& parent)
	{
		UNREFERENCED_PARAMETER(parent);
		if (ecs_instance_)
		{
			Serialize::LoadEntity(ecs_instance_, name);
		}
	}

	void SceneLogic::SetECS(ECS::ECSInstance* ecs)
	{
		if (ecs_instance_)
		{
			Log::Warning("Main", "Trying to set ecs for SceneLogic again.");
			return;
		}
		else
		{
			ecs_instance_ = ecs;
		}
	}


	void SceneLogic::SetSceneTree(SceneTree* sceneTree)
	{

		if (scene_tree_)
		{
			Log::Warning("Main", "Trying to set scene tree for SceneLogic again.");
			return;
		}
		else
		{
			scene_tree_ = sceneTree;
		}
	}

	void SceneLogic::SetSoundSystem(SoundSystem* ptr)
	{

		if (soundsys)
		{
			Log::Warning("Main", "Trying to set sound system again");
			return;
		}
		else
		{
			soundsys = ptr;
		}
	}

	SoundSystem* SceneLogic::GetSoundSystem()
	{
		return soundsys;
	}

	void SceneLogic::SetCurrentSceneName(const std::string& name)
	{
		if (current_scene_name_)
		{
			*current_scene_name_ = name;
		}
	}

	void SceneLogic::EntityFlagActive(const std::string& name, bool flag, int id)
	{
		if (ECS::Entity* e = GetEntity(name, id))
		{
			e->FlagActive(flag);
		}
	}

	int SceneLogic::GetTexture(const std::string& name)
	{
		return ResourceManager::GetTextureID(name);
	}

	void SceneLogic::ChangeScene(const std::string& name)
	{
		if (Serialize::scenes_.find(name) != Serialize::scenes_.end())
		{
			*scene_to_change_to_ = name;
			scene_to_be_changed_ = true;
		}
	}

	SceneLogic& SceneLogic::Instance()
	{
		static SceneLogic instance;
		return instance;
	}

	void SceneLogic::RegisterSceneInit(const std::string& name, fpSceneInit function)
	{
		if (scene_inits_)
		{
			(*scene_inits_)[name] = function;
		}
	}

	void SceneLogic::RegisterSceneLogic(const std::string& name, fpSceneUpdate function)
	{
		if (scene_updates_)
		{
			(*scene_updates_)[name] = function;
		}
	}

	void SceneLogic::UpdateSceneLogic(float dt)
	{
		if (scene_to_be_changed_)
		{
			scene_to_be_changed_ = false;
			scene_tree_->RemoveAllEntities();
			Serialize::DeserializeScene(ecs_instance_, *scene_to_change_to_);
			*scene_tree_->current_scene_name_ = *scene_to_change_to_;
			SceneLogic::Instance().SetCurrentSceneName(*scene_to_change_to_);
			SceneLogic::Instance().BuildEntityMap();
			SceneLogic::Instance().InitSceneLogic();
		}
		if (scene_updates_ && scene_updates_->find(*current_scene_name_) != scene_updates_->end())
		{
			(*scene_updates_)[*current_scene_name_](dt);
		}
	}

	void SceneLogic::InitSceneLogic()
	{
		if (scene_inits_ && scene_inits_->find(*current_scene_name_) != scene_inits_->end())
		{
			(*scene_inits_)[*current_scene_name_]();
		}
	}

	void SceneLogic::BuildEntityMap()
	{
		if (entity_map_ && ecs_instance_)
		{
			// reset entity map from last frame
			for (auto& v : *entity_map_)
			{
				v.second.clear();
			}
			// reconstruct entity map
			for (auto& e : ecs_instance_->entity_manager_.entities_)
			{
				if (e.entity_id_ != static_cast<ECS::ui32>(-1))
				{
					(*entity_map_)[e.name_].emplace_back(&ecs_instance_->GetEntity(e.entity_id_));
				}
			}
		}
	}

	ECS::Entity* SceneLogic::GetEntity(const std::string& name, unsigned int id)
	{
		if (!entity_map_ || entity_map_->find(name) == entity_map_->end())
		{
			Log::Warning("Main", "Trying to get entity [{}] from scene that does not exist", name);
			return nullptr;
		}
		return (*entity_map_)[name][id];
	}

	/*ECS::Entity& SceneLogic::GetEntity(const std::string& name, unsigned int id)
	{

	}*/
}