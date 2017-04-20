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






std::string RecieveMessage(boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
{
	std::string returnMessage = "NULL";
	try
	{
		boost::array<char, 128> buffer;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buffer), error);
		if (error == boost::asio::error::eof)
			return "QUIT"; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.

		std::cout.write(buffer.data(), len);
		
		//for (int i = 0; i < buffer.size(); i++)
			//returnMessage[i] = buffer[i];

		returnMessage = (buffer.data(), len);

		return returnMessage;

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
}
void sendTCPMessage(std::string host, int port, std::string message, boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
{
	
	boost::array<char, 128> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}
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
	//std::thread networkUpdateThread(&SpaceGame::networkUpdate, socket);
}
void SpaceGame::run()
{
	// Creates a grid of cells
	level.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);

	running = true;
	unsigned int timer = 0;
	
	int cellSize = level.getCellSize();
	agentManager.renderStats = false;

	Agent player;
	player.setPosition(50, 50);
	player.characterType = "NPC";
	player.agentWonderWhenIdle = false;
	player.agentCanRotate = false;

	// Server connection deets
	int port = 2222;
	std::string IPAddress = "127.0.0.1";

	// Create socket and io service then connect to sever
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(IPAddress), port);
	socket.connect(endpoint);
	
	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());

	
	// Or Get player name (UNCOMMENT FOR FINAL)
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

	std::cout << playerName << std::endl;

	bool doOnce = true;

	/////////// MAIN LOOP /////////////////
	while (running)
	{
		// Networking
		
		//Spawn Player Once
		if (spawnPlayer)
		{
			agentManager.SpawnAgent(player);
			spawnPlayer = false;
			
		}
		

		bool runUpdate = false;

		float timer = sin(SDL_GetTicks() / 1000);
		// Do every 200 ms
		if (timer >= 0.9999 || timer <= -0.9999)
			runUpdate = true;
		
		if (runUpdate)
		{
			runUpdate = false;
			sendTCPMessage(IPAddress, port, "PLAYER_LOCATIONS_REQUEST\n", ios, socket);
			std::string updateMessage = RecieveMessage(ios, socket);
			if (updateMessage != "NULL" && updateMessage != "QUIT" && updateMessage.size() > 4)
			{
				std::vector<std::string> otherPlayers;
				Agent newPlayer;
				newPlayer.setPosition(50, 50);
				newPlayer.characterType = "NPC";
				newPlayer.agentWonderWhenIdle = false;
				newPlayer.agentCanRotate = false;


				// Go throught the other player locations
				for (char& c : updateMessage)
				{
					// Get player name
					if (&c == "<")
					{
						int i = 0;
						while (&c != ">")
						{
							otherPlayers[i].push_back(c);
							i++;
						}
					}
					// Get player location (the intValue is
					if (&c == "X")
						newPlayer.setX(c + 1 * cellSize);
					if (&c == "Y")
						newPlayer.setY(c + 1 * cellSize);
				}

				// Spawn the new player
				agentManager.SpawnAgent(newPlayer);
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
			}
			else if (state[SDL_SCANCODE_ESCAPE] && menu == true)
			{
				menu = false;
			}

			// Player Movement
			else if (state[SDL_SCANCODE_S])
			{
				agentManager.allAgents[0].setY(agentManager.allAgents[0].getY() + cellSize);
				sendTCPMessage(IPAddress, port, "MOVE_SOUTH\n", ios, socket);
			}
			else if (state[SDL_SCANCODE_A])
			{
				agentManager.allAgents[0].setX(agentManager.allAgents[0].getX() - cellSize);
				sendTCPMessage(IPAddress, port, "MOVE_WEST\n", ios, socket);
			}
			else if (state[SDL_SCANCODE_D])
			{
				agentManager.allAgents[0].setX(agentManager.allAgents[0].getX() + cellSize);
				sendTCPMessage(IPAddress, port, "MOVE_EAST\n", ios, socket);
			}
			else if (state[SDL_SCANCODE_W])
			{
				agentManager.allAgents[0].setY(agentManager.allAgents[0].getY() - cellSize);
				sendTCPMessage(IPAddress, port, "MOVE_NORTH\n", ios, socket);
			}

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


		// All agents move to mouse position
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
		{
			for (int i = 0; i < agentManager.allAgents.size(); i++)
			{
				agentManager.allAgents[i].path.erase(agentManager.allAgents[i].path.begin(), agentManager.allAgents[i].path.end());
				Point StartPoint(agentManager.allAgents[i].getCellX(), agentManager.allAgents[i].getCellY());
				Point EndPoint(mouse_X / cellSize, mouse_Y / cellSize);

				agentManager.allAgents[i].Move(level, StartPoint, EndPoint);
			}
		}
		
		
		
		

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
				RecieveMessage(ios, socket);
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