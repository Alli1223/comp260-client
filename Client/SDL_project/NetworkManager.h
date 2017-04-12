#pragma once
#include "stdafx.h"
#include "NetworkClient.h"

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	void NetworkManager::NetworkUpdate();
	void NetworkManager::server_thread();
	void NetworkManager::connectToServer(std::string host, int port);
	int port = 8080;
	void NetworkManager::sendTCPMessage(std::string host, int port, std::string message);

	void NetworkManager::RecieveMessage();

	
	boost::asio::io_service ios;
	
	
};

