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

		template<typename T, typename EventType>
		void subscribe(T* instance, void (T::* memberFunction)(EventType*))
		{
			HandlerList* handlers = subscribers[typeid(EventType)];

			//First time initialization
			if (handlers == nullptr)
			{
				handlers = new HandlerList();
				subscribers[typeid(EventType)] = handlers;
			}

			handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
		}

	private:
		std::map<std::type_index, HandlerList*> subscribers;
	};



} //JZEngine namespace