#pragma once
#include "stdafx.h"
#include "NetworkClient.h"
#include "Agent.h"
#include "Level.h"
#include "AgentManager.h"

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	void NetworkManager::NetworkUpdate(Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket);
	void NetworkManager::server_thread();
	void NetworkManager::connectToServer(std::string host, int port);
	void NetworkManager::sendTCPMessage(std::string host, int port, std::string message, boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket);

	std::string NetworkManager::RecieveMessage(boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket);

	// Server connection deets
	int port = 2222;
	std::string IPAddresss = "46.101.9.185";
	std::string IPAddress = "127.0.0.1";

	//! Network update interval
	int networkUpdateInterval = 100;

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;
	
	boost::asio::io_service ios;
	
	
};

