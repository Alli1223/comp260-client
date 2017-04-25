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
	//! Main Network update function
	void NetworkManager::NetworkUpdate(Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket);
	//! Send a message using TCP
	void NetworkManager::sendTCPMessage(std::string message, boost::asio::ip::tcp::socket& socket);
	//! Process the players location from string
	void NetworkManager::ProcessPlayerLocations(std::string updateMessage, Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket);
	//! Process a list of player locations
	void NetworkManager::ProcessArrayOfPlayerLocations(std::string updateMessage, Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket);
	//! Return a string from recieve message
	std::string NetworkManager::RecieveMessage(boost::asio::ip::tcp::socket& socket);

	void NetworkManager::runMultiThread(Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket);

	// Server connection deets
	int port = 2222;
	
	std::string ExternalIPAddress = "46.101.9.185";
	std::string InternalIPAddresss = "127.0.0.1";

	//! Whether the client should connect to external server
	bool isServerLocal = true;
	//! Whether the client can enter their name in console
	bool clientCanEnterName = false;
	//! Whether the client should request playernumers
	bool GetNumPlayers = false;

	//! Network update interval
	int networkUpdateInterval = 200;
	//! Stores the number of players in the game
	int numberOfPlayers = 0;

	

	//! get and set server IP address
	std::string getServerIP() { return IPAddress; }
	std::string setServerIP(std::string newIP) { return IPAddress = newIP; }

	//! get and set server IP address
	std::string getPlayerName() { return localPlayerName; }
	std::string setPlayerName(std::string newPlayerName) { return localPlayerName = newPlayerName; }
	

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;
	//! the io service for creating the socket
	boost::asio::io_service ios;

private:
	//! for when I get round to making the client multi threaded
	std::vector<std::thread> some_threads;
	//! for ip Address
	std::string IPAddress;
	//! For the name of the local player
	std::string localPlayerName;
};

