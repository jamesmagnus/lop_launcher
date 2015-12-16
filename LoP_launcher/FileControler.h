﻿// Copyright © 2015,2016 Jean-loup Beaussart 
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

//! \file NetworkManager.h
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Header file for the CFileControler class. It's a class used to check file's version on the drive and to say if needs update or not. It's a singleton.

#pragma once

//! \enum EFileState Enum used to describe if the file is up to date or not.
enum class EFileState
{
	EFileNotFound,		//!< File not found on the drive, needs to be copied.
	EFileUpToDate,		//!< File found and it's the good one.
	EFileNeedsUpdate	//!< File found but it's an older version or it is corrupted, needs to be updated.
};

//! \class CFileControler
//! \brief A singleton that can search for files and checks their version, copy or delete files if needed.
class CFileControler
{
private:
	static CFileControler* mpInstance;

	//! \brief Private constructor.
	CFileControler();

	//! \brief Private destructor.
	~CFileControler();

public:

	//! \brief Get the class unique instance.
	//! \return A pointer to the unique instance.
	static CFileControler* getInstance();

	//! \brief Destroy the unique instance.
	//! \return Nothing.
	static void destroy();
};
