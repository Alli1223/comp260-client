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
	
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(networkManager.IPAddress), networkManager.port);
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
	networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, playerName, ios, socket);
	std::string name = networkManager.RecieveMessage(ios, socket);

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
			networkManager.NetworkUpdate(level, agentManager, socket);
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
				networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "MOVE_SOUTH\n", ios, socket);
			else if (state[SDL_SCANCODE_A])
				networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "MOVE_WEST\n", ios, socket);
			else if (state[SDL_SCANCODE_D])
				networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "MOVE_EAST\n", ios, socket);
			else if (state[SDL_SCANCODE_W])
				networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "MOVE_NORTH\n", ios, socket);
			

			// Player Actions
			else if (state[SDL_SCANCODE_B])
				networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "PLACE_BED\n", ios, socket);
			else if (state[SDL_SCANCODE_C])
				networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "PLACE_BOX\n", ios, socket);


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
	networkManager.sendTCPMessage(networkManager.IPAddress, networkManager.port, "QUIT\n", ios, socket);
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