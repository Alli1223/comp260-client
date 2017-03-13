#pragma once
#include "Texture.h"
class Ship
{
public:
	//! Constructor
	Ship();
	//! Destructor
	~Ship();

	//! Get X position
	int getX() { return x; }
	//! Get Y position
	int getY() { return y; }

	//! Set X position
	int setX(int newX) { return x = newX; }
	//! Set Y position
	int setY(int newY) { return y = newY; }

	//! Get width
	int getWidth() { return width; }
	//!Get Hight
	int getHeight() { return height; }

	// Set width and height
	int setWidth(int newWidth) { return width = newWidth; }
	int setHeight(int newHeight) { return height = newHeight; }

	//! Get and Set ship status
	std::string getShipStatus() { return shipStatus; }
	std::string setShipStatus(std::string newShipStatus) { return shipStatus = newShipStatus; }

	//! Get the ships cargo
	int getAmountOfCargo() { return amountOfCargo; }
	//! Set the ships cargo
	int setAmountOfCargo(int NewAmountOfCargo) { return amountOfCargo = NewAmountOfCargo; }

	//! If the ship has be placed on the path to the dock
	bool shipPlacedOnDockingPath = false;

	//! If the ship is docked
	bool isDocked = false;

	//renders all the ships
	void RenderShip(SDL_Renderer* renderer, Ship& ship);

	//! Is the texture for the cargo ship
	Texture CargoShipTexture;

private:
	int x, y;
	int width = 600, height = 400;
	int amountOfCargo = 3;
	std::string shipStatus = "NA";
};

