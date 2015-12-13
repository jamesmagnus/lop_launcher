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

//! \file NetworkManager.h
//! \author Jean-loup Beaussart
//! \version 0.1
//! \copyright 2015,2016 Jean-loup Beaussart LGPLv3
//! \brief Header file for the class CNetworkManager.

#pragma once

#include <RakNet/RakString.h>

//! \def Define the maximum number of connexions allowed at the same time (server mode).
#define MAX_PEER 500

//! \def Define the server port (server mode).
#define SERVER_PORT 53842

//! \enum ECS Server or Client mode enum.
enum class ECS
{
	EServer,	//!< Server
	EClient		//!< Client
};

class RakNet::RakPeerInterface;

//! \class CNetworkManager
//! \brief This class is used to manage connexions over the network.

//! Only one instance of this class must be created, so it's a singleton.
class CNetworkManager
{
private:
	static CNetworkManager* mpNetManager; //!< Unique instance pointer
	bool mIsServer; //!< True if the network manager is running as a server, false otherwise.
	RakNet::RakPeerInterface* mpPeer; //!< Pointer on raknet peer object.

	//! \brief Constructor.

	//! Private constructor used by the singleton. Use CNetWork::instance().
	//! \param EType: EClient or EServer.
	CNetworkManager(ECS EType);

	//! \brief Destructor.

	//! Private destructor used by the singleton. Use CNetWork::destroy().
	~CNetworkManager();

public:

	//! \brief Get the unique instance of the class.
	//! \param EType: EClient or EServer. Default is EClient. Useful only for the first call.
	//! \return Pointer on the unique instance.
	static CNetworkManager* getInstance(ECS EType=ECS::EClient);

	//! \brief Destroy the unique instance of the singleton.
	//! \return Nothing.
	static void destroy();

	//! \brief Create the sub-system client/server.
	//! \return Nothing
	//! \throw Throw a std::exception if something goes wrong.
	void CreateSubSystem();

	//! \brief Ping an other instance of raknet.
	//! \param port: the port
	//! \param address: target's address
	//! \return Nothing
	void Ping(unsigned int port, RakNet::RakString address = "255.255.255.255") const;

	//! \brief Process each packet on the stack and then free these packets.

	//! Must be called every frame.
	//! \return True if there were packets, false otherwise.
	bool ProcessPackets();

	//! \brief Print a message on std::cout with the details of the ping response.
	//! \param pPacket: a pointer to the packet. Must be a ping response packet.
	//! \return Nothing
	//! \throw Throw a std::exception if the packet is not a ping response packet.
	void PrintPingResponse(RakNet::Packet* pPacket) const;

};

