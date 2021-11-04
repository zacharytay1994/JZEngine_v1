/*	__FILE HEADER__
*	File:		GlobalSystems.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Virtual class for global systems.
*/

#include <PCH.h>
#include "GlobalSystems.h"
#include "DebugTools/PerformanceData.h"

namespace JZEngine
{
	void GlobalSystem::SetGSM ( GlobalSystemsManager* gsm )
	{
		global_systems_manager_ = gsm;
	}

	GlobalSystemsManager::GlobalSystemsManager ()
	{}

	GlobalSystemsManager::~GlobalSystemsManager ()
	{
		for( auto& system : global_systems_vec_ )
		{
			if( system )
			{
				delete system;
			}
		}
	}

	void GlobalSystemsManager::Init ()
	{
		for( auto& system : global_systems_vec_ )
		{
			system->Init ();
		}

	}

	void GlobalSystemsManager::PostInit ()
	{
		for( auto& system : global_systems_vec_ )
		{
			system->PostInit ();
		}

	}

	void GlobalSystemsManager::FrameStart ()
	{
		for( auto& system : global_systems_vec_ )
		{
			system->FrameStart ();
		}
	}

	void GlobalSystemsManager::Update ( float dt )
	{
		for( auto& system : global_systems_vec_ )
		{
			PerformanceData::StartMark ( system->name_ , PerformanceData::TimerType::GLOBAL_SYSTEMS );

			system->Update ( dt );

			PerformanceData::EndMark ( system->name_ , PerformanceData::TimerType::GLOBAL_SYSTEMS );
		}
	}

	void GlobalSystemsManager::FrameEnd ()
	{
		for( auto& system : global_systems_vec_ )
		{
			system->FrameEnd ();
		}
	}

	void GlobalSystemsManager::Free ()
	{
		for( auto& system : global_systems_vec_ )
		{
			if( system )
			{
				system->Free ();
			}
		}
	}
}