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

#ifdef _WIN32
#include "WinUtil.h"
#endif

#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <utf8.h>
#include <exception>
#include <vector>
#include <cstdio>
#include <iostream>
#include <OTHER/include/md5.h>

using namespace std;
using namespace boost;

CFileControler* CFileControler::mpInstance = nullptr;

CFileControler::CFileControler()
{
	mDirectory.clear();
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
			HANDLE p = nullptr;

			if ((p = CreateFile(path.generic_wstring().c_str(), GENERIC_WRITE | GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)) != INVALID_HANDLE_VALUE)
			{
				wstring wPath = path.c_str();
				string pathUTF8;
				utf8::utf16to8(wPath.begin(), wPath.end(), back_inserter(pathUTF8));

				mHandles.insert_or_assign(pathUTF8, p);
			}
			else
			{
				wstring wMessage = path.c_str();
				string exceptionMessageUTF8;

				utf8::utf16to8(wMessage.begin(), wMessage.end(), back_inserter(exceptionMessageUTF8));
				exceptionMessageUTF8 += getWindowsErrorMessage();

				throw std::exception(exceptionMessageUTF8.c_str());
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
	if (!mDirectory.empty())
	{
		vector<string> errors;
		for_each(mHandles.begin(), mHandles.end(), [& errors](pair<string, HANDLE> p)
		{
			if (!CloseHandle(p.second))
			{
				string tmp = p.first;
				tmp += " : ";
				tmp += getWindowsErrorMessage();

				errors.push_back(tmp);
			} 
		});

		mDirectory.clear();
		mHandles.clear();

		if (!errors.empty())
		{
			string msg;

			for_each(errors.begin(), errors.end(), [& msg](string e)
			{
				msg += e;
				msg += "\n";
			});

			throw std::exception(msg.c_str());
		}
	}
}

string CFileControler::FileMD5(string const& rName) const
{
	if (mHandles.find(rName) != mHandles.end())
	{
		md5_byte_t B;
		md5_state_t MD5State;
		md5_init(&MD5State);
		unsigned long nb;

#ifdef _WIN32

		HANDLE file = mHandles.at(rName);
		ReadFile(file, &B, 1, &nb, nullptr);

		do 
		{
			md5_append(&MD5State, &B, 1);
		} while (ReadFile(file, &B, 1, &nb, nullptr) && nb != 0);

		md5_byte_t tmp[17];
		tmp[16] = '\0';

		md5_finish(&MD5State, tmp);

		return (char*)tmp;

#endif
	}
	else
	{
		string msg("Cannot find the requested file: " + rName + "\n");
		throw std::exception(msg.c_str());
	}
}

std::string CFileControler::getGameVersion() const
{
	FILE *pF = nullptr;

	fopen_s(&pF, "/data/manifest.man", "r");

	return "";
}
