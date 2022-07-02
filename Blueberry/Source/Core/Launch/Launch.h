#pragma once

#include "ExitCode.h"

#include "Core/Base.h"
#include "Core/Application.h"
#include "Core/Platform.h"
#include "Core/Memory.h"

namespace Blueberry {
	
	static bool s_RestartApplication = false;

	inline int32_t BlueberryMain(CharT** cmd_params, uint32_t cmd_params_num)
	{
		if (!Platform::Initialize())
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		if (!Memory::Initialize(true))
			return BLUE_EXIT_CODE_INITIALIZE_FAILED;

		int32_t return_code = BLUE_EXIT_CODE_SUCCESS;

		do
		{
			// Creates the application
			Application* application = CreateApplication();

			// Runs the application
			return_code = application->Run(cmd_params, cmd_params_num);

			// Destroys the application
			delete application;
		}
		while (s_RestartApplication);

		Memory::Shutdown();
		Platform::Shutdown();

		return return_code;
	}

}

#if BLUE_PLATFORM_WINDOWS // Compiling for Windows
	#include "WindowsLaunch.h"
#endif