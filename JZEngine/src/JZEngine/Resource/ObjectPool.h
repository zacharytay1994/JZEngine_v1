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
	}
	struct ObjectPool
	{
		static void		CreatePool(ECS::ECSInstance* ecs, const std::string& prefab, unsigned int count, bool persistant = false);
		static int		ActivateEntity(ECS::ECSInstance* ecs, const std::string& prefab);
		static void		FrameEnd(ECS::ECSInstance* ecs);
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