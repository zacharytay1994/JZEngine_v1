/*	__FILE HEADER__
*	File:	DebugNew.h
	Author: JZ
	Date:	28/09/2021
	Brief:
	Memory leaks result from the failure to correctly deallocate memory
	that was previously allocated. A small memory leak might not be noticed 
	at first, but over time can cause symptoms ranging from poor performance
	to crashing when the app runs out of memory. A leaking app that uses up
	all available memory can cause other apps to crash, creating confusion
	as to which app is responsible. Even harmless memory leaks might indicate 
	other problems that should be corrected.

	How to use : 
	1 .Replace the new operator by using the "DBG_NEW" in your code.

	Alternatively , 
	2 .You can just write "new" as per usual.
	If you do not want to rewrite your entire program to use DEBUG_NEW .
*/

#pragma once

#define _CRTDBG_MAP_ALLOC

#include<iostream>
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
	#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
	#define new DEBUG_NEW
#else
	#define DEBUG_NEW new
	#define new DEBUG_NEW
#endif
