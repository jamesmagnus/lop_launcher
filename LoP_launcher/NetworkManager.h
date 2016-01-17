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
//! \brief Header file for the class CNetworkManager. This class is a singleton and manage the send/receive packets.

#pragma once

#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakString.h>
#include <RakNet/BitStream.h>
#include <string>

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

//! \enum ECustomMessageID extends the Raknet message ID with custom IDs.
enum ECustomMessageID
{
	EMsgIDFileInfo = DefaultMessageIDTypes::ID_USER_PACKET_ENUM,	//!< Message with informations about a file.
	EMsgIDFileContent,												//!< File transfer.
	EMsgIDFileHash,													//!< MD5 file hash.
	EMsgIDVersion													//!< Game version.
};

//! \enum ESubrequestID completes the message ID with a second byte that tells the system what to do with the file hash for exemple.
enum ESubrequestID
{
	ESubMsgRequest = 1,		//!< Ask the system for something (like a file hash).
	ESubMsgResponse			//!< Response from the remote system to a request previously sent.
};

class RakNet::RakPeerInterface;

//! \class CNetworkManager
//! \brief This class is used to manage connexions over the network.

//! Only one instance of this class must be created, so it's a singleton.
class CNetworkManager
{
private:
	static CNetworkManager* mpNetManager;	//!< Unique instance pointer
	bool mIsServer;							//!< True if the network manager is running as a server, false otherwise.
	RakNet::RakPeerInterface* mpPeer;		//!< Pointer on raknet peer object.
	RakNet::BitStream mBS;					//!< BitStream will be fed with some data before be sent as a packet.
	bool mIsConnected;						//!< True if the system is connected to the server, false otherwise.

	//! \brief Constructor.

	//! Private constructor used by the singleton. Use CNetWork::instance().
	//! \param EType: EClient or EServer.
	CNetworkManager(ECS EType);

	//! \brief Destructor.

	//! Private destructor used by the singleton. Use CNetWork::destroy().
	~CNetworkManager();

	//! \brief Private const method that return the identifier byte of a packet.
	//! \param pPacket: the address of a packet.
	//! \return Return the identifier (1 byte) of the packet.
	RakNet::MessageID getPacketIdentifier(RakNet::Packet const* pPacket) const;

	//! \brief Private const method that return the second identifier byte of packet. (subrequest ID).
	//! \param pPacket: the address of a packet. Caution passing a packet without a subrequest ID will return undefined byte!
	//! \return Return the sub ID (1 byte).
	RakNet::MessageID getPacketSubIdentifier(RakNet::Packet const* pPacket) const;

	//! \brief Private method to handle a game version request.
	//! \param pPacket: the address of a packet containing the request.
	//! \return Nothing.
	//! \throw Throw a std::exception if the packet doesn't contain a version request.
	void HandleVersionRequest(RakNet::Packet const* pPacket);

public:

	//! \brief Get the class unique instance.
	//! \param EType: EClient or EServer. Default is EClient. Useful only for the first call.
	//! \return Pointer on the unique instance.
	static CNetworkManager* getInstance(ECS EType = ECS::EClient);

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
	//! \throw Throw a std::exception if the host name isn't valid.
	void Ping(unsigned short port, RakNet::RakString address = "255.255.255.255") const;

	//! \brief Process each packet on the stack and then free these packets.

	//! Must be called every frame.
	//! \return True if there were packets, false otherwise.
	bool ProcessPackets();

	//! \brief Print a message on std::cout with the details of the ping response.
	//! \param pPacket: a pointer to the packet. Must be a ping response packet.
	//! \return Nothing
	//! \throw Throw a std::exception if the packet is not a ping response packet.
	void PrintPingResponse(RakNet::Packet* pPacket) const;

	//! \brief Create a new packet that will be sent over the network.

	//! Packet only contains timestamp. You need to fill it with AddData(data).
	//! \param EmessageID: an ECustomMessageID enum's element that indicate to the receiver what to do with the packet.
	//! \return Nothing.
	void CreatePacket(ECustomMessageID EmessageID);

	//! \brief Try to establish a connection with a server.
	//! \param rIP: a string with the rIP address to connect to. Ex: "127.0.0.1".
	//! \param port: port number.
	//! \param rPublicKey: public key to authenticate yourself with the server.
	//! \param connectionTry: number of connection request before give up.
	//! \param timeBetween: time to wait for a response before trying again.
	//! \return Nothing.
	void Connect(std::string const& rIP, unsigned short port, RakNet::PublicKey *pPublicKey, unsigned int connectionTry = 12, unsigned int timeBetween = 1000);

	//! \brief Send the current packet to the server.
	//! \return Nothing.
	//! \throw Throw a std::exception if the function fails to send the packet. If no exception is thrown it doesn't mean the packet has been receive.
	void Send();

	//! \brief Template method that add some data to the current packet.

	//! It's template because you can write integer, float, std::string, literal string, structure that is a mix of all of these.
	//! \param data: the data you want to write in the current packet, it must not be a pointer or a structure containing a pointer!
	//! \return Nothing
	template<typename T>
	void AddData(T data);

};

template<typename T>
void CNetworkManager::AddData(T data)
{
	mBS.Write(data);
}

