#pragma once

#include "../ECS/ECS.h"

#include <string>
#include <unordered_map>

namespace JZEngine
{
	static constexpr int MAX_LOGIC_PER_ENTITY = 10;

	struct EntityPacket
	{
		ECS::Chunk* chunk_ { nullptr };
		ECS::ui32 id_ = static_cast< ECS::ui32 >( -1 );
		EntityPacket ( ECS::Chunk* chunk , ECS::ui32 id )
			:
			chunk_ ( chunk ) ,
			id_ ( id )
		{
		}
	};

	struct CustomLogicContainer
	{
		// 10 functions max per entity
		int updates[ MAX_LOGIC_PER_ENTITY ] { 0 };
	};

	struct LogicContainerSystem : public ECS::System
	{
		LogicContainerSystem ();

		void Update ( float const& dt ) override;
	};

	typedef void( *JZUpdate )( float const& , EntityPacket& );

	void DefaultUpdate ( float const& dt , EntityPacket& ep );

	struct LogicContainer
	{
		static LogicContainer& Instance ();

		void Register ( std::string const& name , JZUpdate function );
		void Invoke ( int id , float dt , EntityPacket ep );
		void Invoke ( std::string& name , float dt , EntityPacket ep );

		std::unordered_map<std::string , int>& GetUpdates ();
		std::string GetUpdateName ( int i );
		int GetUpdateID ( std::string const& name );

	private:
		LogicContainer ();

		std::unordered_map<std::string, int> logic_map_;
		std::vector<JZUpdate> logic_;
	};
}