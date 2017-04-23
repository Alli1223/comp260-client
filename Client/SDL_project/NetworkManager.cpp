#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

//! Gets integer values from the string
int GetGameInfo(std::string message)
{
	std::string::size_type sz;
	std::string number = "                       ";
	//Number of players
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == *"[" && message[i + 1] == *"#" && message[i + 2] == *":")
		{
			for (int j = 0; j < 10; j++)
			{
				if (message[i + 3 + j] == *"]" && message[i + 4 + j] == *".")
					break;
				number[j] = message[i + 3 + j];

			}
			number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
			int num = std::stoi(number, &sz);
			if (num < 40)
				return num;
		}
	}
}
//! main netwrok update function
void NetworkManager::NetworkUpdate(Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket)
{
	//Gets the number of current players in the game
	if (GetNumPlayers)
	{
		//Request number of current players
		sendTCPMessage("NUMBER_OF_PLAYERS_REQUEST\n", socket);
		std::string playerNumberString = RecieveMessage(socket);

		numberOfPlayers = GetGameInfo(playerNumberString);
		std::cout << "Number Of Players: " << numberOfPlayers << std::endl;
		GetNumPlayers = false;
	}

	// Request player locations
	sendTCPMessage("PLAYER_LOCATIONS_REQUEST\n", socket);

	// process the list of players
	std::string updateMessage = RecieveMessage(socket);
	ProcessArrayOfPlayerLocations(updateMessage, level, agentManager, socket);


}

void NetworkManager::runMultiThread(Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket)
{
	//std::thread t2(&NetworkManager::runMultiThread, std::ref(socket), 32);

}


//! Returns whether the player exists in the list of players
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

//! Processes an array of player locations
void NetworkManager::ProcessArrayOfPlayerLocations(std::string updateMessage, Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket)
{
	std::string temp = "                                                                                                                                     ";
	//Create a list of all the players in the update message
	std::vector<std::string> allPlayers;
	int iterator = 0;
	// if the update message is not null
	if (updateMessage != "NULL" && updateMessage != "QUIT")
	{
		int playerStart = 0, playerStop = 0;
		//loop through the message and mark the start and stop point for the player
		for (int i = 1; i < updateMessage.size(); i++)
		{
			if (updateMessage[i] == *"{")
				playerStart = i;
			else if (updateMessage[i] == *"}")
				playerStop = i;
		}
		// if the start and stop point exist in the mesage
		if (playerStart != 0 && playerStop != 0)
		{
			int j = 0;
			// push the player data to the temp string
			for (int S = playerStart + 1; S < playerStop; S++)
			{
				temp[j] = updateMessage[S];
				j++;
			}
			//remove any spaces and push that into the list of players
			temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
			allPlayers.push_back(temp);
			iterator++;
		}
	}
	//Send the player data to the process playerlocations fucntion
	for (int i = 0; i < allPlayers.size(); i++)
	{
		ProcessPlayerLocations(allPlayers[i], level, agentManager, socket);
		std::cout << allPlayers[i] << std::endl;
	}

}
//! loops through the playerdata string and puts that into the agent manager
void NetworkManager::ProcessPlayerLocations(std::string updateMessage, Level& level, AgentManager& agentManager, boost::asio::ip::tcp::socket& socket)
{
	if (updateMessage != "NULL" && updateMessage != "QUIT")
	{
		//print to console what the message is for debug purposes
		std::cout << "RECIEVE MESSAGE: " << updateMessage << std::endl;
		// Create a temp playername string to be overwirtten later
		std::string otherPlayerName = "                                                          ";

		// loop throuh the message to get the player name
		for (int i = 1; i < updateMessage.size(); i++)
		{
			if (updateMessage[i] != *">" && updateMessage[i + 1] != *" " && updateMessage[0] == *"<")
				otherPlayerName[i] = updateMessage[i];
			else
				break;
		}
		// Remove any spaces from name
		otherPlayerName.erase(std::remove(otherPlayerName.begin(), otherPlayerName.end(), ' '), otherPlayerName.end());


		// If the player already exists
		if (DoesPlayerExist(otherPlayerNames, otherPlayerName))
		{
			// If it does
			// Update Player Positions
			for (int i = 0; i < updateMessage.size(); i++)
			{
				// Don't go out of range
				if (i + 4 < updateMessage.size())
				{
					// Process X position
					if (updateMessage[i] == *"X" && updateMessage[i + 1] == *":")
					{
						// Convert string to int
						std::string::size_type sz;
						std::string updatenumber = "        ";
						updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
						// Remove white space
						updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
						int pos = std::stoi(updatenumber, &sz);
						pos *= level.getCellSize();
						if (agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getX() != pos)
							agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setX(pos);
					
					}
					//Process Y position
					if (updateMessage[i] == *"Y" && updateMessage[i + 1] == *":")
					{
						// Convert string to int
						std::string::size_type sz;
						std::string updatenumber = "            ";
						updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
						// Remove white space
						updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
						int pos = std::stoi(updatenumber, &sz);
						pos *= level.getCellSize();
						if (agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() != pos)
							agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setY(pos);
					}
					


					// Update Player Actions
					std::string otherPlayerAction = "                                                                     ";
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
						//Place bed on cell if the player places a bed
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





//! sends a tcp message to the socket
void NetworkManager::sendTCPMessage(std::string message, boost::asio::ip::tcp::socket& socket)
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


//! returns a string from the socket
std::string NetworkManager::RecieveMessage(boost::asio::ip::tcp::socket& socket)
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