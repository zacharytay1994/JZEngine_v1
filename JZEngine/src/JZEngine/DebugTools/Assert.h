/*	__FILE HEADER__
*	File:		Assert.h
	Primary:	Jia Min
	Secondary:	
	Date:		28/09/2021
	Brief:

	How to use :
	Call the word "ASSERT" .

	Example #1 : JZ_ASSERT(J+Z == 1 , "engine");

		Console Print Out for Example 1 :
		Assertion Failed: J+Z == 1
		Message         : engine
		File            : main.cpp, line 33

	Example #2 : JZ_ASSERT(J+Z == 1, "engine")(J);

		Console Print Out for Example 2 :
		Assertion Failed: J+Z == 1
		Message         : engine
		File            : main.cpp, line 33
		Report          : J = 2

	More explanation below.
*/

#pragma once
//#a
#define __ASSERT1__(x) __REPORT__(x).__ASSERT2__ 
//#b
#define __ASSERT2__(x) __REPORT__(x).__ASSERT1__ 
//#c
#define __REPORT__(x) report(#x,(x)) 
//#d
#define JZ_ASSERT(cond, msg) if(!(cond)) Assert(#cond,msg,__FILE__,__LINE__).__ASSERT1__

/*
	Why mutual recursion? Let's expand using example #3.

	Example #3: JZ_ASSERT(J+Z == 1, "engine")(J)(Z)

	1.  if(!(J+Z)==1)Assert(J+Z==1,"engine", __FILE__ , __LINE__).
		report("J",(J)).__ASSERT2__(Z)

	2. if(!(J+Z)==1)Assert(J+Z==1,"engine", __FILE__ , __LINE__).
		report("J",(J)).report("Z", (Z)).__ASSERT1__

	Sequence :d>a>c>b
	__ASSERT1__ will not continue to expand.

	Call it a SMART assert ? hohoho
	Mutual recursion of between macros __ASSERT1__ and __ASSERT2__, and
	by two useless members Assert.__ASSERT1__ and Assert.__ASSERT2__, it
	manage to coin a confusing syntax. C macros doesn't make any sense.
	It's a legacy tool.
*/

#include <iostream>

struct Assert
{
	template<class T>
	Assert ( const char* cond , T&& msg , const char* file , int line )
	{
		std::cout << "\n_____________JZ_ASSERT_____________\n";
		std::cerr << "Assertion Failed: " << cond << "\n";
		std::cerr << "Message         : " << msg << "\n";
		std::cerr << "File            : " << file << ", line " << line << "\n";
	};

	template<class T>
	Assert& report ( const char* name , T&& value )
	{
		std::cerr << "Report          : " << name << " = " << value << "\n";
		return *this;
	};

	struct Empty
	{};
	static constexpr Empty __ASSERT1__{} , __ASSERT2__{};

	~Assert ()
	{
		exit ( -1 );
	};
};
