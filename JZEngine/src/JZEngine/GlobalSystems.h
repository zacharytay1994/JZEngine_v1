#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <initializer_list>

namespace JZEngine
{
	struct GlobalSystemsManager;
	struct GlobalSystem
	{
		virtual ~GlobalSystem() {};
		virtual void Init() {};
		virtual void FrameStart() {};
		virtual void Update(float dt) {};
		virtual void FrameEnd() {};
		virtual void Free() {};

		void SetGSM(GlobalSystemsManager* gsm);
		template <typename SYSTEM>
		SYSTEM* GetSystem();
	private:
		GlobalSystemsManager* global_systems_manager_;
	};

	struct GlobalSystemsManager
	{
		std::vector<GlobalSystem*> global_systems_vec_;
		std::unordered_map<std::string, GlobalSystem*> global_systems_map_;

		GlobalSystemsManager();
		~GlobalSystemsManager();

		template <typename DERIVED, typename...ARGS>
		void AddSystem(ARGS... args)
		{
			global_systems_vec_.push_back(new DERIVED(args...));
			global_systems_map_[typeid(DERIVED).name()] = global_systems_vec_.back();
			global_systems_vec_.back()->SetGSM(this);
			global_systems_vec_.back()->Init();
		}

		template <typename DERIVED>
		DERIVED* GetSystem()
		{
			if (global_systems_map_.find(typeid(DERIVED).name()) != global_systems_map_.end())
			{
				return dynamic_cast<DERIVED*>(global_systems_map_[typeid(DERIVED).name()]);
			}
			return nullptr;
		}

		void Init();
		void FrameStart();
		void Update(float dt);
		void FrameEnd();
		void Free();
	};

	template <typename SYSTEM>
	SYSTEM* GlobalSystem::GetSystem()
	{
		if (global_systems_manager_)
		{
			return global_systems_manager_->GetSystem<SYSTEM>();
		}
		return nullptr;
	}
}