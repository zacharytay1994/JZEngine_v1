/*	__FILE HEADER__
*	File:		Event.h
	Primary:	Yu Ching Yin
	Date:		01/07/21
	Brief:		Message Bus.
*/

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

			//to loop thru all subscribers
			for (auto& handler : *handlers)
			{
				if (handler != nullptr)
				{
					//calls subscribers
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

			//encpsulate instance & memberFunction
			handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
		}

		~MessageBus()
		{
			for (const auto& [key, value]: subscribers)
			{
				for (auto& handler : *value)
				{
					//delete everything inside the list
					delete handler;
				}

				//delete the HandlerList pointer itself
				delete value;
			}
		}

	private:
		std::map<std::type_index, HandlerList*> subscribers;
	};



} //JZEngine namespace