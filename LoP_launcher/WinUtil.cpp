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

//! \file WinUtil.cpp
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Utility functions for Windows OS.


#include "WinUtil.h"
#include <utf8.h>
#include <Windows.h>

using namespace std;

string getWindowsErrorMessage()
{
	wstring wMessage;
	LPWSTR pErr = nullptr;

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, GetLastError(), 0, (LPWSTR)&pErr, ERROR_STR_MAX_SIZE, nullptr);

	wMessage = pErr;

	HeapFree(GetProcessHeap(), 0, pErr);

	string exceptionMessageUTF8;
	utf8::utf16to8(wMessage.begin(), wMessage.end(), back_inserter(exceptionMessageUTF8));

	return exceptionMessageUTF8;
}

