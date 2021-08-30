/*	__FILE HEADER__
*	File:	BuildDefinitions.h
*	Author: JZ
*	Date:	19/06/21
*	Brief:	Defines some stuff to shorten the dllexport and import
*			syntax on the engine and client's side.
*/

#pragma once

/*	ENGINE_PLATFORM_WINDOWS preprocessor definition included in both 
	engine project and client project	*/
#ifdef JZENGINE_PLATFORM_WINDOWS
/*	ENGINE_BUILD_DLL preprocessor definition included only in engine
	project */
	#ifdef JZENGINE_BUILD_DLL
		#define JZENGINE_API __declspec(dllexport)
		#define JZENGINE_EXTERN
	#else
		#define JZENGINE_API __declspec(dllimport)
		#define JZENGINE_EXTERN extern
	#endif
#else
	#error PLATFORM IS NOT WINDOWS!
#endif // !ENGINE_PLATFORM_WINDOWS
