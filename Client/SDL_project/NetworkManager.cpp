#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}
void NetworkManager::server_thread() {
	try
	{

		boost::asio::ip::tcp::acceptor acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 2223));

		{
			boost::asio::ip::tcp::socket socket(ios);
			acceptor.accept(socket);

			boost::asio::streambuf streamBuffer;
			boost::system::error_code errorCode;
			while (boost::asio::read(socket, streamBuffer, errorCode)) 
			{
				std::cout << "received: '" << &streamBuffer << "'\n";

				if (errorCode) {
					std::cout << "status: " << errorCode.message() << "\n";
					break;
				}
				break;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}


bool DoesPlayerExist(std::vector<std::string>& playerNames, std::string playername)
{
	// Return true if theres a match
	for (int i = 0; i < playerNames.size(); i++)
	{
		if (playername == playerNames[i])
			return true;
	}
	// Return false if no player with that name exists
	return false;
}

int GetGameInfo(std::string message)
{
	//Number of players
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == *"r" && message[i + 1] == *"#" && message[i + 2] == *":")
		{
			// Convert string to int
			std::string::size_type sz;
			std::string updatenumber = "      ";
			updatenumber[0] = message[i + 3]; updatenumber[1] = message[i + 4];
			// Remove white space
			updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
			int num = std::stoi(updatenumber, &sz);

			return num;

		}
		
	}
	return 0;
}

// Update every frame
void NetworkManager::NetworkUpdate(Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket)
{

	//Request number of current players
	//sendTCPMessage(IPAddress, port, "NUMBER_OF_PLAYERS_REQUEST\n", ios, socket);
	//std::string playerNumberString = RecieveMessage(ios, socket);
	//int numberOfPlayers = GetGameInfo(playerNumberString);

	// Request player locations
	sendTCPMessage(IPAddress, port, "PLAYER_LOCATIONS_REQUEST\n", ios, socket);
	std::string updateMessage = RecieveMessage(ios, socket);
	if (updateMessage != "NULL" && updateMessage != "QUIT" && updateMessage[0] == *"<")
	{
		std::cout << "RECIEVE MESSAGE: " << updateMessage << std::endl;

		std::string otherPlayerName = "                                                          ";

		// PlayerName
		for (int i = 1; i < updateMessage.size(); i++)
		{
			if (updateMessage[i] != *">")
				otherPlayerName[i] = updateMessage[i];
			else
				break;
		}
		// Remove any spaces from name
		otherPlayerName.erase(std::remove(otherPlayerName.begin(), otherPlayerName.end(), ' '), otherPlayerName.end());


		// If the player already exists
		if (DoesPlayerExist(otherPlayerNames, otherPlayerName))
		{
			// Update Player Positions
			for (int i = 0; i < updateMessage.size(); i++)
			{
				bool xUpdate = false, yUpdate = false;
				if (updateMessage[i] == *"X" && updateMessage[i + 1] == *":")
				{
					// Convert string to int
					std::string::size_type sz;
					std::string updatenumber = "      ";
					updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
					// Remove white space
					updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
					int pos = std::stoi(updatenumber, &sz);
					pos *= level.getCellSize();
					if (agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() != pos)
					{
						agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setX(pos);
						xUpdate = true;
					}
				}
				if (updateMessage[i] == *"Y" && updateMessage[i + 1] == *":")
				{
					// Convert string to int
					std::string::size_type sz;
					std::string updatenumber = "     ";
					updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
					// Remove white space
					updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
					int pos = std::stoi(updatenumber, &sz);
					pos *= level.getCellSize();
					if (agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() != pos)
					{
						agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setY(pos);
						yUpdate = true;
					}
				}
				if (xUpdate && yUpdate)
					break;


				// Update Player Actions
				std::string otherPlayerAction = "                                      ";
				if (updateMessage[i] == *"A" && updateMessage[i + 1] == *"C" && updateMessage[i + 2] == *"T" && updateMessage[i + 3] == *":")
				{
					for (int j = 0; j < 10; j++)
					{
						if (updateMessage[i + 4 + j] == *".")
							break;
						otherPlayerAction[j] = updateMessage[i + 4 + j];

					}
					//Remove Spaces
					otherPlayerAction.erase(std::remove(otherPlayerAction.begin(), otherPlayerAction.end(), ' '), otherPlayerAction.end());
					if (otherPlayerAction == "PLACE_BED")
					{
						std::cout << otherPlayerAction << std::endl;
						level.grid[agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() / 50][agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() / 50]->isBed = true;
					}
					else if (otherPlayerAction == "PLACE_BOX")
					{
						std::cout << otherPlayerAction << std::endl;
						level.grid[agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() / 50][agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() / 50]->isCargo = true;
					}
				}
			}
		}


		//Spawn new player
		else
		{
			otherPlayerNames.push_back(otherPlayerName);
			Agent newPlayer;
			newPlayer.characterType = "Player";
			newPlayer.agentWonderWhenIdle = false;
			newPlayer.agentCanRotate = true;

			newPlayer.setID(otherPlayerName);
			agentManager.SpawnAgent(newPlayer);
		}
	}
}



void NetworkManager::connectToServer(std::string host, int port)
{
	
}



void NetworkManager::sendTCPMessage(std::string host, int port, std::string message, boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
{
	// Fill the buffer with the data from the string
	boost::array<char, 128> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}
	//Try sending the data
	try
	{
		boost::system::error_code error;
		socket.write_some(boost::asio::buffer(buf, message.size()), error);
		//std::cout << "Message sent: " << message << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}



std::string NetworkManager::RecieveMessage(boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
{
	//Create return messages and an instream to put the buffer data into
	std::string returnMessage;
	std::stringstream inStream;
	try
	{
		boost::array<char, 128> buffer;
		boost::system::error_code error;

		// Read the data from the socket
		size_t len = socket.read_some(boost::asio::buffer(buffer), error);
		if (error == boost::asio::error::eof)
			return "QUIT"; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.

													  //Print receive message
													  //std::cout.write(buffer.data(), len);

													  // Feed the buffer data into the inStream
		inStream << (buffer.data());

		// Convert inStream to string
		returnMessage = inStream.str();
		// Remove weird character that gets stuck the the end of messages
		returnMessage.erase(std::remove(returnMessage.begin(), returnMessage.end(), 'Ì'), returnMessage.end());

		// Return String
		return returnMessage;

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

}