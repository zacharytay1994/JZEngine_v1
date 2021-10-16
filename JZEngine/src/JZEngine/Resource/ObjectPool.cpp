#include <PCH.h>
#include "ObjectPool.h"
#include "Serialize.h"
#include "../ECS/ECS.h"
#include "../DebugTools/Assert.h"
#include "../DebugTools/Log.h"

namespace JZEngine
{
	std::unordered_map<std::string, ObjectPool::PoolData>  ObjectPool::pools_;

	void ObjectPool::CreatePool(ECS::ECSInstance* ecs, const std::string& prefab, unsigned int count, bool persistant)
	{
		JZ_ASSERT(ecs != nullptr, "Creating Pool before ECSInstance is initialized")(ecs);
		for (int i = 0; i < count; ++i)
		{
			auto& pool_data = pools_[prefab];
			pool_data.pool_.emplace_back(Serialize::LoadEntity(ecs, prefab));
			ECS::Entity& e = ecs->GetEntity(pool_data.pool_.back());
			e.FlagActive(false);
			e.persistant_ = persistant;
			pool_data.free_pool_slots_.push_back(static_cast<int>(pool_data.pool_[pool_data.pool_.size() - 1]));
		}
	}

	int ObjectPool::GetEntity(ECS::ECSInstance* ecs, const std::string& prefab)
	{
		JZ_ASSERT(pools_.find(prefab) != pools_.end(), "Trying to create pool entity not in pool.")(prefab);
		auto& pool_data = pools_[prefab];
		if (pools_[prefab].free_pool_slots_.size() > 0)
		{
			int id = pool_data.free_pool_slots_.back();
			pool_data.free_pool_slots_.pop_back();
			ecs->GetEntity(id).FlagActive(true);
			return id;
		}
		// expand pool
		Log::Warning("Main", "Not enough objects in pool {}. Expanding.", prefab);
		CreatePool(ecs, prefab, static_cast<unsigned int>(pool_data.pool_.size() * 0.5f));
		return GetEntity(ecs, prefab);
	}

	void ObjectPool::FrameEnd(ECS::ECSInstance* ecs)
	{
		// Get all inactive entities and push to their stack
		for (auto& pool : pools_)
		{
			pool.second.free_pool_slots_.clear();
			for (auto& eid : pool.second.pool_)
			{
				// if entity is inactive
				if (!ecs->GetEntity(eid).GetFlag())
				{
					pool.second.free_pool_slots_.emplace_back(eid);
				}
			}
		}
	}

	void ObjectPool::UpdatePool(ECS::ECSInstance* ecs, const std::string& prefab)
	{
		if (pools_.find(prefab) != pools_.end())
		{
			int pool_size = 0;
			// remove all objects from pool
			for (auto& e : pools_[prefab].pool_)
			{
				ecs->RemoveEntity(e);
			}
			pool_size += pools_[prefab].pool_.capacity();
			pools_[prefab].pool_.clear();
			pools_[prefab].free_pool_slots_.clear();
			// recreate pool with updated prefab
			CreatePool(ecs, prefab, pool_size);
		}
	}
}