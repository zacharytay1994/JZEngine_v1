#pragma once

#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

namespace JZEngine
{
	namespace ECS
	{
		struct ECSInstance;
		struct Entity;
	}
	struct ObjectPool
	{
		static void				CreatePool(ECS::ECSInstance* ecs, const std::string& prefab, unsigned int count, bool persistant = false);
		static ECS::Entity&		GetEntity(ECS::ECSInstance* ecs, const std::string& prefab, bool persistant = false);
		static ECS::Entity&		GetNewEntity(ECS::ECSInstance* ecs, const std::string& prefab, bool persistant = false);
		static void				FrameEnd(ECS::ECSInstance* ecs);
		static void				UpdatePool(ECS::ECSInstance* ecs, const std::string& prefab);

		static int		TotalEntities();
		static int		ActiveEntities();
	private:
		ECS::ECSInstance* ecs_instance_{ nullptr };
		struct PoolData
		{
			std::vector<int> pool_;
			std::vector<int> free_pool_slots_;
		};
		static std::unordered_map<std::string, PoolData> pools_;
	};
}