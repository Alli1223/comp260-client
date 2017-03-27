#pragma once
#include "Level.h"

class CellRendering
{
public:
	CellRendering();
	~CellRendering();

	void RenderCells(Level& level, SDL_Renderer* renderer, int x, int y);

private:
	const std::string RoomSpriteTextureLocation = "Resources\\roomSprites\\texturePack\\";
	const std::string ItemsSpriteTextureLocation = "Resources\\SpawnItems\\";

	// Textures for game objects
	//! For cells that are a room
	Texture roomCell;
	//! For cells that are transparent
	Texture emptyCell;
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

	//! Is the texture for the beds
	Texture bedSideTexture;
	//! Is the texture for the toilet
	Texture toiletTexture;
	//! Is the texture for the kitchen
	Texture kitchenTexture;


	//! Is the texture for hull breaches
	Texture hullBreachTexture;
	//! Is the death animation texture
	Texture deathAnim;

	//! Are the textures for the differnt sides of the room cells
	Texture topRoomCell;
	Texture topRightRoomCell;
	Texture rightRoomCell;
	Texture bottomRightRoomCell;
	Texture bottomRoomCell;
	Texture bottomLeftRoomCell;
	Texture leftRoomCell;
	Texture topLeftRoomCell;
};

