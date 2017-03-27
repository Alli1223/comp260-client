#include "stdafx.h"
#include "SpaceGame.h"
#include "InitialisationError.h"

SpaceGame::SpaceGame()
	// Texture file locations
	: roomCell("Resources\\roomSprites\\texturePack\\center.png"), emptyCell("Resources\\roomSprites\\emptyCell.png"),
	topRoomCell("Resources\\roomSprites\\texturePack\\top.png"), topRightRoomCell("Resources\\roomSprites\\texturePack\\topRight.png"), rightRoomCell("Resources\\roomSprites\\texturePack\\right.png"), bottomRightRoomCell("Resources\\roomSprites\\texturePack\\bottomRight.png"), bottomRoomCell("Resources\\roomSprites\\texturePack\\bottom.png"), bottomLeftRoomCell("Resources\\roomSprites\\texturePack\\bottomLeft.png"), leftRoomCell("Resources\\roomSprites\\texturePack\\left.png"), topLeftRoomCell("Resources\\roomSprites\\texturePack\\topLeft.png"),
	cargoBayTexture("Resources\\roomSprites\\texturePack\\cargoBayStorage.png"), cargoTexture("Resources\\roomSprites\\crate1.png"),
	characterTex("Resources\\crew2.png"), characterLeft("Resources\\Character\\crewLeft.png"), characterRight("Resources\\Character\\crewRight.png"), characterUp("Resources\\Character\\crewUp.png"), characterDown("Resources\\Character\\crewDown.png"),
	npcLeft("Resources\\Character\\npcLeft.png"), npcRight("Resources\\Character\\npcRight.png"), npcUp("Resources\\Character\\npcUp.png"), npcDown("Resources\\Character\\npcDown.png"),
	NpcTex("Resources\\Character\\NPC.png"),
	openDoorTexture("Resources\\roomSprites\\texturePack\\center.png"),
	closedDoorTexture("Resources\\roomSprites\\texturePack\\door.png"),
	oxygenTex("Resources\\oxygen.png"),
	oxygenTank("Resources\\SpawnItems\\oxygenTank.png"), healthPack("Resources\\SpawnItems\\healthPack.png"),
	healthBar("Resources\\health.png"),
	healthText("Resources\\healthText.png"),
	winTexture("Resources\\oxygenBar.png"),
	winText("Resources\\you_win.png"),
	oxygenBar("Resources\\oxygenBar.png"),
	oxygenText("Resources\\oxygenText.png"),
	gameOver("Resources\\health.png"),
	gameOverText("Resources\\game_over.png"),
	fireTexture("Resources\\SpawnItems\\fire1.png"),
	backgroundTexture("Resources\\background.png"),
	hullBreachTexture("Resources\\roomSprites\\hullBreach2.png"),
	deathAnim("Resources\\deathAnim.png"),
	goalTexture("Resources\\roomSprites\\crate1.png"){
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}
	gameSettings.getScreenResolution();
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
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
	// Level generation
	Level level;
	level.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);



	// Choose whether to generate or load a map
	//mapLoader.LoadMap("Resources\\Map\\Default_map.txt", room);
	//mapLoader.generateMap(room, designroom);


	MainCharacter characterOne;

	Cell cell;
	Point point;
	ToolBar toolbar;
	Hydroponics hydroponics;
	EscapeMenu escapemenu;



	characterOne.windowHeight = WINDOW_HEIGHT;
	characterOne.windowWidth = WINDOW_WIDTH;

	int cellSize = level.getCellSize();

	running = true;
	unsigned int timer = 0;

	while (running)
	{
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

		}//End pollevent if

		// Checks the keyboard for input
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Renders the background image
		backgroundTexture.render(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);



		for (int x = 0; x < level.grid.size(); x++)
		{
			for (int y = 0; y < level.grid[x].size(); y++)
			{
				int xPos = x * cellSize + cellSize / 2;
				int yPos = y * cellSize + cellSize / 2;

				//RENDERING THE CELLS
				if (true)
				{
					// Checks if the cell is a room
					if (level.grid[x][y]->isRoom)
					{
						oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel);
						roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
						oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
						if (level.grid[x][y]->getOxygenLevel() > 0 && level.grid[x][y]->getOxygenLevel() <= 100)
							level.grid[x][y]->setOxygenLevel(level.grid[x][y]->getOxygenLevel() - 0.5);
					}
					if (!level.grid[x][y]->isRoom)
					{
						level.grid[x][y]->setOxygenLevel(0);
						emptyCell.alterTransparency(0);
						emptyCell.render(renderer, xPos, yPos, cellSize, cellSize);
					}

					
				}
			}
		}
	} //End for Y loop
//End for X loop



		/* Renders the health and oxygen bar above player
		healthBar.render(renderer, characterOne.getX(), characterOne.getY() - 40, characterOne.health, 10);
		healthBar.alterTransparency(150);
		healthText.render(renderer, characterOne.getX(), characterOne.getY() - 40, 60, 20);
		oxygenBar.render(renderer, characterOne.getX(), characterOne.getY() - 30, oxygen.getOxygenReserves() / 40, 10);
		oxygenBar.alterTransparency(150);
		oxygenText.render(renderer, characterOne.getX(), characterOne.getY() - 30, 60, 20);
		*/


		// player orientation
	if (characterOne.direction == 0)
	{
		characterDown.render(renderer, characterOne.getX(), characterOne.getY(), characterOne.getSize(), characterOne.getSize());
	}
	else if (characterOne.direction == 1)
	{
		characterUp.render(renderer, characterOne.getX(), characterOne.getY(), characterOne.getSize(), characterOne.getSize());
	}
	else if (characterOne.direction == 2)
	{
		characterRight.render(renderer, characterOne.getX(), characterOne.getY(), characterOne.getSize(), characterOne.getSize());
	}
	else if (characterOne.direction == 3)
	{
		characterLeft.render(renderer, characterOne.getX(), characterOne.getY(), characterOne.getSize(), characterOne.getSize());
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
			SpaceGame::run();
		}
	}

	SDL_RenderPresent(renderer);
}// End while running


void SpaceGame::deleteVectors()
{

}



int SpaceGame::networkingTCP(int argc, char* argv[])
{
	
  //Time Sync
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;

}
