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


void sendTCPMessage(std::string host, int port, std::string message, boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
{

	boost::array<char, 128> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}

	boost::system::error_code error;
	socket.write_some(boost::asio::buffer(buf, message.size()), error);
	socket.send(boost::asio::buffer(buf, message.size()));
	std::cout << "Message: " << message << " sent." << std::endl;
	//socket.close();
}

void RecieveMessage(boost::asio::io_service& ios, boost::asio::ip::tcp::socket& socket)
{
	boost::array<char, 128> data;
	try
	{
		boost::array<char, 128> buf;
		boost::system::error_code error;


		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error == boost::asio::error::eof)
			return; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.

		std::cout.write(buf.data(), len);
		return;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
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

	// socket
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 2222);
	socket.connect(endpoint);

	// Send initial message
	sendTCPMessage("127.0.0.1", 2222, "Connecting", ios, socket);

	//Close socket and reopen
	socket.close();
	socket.connect(endpoint);


	// Main loop
	while (running)
	{
		// Networking
		
		if (spawnPlayer)
		{
			//networkClient.sendTCPMessage("127.0.0.1", 2222, "Test");
			agentManager.SpawnAgent(player);
			spawnPlayer = false;
		}

		
		//std::thread networkUpdateThread(RecieveMessage, ios, socket);

		RecieveMessage(ios, socket);


		
		//networkManager.NetworkUpdate();


		// Synchronse the network update thread
		//if(networkUpdateThread.joinable())
			//networkUpdateThread.join();
		//std::thread networkUpdate(networkManager.NetworkUpdate);


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
				sendTCPMessage("127.0.0.1", 2222, "Move Down", ios, socket);
			}
			else if (state[SDL_SCANCODE_A])
			{
				agentManager.allAgents[0].setX(agentManager.allAgents[0].getX() - cellSize);
				sendTCPMessage("127.0.0.1", 2222, "Move Left", ios, socket);
			}
			else if (state[SDL_SCANCODE_D])
			{
				agentManager.allAgents[0].setX(agentManager.allAgents[0].getX() + cellSize);
				sendTCPMessage("127.0.0.1", 2222, "Move Right", ios, socket);
			}
			else if (state[SDL_SCANCODE_W])
			{
				agentManager.allAgents[0].setY(agentManager.allAgents[0].getY() - cellSize);
				sendTCPMessage("127.0.0.1", 2222, "Move Up", ios, socket);
			}
			

			else if (state[SDL_SCANCODE_0])
			{
				agentManager.EraseAllAgents(agentManager.allAgents);
			}
			else if (state[SDL_SCANCODE_9])
			{
				agentManager.EraseAllAgentPaths(agentManager.allAgents);
			}

		}//End pollevent if

		// Checks the keyboard for input
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Renders the background image
		backgroundTexture.render(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
		
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{

			//if (level.grid[mouse_X / cellSize][mouse_Y / cellSize]->isRoom)
				//agentManager.SpawnAgent("NPC", agentManager.allAgents, mouse_X, mouse_Y);
		}
		
		


		
		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////
		
		for (int x = 0; x < level.grid.size(); x++)
		{
			for (int y = 0; y < level.grid[x].size(); y++)
			{
				//Renders all he cells
				cellrenderer.RenderCells(level, renderer, x, y);

				agentManager.agentBehaviour.UpdateLevelInfo(level, x, y);

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
				deleteVectors();
				SpaceGame::~SpaceGame();
				SpaceGame::run();
			}
		}
		SDL_RenderPresent(renderer);
	}
	//close socket when game ends
	socket.close();
	
}// End while running


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