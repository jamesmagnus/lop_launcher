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

CFileControler* CFileControler::mpInstance = nullptr;

CFileControler::CFileControler()
{
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
