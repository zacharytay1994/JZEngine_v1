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
			pools_[prefab].pool_.emplace_back(Serialize::LoadEntity(ecs, prefab));
			ECS::Entity& e = ecs->GetEntity(pools_[prefab].pool_.back());
			e.FlagActive(false);
			e.persistant_ = persistant;
			pools_[prefab].free_pool_slots_.push_back(static_cast<int>(pools_[prefab].pool_.size()-1));
		}
	}

	int ObjectPool::ActivateEntity(ECS::ECSInstance* ecs, const std::string& prefab)
	{
		JZ_ASSERT(pools_.find(prefab) != pools_.end(), "Trying to create pool entity not in pool.")(prefab);
		if (pools_[prefab].free_pool_slots_.size() > 0)
		{
			int id = pools_[prefab].free_pool_slots_.back();
			pools_[prefab].free_pool_slots_.pop_back();
			ecs->GetEntity(id).FlagActive(true);
			return id;
		}
		// expand pool
		Log::Warning("Main", "Not enough objects in pool {}. Expanding.", prefab);
		CreatePool(ecs, prefab, static_cast<unsigned int>(pools_[prefab].pool_.size() * 0.5f));
		return ActivateEntity(ecs, prefab);
		//return pools_[prefab].pool_[0];
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
}