#pragma once
#include "stdafx.h"
#include "NetworkClient.h"




class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();
	void NetworkClient::sendTCPMessage(std::string host, int port, std::string message);

	void NetworkClient::RecieveMessage();

	
};

