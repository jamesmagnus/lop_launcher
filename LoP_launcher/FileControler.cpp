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

//! \file FileControler.cpp
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Methods and functions related to the CFileControler class. It's a class used to check file's version on the drive and to say if needs update or not. It's a singleton.

#include "FileControler.h"
#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <exception>
#include <vector>

#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;
using namespace boost;

CFileControler* CFileControler::mpInstance = nullptr;

CFileControler::CFileControler()
{
	mDirectory = "";
}

CFileControler::~CFileControler()
{
}

CFileControler* CFileControler::getInstance()
{
	if (!mpInstance)
	{
		mpInstance = new CFileControler();
	}

	return mpInstance;
}

void CFileControler::destroy()
{
	delete mpInstance;
}

void CFileControler::LoadDirectoryAndLock(string const& rDirectory)
{
	if (filesystem::exists(rDirectory) && filesystem::is_directory(rDirectory))
	{
		vector<filesystem::path> paths;

		mDirectory = rDirectory;

		copy_if(filesystem::recursive_directory_iterator(rDirectory), filesystem::recursive_directory_iterator(), back_inserter(paths), [](filesystem::directory_entry it)
		{
			return !filesystem::is_directory(it.path());
		});

		for_each(paths.begin(), paths.end(), [this](filesystem::path path)
		{
#ifdef WIN32
			/* Getting windows handle on file to prevent other process from modifying it */
			void* p = nullptr;

			if ((p = CreateFile(path.generic_wstring().c_str(), GENERIC_WRITE | GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)) != INVALID_HANDLE_VALUE)
			{
				mHandles.push_back(p);
			}
			else
			{
				
				wstring e = path.c_str();
				LPWSTR k = nullptr;
				char *exceptionMessage = new char[ERROR_STR_MAX_SIZE];

				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, GetLastError(), 0, (LPWSTR)&k, ERROR_STR_MAX_SIZE, nullptr);
				
				e += L" : ";
				e += k;

				HeapFree(GetProcessHeap(), 0, k);

				WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, e.c_str(), -1, (LPSTR)exceptionMessage, ERROR_STR_MAX_SIZE, nullptr, nullptr);

				throw std::exception(exceptionMessage);
			}	
#endif
		});
	}
	else
	{
		string e = rDirectory + " doesn't exist or is not a directory.";
		throw std::exception(e.c_str());
	}
}

void CFileControler::UnloadDirectory()
{
	if (mDirectory != "")
	{
		for_each(mHandles.begin(), mHandles.end(), [](void *p)
		{
			CloseHandle(p);
		});
	}
}
