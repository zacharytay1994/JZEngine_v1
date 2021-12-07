/*	__FILE HEADER__
*	File:		LogicContainer.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Custom Logic.
*/

#include <PCH.h>
#include "LogicContainer.h"

#include "../DebugTools/Log.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	void DefaultUpdate ( float const& dt , EntityPacket& ep )
	{
		UNREFERENCED_PARAMETER ( dt );
		UNREFERENCED_PARAMETER ( ep );
	}

	void Update2 ( float const& dt , EntityPacket& ep )
	{
		UNREFERENCED_PARAMETER ( dt );
		UNREFERENCED_PARAMETER ( ep );
		Log::Info ( "Main" , "Update2 updating" );
		
	}
	
	void Update3 ( float const& dt , EntityPacket& ep )
	{
		UNREFERENCED_PARAMETER ( dt );
		UNREFERENCED_PARAMETER ( ep );
		//Log::Info ( "Main" , "Position x : {}" , system.GetComponent<JZEngine::Transform> ().position_.x );
	}

	LogicContainerSystem::LogicContainerSystem ()
	{
		RegisterComponents<CustomLogicContainer> ();
	}

	void LogicContainerSystem::Update ( float const& dt )
	{
		CustomLogicContainer& functions = GetComponent<CustomLogicContainer> ();
		for ( int i = 0; i < MAX_LOGIC_PER_ENTITY; ++i )
		{
			if ( functions.updates[ i ] != 0 )
			{
				LogicContainer::Instance ().Invoke ( functions.updates[ i ] , dt , EntityPacket(current_chunk_, current_id_) );
			}
		}
	}

	LogicContainer::LogicContainer ()
	{
		Register ( "Remove" , DefaultUpdate );
		/*Register ( "Update2" , Update2 );
		Register ( "Update3" , Update3 );*/
	}

	LogicContainer& LogicContainer::Instance ()
	{
		static LogicContainer instance;
		return instance;
	}

	void LogicContainer::Register ( std::string const& name , JZUpdate function )
	{
		logic_.push_back ( function );
		logic_map_[ name ] = static_cast<int>(logic_.size ()) - 1;
	}

	void LogicContainer::Invoke ( int id , float dt , EntityPacket ep )
	{
		if ( id < logic_.size () )
		{
			logic_[ id ] (dt, ep );
		}
	}

	void LogicContainer::Invoke ( std::string& name , float dt , EntityPacket ep )
	{
		if ( logic_map_.find ( name ) != logic_map_.end () )
		{
			Invoke ( logic_map_[ name ] , dt , ep );
		}
	}

	std::unordered_map<std::string , int>& LogicContainer::GetUpdates ()
	{
		return logic_map_;
	}

	std::string LogicContainer::GetUpdateName ( int i )
	{
		if ( i < logic_.size () )
		{
			for ( auto& update : logic_map_ )
			{
				if ( update.second == i )
				{
					return update.first;
				}
			}
		}
		return "NotFound";
	}

	int LogicContainer::GetUpdateID ( std::string const& name )
	{
		if ( logic_map_.find ( name ) != logic_map_.end () )
		{
			return logic_map_[ name ];
		}
		return 0;
	}
}