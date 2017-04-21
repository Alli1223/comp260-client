#include "stdafx.h"
#include "SpaceGame.h"
#include "InitialisationError.h"

SpaceGame::SpaceGame() : backgroundTexture("Resources\\background5.jpg")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}
	gameSettings.getScreenResolution();
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT / 2;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH / 2;
	window = SDL_CreateWindow("SpaceGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	
	if (window == nullptr)
	{
		throw InitialisationError("SDL_CreateWindow failed");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		throw InitialisationError("SDL_CreateRenderer failed");
	}
	
}

SpaceGame::~SpaceGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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

bool timer(int start, int currentTime, int intervalMS, bool& timer)
{
	return false;
}


std::string RecieveMessage(boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
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
void sendTCPMessage(std::string host, int port, std::string message, boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
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
	//RecieveMessage(ios, socket);
}


void SpaceGame::networkUpdate()
{
	//BORKEN
	//std::thread networkUpdateThread(&SpaceGame::networkUpdate);
	
}
void SpaceGame::run()
{
	// Creates a grid of cells
	level.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);

	running = true;
	unsigned int timer = 0;

	int cellSize = level.getCellSize();
	agentManager.renderStats = false;


	// Create socket and io service then connect to sever
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(IPAddress), port);
	socket.connect(endpoint);

	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());


	// Or Get player name
	if (clientCanEnterName)
	{
		std::cout << "ENTER YOUR NAME: " << std::endl;
		std::cin >> playerName;
		std::cout << "NAME: " << playerName << std::endl;
	}

	// add endline suffix to name
	playerName = playerName + "\n";

	// Send initial message with player name
	sendTCPMessage(IPAddress, port, playerName, ios, socket);
	std::string name = RecieveMessage(ios, socket);

	std::cout << "PlayerName: " << playerName << std::endl;


	bool MessageSent = false;
	double lastTime = SDL_GetTicks();
	double timebehind = 0;
	bool run = false;
	//bool AlwaysUpdate = tru;
	/////////// MAIN LOOP /////////////////
	while (running)
	{

		timebehind += SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();




		while (timebehind >= 50)
		{
			// Update the game.
			run = true;
			// Every time we update, we subtract a timestep from the amount we are behind.
			timebehind -= 50;
		}




		// Only run when the player moves
		if (run)
		{
			run = false;
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
								agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setX(pos);
						}
						else if (updateMessage[i] == *"Y" && updateMessage[i + 1] == *":")
						{
							// Convert string to int
							std::string::size_type sz;
							std::string updatenumber = "     ";
							updatenumber[0] = updateMessage[i + 2]; updatenumber[1] = updateMessage[i + 3]; updatenumber[2] = updateMessage[i + 4];
							// Remove white space
							updatenumber.erase(std::remove(updatenumber.begin(), updatenumber.end(), ' '), updatenumber.end());
							int pos = std::stoi(updatenumber, &sz);
							pos *= level.getCellSize();
							if(agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].getY() != pos)
								agentManager.allAgents[agentManager.GetAgentNumberFomID(otherPlayerName)].setY(pos);
						}


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

		// Synchronse the network update thread
		//networkUpdateThread.join();
		// Handle events
		SDL_Event ev;
		if (SDL_PollEvent(&ev))
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			switch (ev.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
			if (state[SDL_SCANCODE_ESCAPE] && menu == false)
			{
				menu = true;
				running = false;
			}
			else if (state[SDL_SCANCODE_ESCAPE] && menu == true)
			{
				menu = false;
			}


			// Player Movement
			else if (state[SDL_SCANCODE_S])
				sendTCPMessage(IPAddress, port, "MOVE_SOUTH\n", ios, socket);
			else if (state[SDL_SCANCODE_A])
				sendTCPMessage(IPAddress, port, "MOVE_WEST\n", ios, socket);
			else if (state[SDL_SCANCODE_D])
				sendTCPMessage(IPAddress, port, "MOVE_EAST\n", ios, socket);
			else if (state[SDL_SCANCODE_W])
				sendTCPMessage(IPAddress, port, "MOVE_NORTH\n", ios, socket);
			

			// Player Actions
			else if (state[SDL_SCANCODE_B])
				sendTCPMessage(IPAddress, port, "PLACE_BED\n", ios, socket);
			else if (state[SDL_SCANCODE_C])
				sendTCPMessage(IPAddress, port, "PLACE_BOX\n", ios, socket);


		}//End pollevent if


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Renders the background image
		backgroundTexture.render(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);



		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////

		for (int x = 0; x < level.grid.size(); x++)
		{
			for (int y = 0; y < level.grid[x].size(); y++)
			{
				//Renders all he cells
				cellrenderer.RenderCells(level, renderer, x, y);

				if (FillLevelWithCells)
				{
					level.grid[x][y]->isRoom = true;

				}

			} //End for Y loop
		}//End for X loop
		FillLevelWithCells = false;
		// Render the vector of hydroponics
		hydroponics.renderItems(renderer, level, allHydroponicsFarms);

		// Render characters
		agentManager.UpdateAgents(agentManager.allAgents, renderer, level);

		// TOOLBAR
		toolbar.ToolBarFunctionality(level, designroom, dockingdoors, hydroponics, allHydroponicsFarms, renderer, mouse_X, mouse_Y);
		toolbar.RenderToolbar(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y);





		///////////////////////////////////////
		//MENU
		//////////////////////////////////////

		if (menu)
		{
			escapemenu.RunEscapeMenu(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y, running);
			if (escapemenu.exit)
			{
				running = false;
			}
			if (escapemenu.restart)
			{
				socket.close();
				socket.connect(endpoint);
			}
		}

		// Sync threads
		//if(networkUpdateThread.joinable())
			//networkUpdateThread.join();


		SDL_RenderPresent(renderer);
	}// End while running

	// Send quit message and close socket when game ends
	sendTCPMessage(IPAddress, port, "QUIT\n", ios, socket);
	socket.close();

}


void SpaceGame::deleteVectors()
{
	allHydroponicsFarms.erase(allHydroponicsFarms.begin(), allHydroponicsFarms.end());
}

bool static isMouseOverRoomCell(Level& level)
{
	int mouse_X, mouse_Y;
	SDL_GetMouseState(&mouse_X, &mouse_Y);
	if (level.grid[mouse_X / level.getCellSize()][mouse_Y / level.getCellSize()]->isRoom)
	{
		return true;
	}
	else
	{
		return false;
	}
}