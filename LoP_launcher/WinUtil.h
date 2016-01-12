// Copyright © 2015,2016 Jean-loup Beaussart 
//
// This file is part of Light of Paladin Launcher.
// 
// Light of Paladin Launcher is free software : you can redistribute it and / or modify
// it under the terms of the LGPL Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Light of Paladin Launcher is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// LGPL Lesser General Public License for more details.
// 
// You should have received a copy of the LGPL Lesser General Public License
// along with Light of Paladin Launcher. If not, see < http://www.gnu.org/licenses/ >.

//! \file WinUtil.h
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Header file for WinUtil.cpp. It contains Windows OS relative functions declarations. Like error handling.


#pragma once

#include <string>

#ifdef _WIN32

//! \def Windows only. Define the max size in byte for the temporary string holding error message from system.
#define ERROR_STR_MAX_SIZE 2048

#endif

//! \brief Get the last Windows thread error code via GetLastError(). Create the corresponding message with FormatMessage() then encode it in UTF-8.
//! \return Return a std::string with the last error message UTF-8 encoded.
std::string getWindowsErrorMessage();