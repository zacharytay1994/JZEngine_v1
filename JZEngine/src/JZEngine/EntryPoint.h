/*	__FILE HEADER__
*	File:	EntryPoint.h
	Author: JZ
	Date:	19/06/21
	Brief:	Defines the entry point if the current project
			has preprocessor definition JZENGINE_PLATFORM_WINDOWS defined.	*/

#pragma once

#include "Application.h"

#ifdef JZENGINE_PLATFORM_WINDOWS
	extern JZEngine::Application* JZEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = JZEngine::CreateApplication();
		app->Run();
		delete app;
	}
#endif // !ENGINE_PLATFORM_WINDOWS
