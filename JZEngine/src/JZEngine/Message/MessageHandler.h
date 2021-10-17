/*	__FILE HEADER__
*	File:		Event.h
	Primary:	Yu Ching Yin
	Date:		01/07/21
	Brief:		Message Handler.
*/

#pragma once

namespace JZEngine
{
	class Event
	{
	protected:
		virtual ~Event() = default;
	};


	class HandlerFunctionBase
	{
	public:

		//Call the member function
		void exec(Event* event)
		{
			call(event);
		}

	private:

		//To be implemented by MemberFunctionHandler
		// = 0 is pure virtual function and requires to be overwritten in a derived class
		virtual void call(Event* event) = 0; 
	};
	

	template<typename T, typename EventType>
	class MemberFunctionHandler : public HandlerFunctionBase
	{
	public:

		//This is a function pointer
		typedef void (T::* MemberFunction)(EventType*);

		MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

		void call(Event* event)
		{
			//Cast event to the correct type and call member function
			//For simplicity think of it as memberFunction(event)
			(instance->*memberFunction)(static_cast<EventType*>(event));
		}

	private:

		//Pointer to class/typename instance
		T* instance;

		//Pointer to member function
		MemberFunction memberFunction;
	};



} //JZEngine namespace