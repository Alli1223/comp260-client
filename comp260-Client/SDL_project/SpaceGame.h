#pragma once

#include "Texture.h"
#include "Level.h"
#include "Map.h"
#include "Point.h"
#include "SDL2_image-2.0.1\include\SDL_image.h"
#include "Cell.h"
#include "MainCharacter.h"
#include "NPC.h"
#include "IdleState.h"
#include "Oxygen.h"
#include "Fire.h"
#include "RoomDesign.h"
#include "PlayerInteraction.h"
#include "PathFinder.h"
#include "TraversePath.h"
#include "ObjectiveManager.h"
#include "GameSettings.h"
#include "GUI.h"
#include "ToolBar.h"
#include "Items.h"
#include "Hydroponics.h"
#include "EscapeMenu.h"
#include "DockingDoors.h"
#include "ShipManager.h"
#include "PlayerStats.h"
//! The main class
/*!
This is the main class where the game is laoded and run. 
*/
class SpaceGame
{
public:
	//! A constructor
	SpaceGame();
	//! A deconstructor
	~SpaceGame();

	const Point& getStartPoint() const { return startPoint; }
	int getStartX() const { return startPoint.getX(); }
	int getStartY() const { return startPoint.getY(); }

	//! Main Run loop
	void run();

	//! Removes all the data from stored vectors
	void SpaceGame::deleteVectors();

	GameSettings gameSettings;

	
	//! Pathfinding function
	void SpaceGame::drawPath(Point& point, Level& level);

	//! Conains the list of nodes that makes the path
	std::vector<Point> path;
	
	//! Contains a list of all the hydroponic farms
	std::vector<Hydroponics> allHydroponicsFarms;

	//! Contains a list of all the ship
	std::vector<Ship> allShips;


	//! The window width 
	int WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
	//! The window height
	int WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	//! Coordinates of the mouse 
	int mouse_X, mouse_Y;

	//! Fog of War distance
	int fogOfWar = WINDOW_WIDTH;
private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Pointer to the window that the game will be rendered in
	SDL_Window* window;
	//" Pointer to the renderer
	SDL_Renderer* renderer;

	// Textures for game objects
	//! For cells that are a room
	Texture roomCell;
	//! For cells that are transparent
	Texture emptyCell;
	//! For the Character
	Texture characterTex;
	//! For door cells
	Texture openDoorTexture;
	Texture closedDoorTexture;
	//! To show the oxygen level in a room
	Texture oxygenTex;
	//! To show oxygen tanks
	Texture oxygenTank;
	//! To show fireExtinguisher
	Texture healthPack;
	//! To show the character health
	Texture healthBar;
	//! Label for character health
	Texture healthText;
	//! To show the oxygen level
	Texture oxygenBar;
	//! Label for oxygen level
	Texture oxygenText;
	//! This will display when the player fails to win	
	Texture gameOver;
	//!will display over the background when the player fails to win
	Texture gameOverText;
	//! Is the texture for the win background
	Texture winTexture;
	//! Is the texture for the win text
	Texture winText;
	//! Is the texture for the goal
	Texture goalTexture;
	//! Is the texture for fire
	Texture fireTexture;
	//! Is the texture for the background
	Texture backgroundTexture;

	//! Is the texture for the cargoBay
	Texture cargoBayTexture;
	//! Is the texture for the cargo
	Texture cargoTexture;
	
	
	//! Is the texture for hull breaches
	Texture hullBreachTexture;
	//! Is the death animation texture
	Texture deathAnim;

	//! Are the textures for the different character orientations
	Texture characterLeft;
	Texture characterRight;
	Texture characterUp;
	Texture characterDown;

	//! Are the textures for the NPC
	Texture NpcTex;
	Texture npcLeft;
	Texture npcRight;
	Texture npcUp;
	Texture npcDown;

	//! Are the textures for the differnt sides of the room cells
	Texture topRoomCell;
	Texture topRightRoomCell;
	Texture rightRoomCell;
	Texture bottomRightRoomCell;
	Texture bottomRoomCell;
	Texture bottomLeftRoomCell;
	Texture leftRoomCell;
	Texture topLeftRoomCell;

	//! Whether the game is running or not
	bool running;
	bool menu;

	
};

