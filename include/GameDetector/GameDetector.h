#pragma once

#if defined(_WIN32)
	#include "Steam_Win32.h"
	#include "GOG.h"
	#include "EpicGames.h"
#elif defined(__linux__)
	#include "Steam_Unix.h"
#endif
