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

//! \file NetworkManager.cpp
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Methods and functions related to the CNetworkManager class. This class is a singleton and manage the send/receive packets.

#include "NetworkManager.h"
#include <exception>
#include <iostream>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakNetTime.h>
#include <RakNet/GetTime.h>

CNetworkManager* CNetworkManager::mpNetManager = nullptr;

CNetworkManager::CNetworkManager(ECS EType)
{
	mIsServer = EType==ECS::EServer ? true : false;
}

CNetworkManager::~CNetworkManager()
{
}

CNetworkManager * CNetworkManager::getInstance(ECS EType)
{
	if (!mpNetManager)	// EType used only when creating the singleton.
	{
		mpNetManager = new CNetworkManager(EType);
	}

	return mpNetManager;
}

void CNetworkManager::destroy()
{
	delete mpNetManager;
}

void CNetworkManager::CreateSubSystem()
{
	mpPeer = RakNet::RakPeerInterface::GetInstance();

	if (mIsServer)
	{
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		if (mpPeer->Startup(MAX_PEER, &sd, 1))
		{
			throw std::exception("Error while starting the network thread.");
		}
		mpPeer->SetMaximumIncomingConnections(MAX_PEER);
	}
	else
	{
		RakNet::SocketDescriptor sd;
		if (mpPeer->Startup(1, &sd, 1))
		{
			throw std::exception("Error while starting the network thread.");
		}
	}
}

void CNetworkManager::Ping(unsigned int port, RakNet::RakString address) const
{
	mpPeer->Ping(address.C_String(), port, false);
}

bool CNetworkManager::ProcessPackets()
{
	RakNet::Packet* pPacket = nullptr;

	while (pPacket = mpPeer->Receive())
	{
		switch (pPacket->data[0])
		{
		case ID_UNCONNECTED_PONG:
			PrintPingResponse(pPacket);
			break;
		case EFileInfo:
			break;
		case EFileContent:
			break;
		case EVersion:
			break;
		default:
			break;
		}

		mpPeer->DeallocatePacket(pPacket);
	}

	return true;
}

void CNetworkManager::PrintPingResponse(RakNet::Packet* pPacket) const
{
	if (pPacket->data[0] != ID_UNCONNECTED_PONG)
	{
		throw std::exception("Error: wrong packet type.");
	} 
	else
	{
		RakNet::BitStream bs(pPacket->data, pPacket->length, false);
		bs.IgnoreBytes(1);

		RakNet::TimeMS time;
		bs.Read(time);
		std::cout << "Response from: " << pPacket->systemAddress.ToString() << " Ping: " << RakNet::GetTimeMS() - time << std::endl;
	}
}

void CNetworkManager::CreatePacket(ECustomID EmessageID)
{
	mBS.Reset();

	mBS.Write(static_cast<RakNet::MessageID>(DefaultMessageIDTypes::ID_TIMESTAMP));
	mBS.Write(RakNet::GetTime());

	mBS.Write(static_cast<RakNet::MessageID>(EmessageID));
}
