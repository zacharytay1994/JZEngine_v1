#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

#include "../BuildDefinitions.h"
#include "../ECS/ECS.h"
#include "../DebugTools/Log.h"
#include "../Sound/Sound.h"

namespace JZEngine
{
	namespace ECS
	{
		struct Entity;
		struct ECSInstance;
	}
	struct SceneTree;
	struct JZENGINE_API SceneLogic
	{
		typedef void(*fpSceneInit)();
		typedef void(*fpSceneUpdate)(float dt);

		~SceneLogic();
		static SceneLogic& Instance();

		void RegisterSceneInit(const std::string& name, fpSceneInit function);
		void RegisterSceneLogic(const std::string& name, fpSceneUpdate function);
		void UpdateSceneLogic(float dt);
		void InitSceneLogic();
		void BuildEntityMap();
		template <typename T>
		T* GetComponent(const std::string& name, unsigned int id = 0)
		{
			if (!entity_map_ || entity_map_->find(name) == entity_map_->end())
			{
				//Log::Warning("Error", "Trying to get entity [{}] from scene that does not exist", name);
				return nullptr;
			}
			return &((*entity_map_)[name][id])->GetComponentEX<T>();
		}
		ECS::Entity* GetEntity(const std::string& name, unsigned int id = 0);
		void AddPrefab(const std::string& name, const std::string& parent = "default");
		void SetECS(ECS::ECSInstance* ecs);
		void SetSceneTree(SceneTree* sceneTree);
		void SetSoundSystem(SoundSystem* soundsys);
		SoundSystem* GetSoundSystem();
		void PlaySound(const std::string& name);

		void SetCurrentSceneName(const std::string& name);
		void EntityFlagActive(const std::string& name, bool flag, int id = 0);
		int GetTexture(const std::string& name);
		void ChangeScene(const std::string& name);


	private:


		std::string* scene_to_change_to_{ nullptr };
		bool scene_to_be_changed_{ false };
		ECS::ECSInstance* ecs_instance_{ nullptr };
		SceneTree* scene_tree_{ nullptr };
		SoundSystem* soundsys{ nullptr };
		std::unordered_map<std::string, fpSceneInit>* scene_inits_{ nullptr };
		std::unordered_map<std::string, fpSceneUpdate>* scene_updates_{ nullptr };
		std::unordered_map<std::string, std::vector<ECS::Entity*>>* entity_map_{ nullptr };
		std::string* current_scene_name_{ nullptr };

		SceneLogic();
	};
}