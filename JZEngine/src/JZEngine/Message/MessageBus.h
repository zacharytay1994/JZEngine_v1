#pragma once

#include <list>
#include <map>
#include <typeindex>  //std::type_index
#include <typeinfo>  //operator typeid
#include "../Message/MessageHandler.h"

namespace JZEngine
{
	typedef std::list<HandlerFunctionBase*> HandlerList;

	class MessageBus
	{
	public:
		template<typename EventType>
		void publish(EventType* event)
		{
			HandlerList* handlers = subscribers[typeid(EventType)];

			if (handlers == nullptr)
			{
				return;
			}

			//to loop thru
			for (auto& handler : *handlers)
			{
				if (handler != nullptr)
				{
					handler->exec(event);
				}
			}
		}

	private:
		std::map<std::type_index, HandlerList*> subscribers;
	};












} //JZEngine namespace