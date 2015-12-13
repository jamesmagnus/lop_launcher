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

//! \file main.cpp
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Source file with the main function, starting and ending points.

#include "main.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	CBaseWindow* pMainWindow = new CBaseWindow();
	pMainWindow->SetupUi();
	pMainWindow->show();

	CNetworkManager::getInstance(ECS::EClient)->CreateSubSystem();

	//TEST
	while (false)
	{
		CNetworkManager::getInstance()->Ping(53842, "127.0.0.1");
		CNetworkManager::getInstance()->ProcessPackets();
	}
	//TEST

	return app.exec();
}