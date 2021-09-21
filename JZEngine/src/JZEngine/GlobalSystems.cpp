#include <PCH.h>
#include "GlobalSystems.h"

namespace JZEngine
{
	GlobalSystemsManager::GlobalSystemsManager()
	{

	}

	GlobalSystemsManager::~GlobalSystemsManager()
	{
		for (auto& system : global_systems_vec_)
		{
			if (system)
			{
				delete system;
			}
		}
	}

	void GlobalSystemsManager::Init()
	{
		for (auto& system : global_systems_vec_)
		{
			system->Init();
		}
	}

	void GlobalSystemsManager::FrameStart()
	{
		for (auto& system : global_systems_vec_)
		{
			system->FrameStart();
		}
	}

	void GlobalSystemsManager::Update(float dt)
	{
		for (auto& system : global_systems_vec_)
		{
			system->Update(dt);
		}
	}

	void GlobalSystemsManager::FrameEnd()
	{
		for (auto& system : global_systems_vec_)
		{
			system->FrameEnd();
		}
	}

	void GlobalSystemsManager::Free()
	{
		for (auto& system : global_systems_vec_)
		{
			if (system)
			{
				system->Free();
			}
		}
	}
}