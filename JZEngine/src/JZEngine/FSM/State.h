/*	__FILE HEADER__
*	File:		State.h
	Primary:	Ching Yin
	Date:		19/06/21
	Brief:		State of statemachine.
*/

#pragma once

#include <string>

namespace JZEngine
{
	template <typename T>
	class State
	{
	public:

		//Use inline for small/one liner function in header file to increase compilation time
		inline T getID()
		{
			return mID;
		}

		inline const std::string& getName() const
		{
			return mName;
		}

		//Use explicit to avoid any implicit conversion
		explicit State(T id, std::string name = "default") : mName{ name }, mID{ id } {}

		virtual void enter()
		{
			//To be overwritten in a derived class
		}

		virtual void exit()
		{
			//To be overwritten in a derived class
		}

		virtual void update(float dt)
		{
			UNREFERENCED_PARAMETER(dt);
			//To be overwritten in a derived class
		}

		//To delete the inherited ones (aka CustomerState), not the base class State
		virtual ~State() = default;

	private:
		std::string mName;
		T mID;
	};


} //JZEngine namespace
