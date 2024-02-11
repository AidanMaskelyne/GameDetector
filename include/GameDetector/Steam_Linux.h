#pragma once

#include "Utilities.h"

#if defined(__linux__)
#else
#error Tried to include Steam_Unix.h on a non-unix operating system
#endif
