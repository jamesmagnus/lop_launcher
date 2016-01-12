#pragma once

#include <string>

#ifdef _WIN32

//! \def Windows only. Define the max size in byte for the temporary string holding error message from system.
#define ERROR_STR_MAX_SIZE 2048

#endif

std::string getWindowsErrorMessage();