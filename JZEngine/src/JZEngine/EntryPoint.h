/*	__FILE HEADER__
*	File:	EntryPoint.h
	Author: JZ
	Date:	19/06/21
	Brief:	Defines the entry point if the current project
			has preprocessor definition JZENGINE_PLATFORM_WINDOWS defined.	
*/

#pragma once

#include "Application.h"

// Memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef JZENGINE_PLATFORM_WINDOWS
	extern JZEngine::Application* JZEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

		auto app = JZEngine::CreateApplication();
		app->Run();
		delete app;

		_CrtDumpMemoryLeaks();
	}
#endif // !ENGINE_PLATFORM_WINDOWS
