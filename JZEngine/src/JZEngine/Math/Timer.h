/*	__FILE HEADER__
*	File:		Timer.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Custom timer class.
*/

#pragma once

#include "../BuildDefinitions.h"


namespace JZEngine
{
	class JZENGINE_API Timer
	{
	public:

		/*
		* noxcept operator
		* - performs a compile time check that returns true if an expression is declared to not throw any exceptions
		* - returns a prvalue of type bool
		*/
		Timer () noexcept;
		// Mark : Put at the start of the function / feature that you like to time . 
		float Mark () noexcept;
		// Peek : Put it at the end of the function / feature .
		//		: Std::cout Peek to see the duration of the start to the end of the function / feature .
		//		: User is encouraged to specified the file name to save to else will go into the public default timer history file.
		float Peek ( const std::string& filename = "TimerHistory.txt" ) noexcept;
		// TimerHistory : Call this function to print the last 5 timer history .
		void TimerHistory () const noexcept;

	private:

		/*
		* Class std::chrono::steady_clock::time_point
		* - represents a point in time , stores value of type : Duration
		*/
		void LastDuration ( float last_timer , const std::string& filename );
	};
}

