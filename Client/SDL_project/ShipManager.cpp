#include "stdafx.h"
#include "ShipManager.h"


ShipManager::ShipManager()
{
}


ShipManager::~ShipManager()
{
}

void ShipManager::createShip(std::vector<Ship>& allShips)
{
	CargoShip shipOne;
	allShips.push_back(shipOne);
	shipAlreadySpawned = true;
}

void ShipManager::shipTimer(Level& level, std::vector<Ship>& allShips)
{
	int timer = SDL_GetTicks() / 1000;
	
	if (!shipAlreadySpawned && timer > 30)
	{
		createShip(allShips);
	}

	if (!thereIsDockingPath)
	{
		for (int i = 0; i < allShips.size(); i++)
			findShipSpawn(level, allShips[i]);
	}

	for (int i = 0; i < allShips.size(); i++)
	{
		if (thereIsDockingPath && !allShips[i].isDocked)
		{
			moveShipToDock(level, allShips[i], 1);
		}
	}
}

void ShipManager::renderShip(std::vector<Ship>& allships, SDL_Renderer* renderer)
{
	for each(auto ship in allships)
	{
		ship.RenderShip(renderer, ship);
	}
}



void ShipManager::findShipSpawn(Level& level, Ship& ship)
{
	// find and set intital ship spawn position
	for (int y = 0; y < level.getLevelHeight(); y++)
	{
		if (level.grid[0][y]->isDockingPath)
		{
			ship.setX(0);
			ship.setY(y * level.getCellSize() + (level.getCellSize() / 2));
			thereIsDockingPath = true;
			ship.shipPlacedOnDockingPath = true;
		}
	}
}

void ShipManager::shipDocked(Level& level, Ship& ship)
{
	int shipX = ship.getX() / level.getCellSize();
	int shipY = ship.getY() / level.getCellSize();


	//Place cargo
	for (int x = -1; x > -5; x--)
	{
		for (int y = -1; y < 2; y++)
		{
			level.grid[shipX + x][shipY + y]->isShipCargoBay = true;
			level.grid[shipX + x][shipY + y]->isRoom = true;
			level.grid[shipX + x][shipY + y]->oxygenLevel = 100;

			if (ship.getAmountOfCargo() > 0)
			{
				if (rand() % ship.getAmountOfCargo() == 0)
				{
					level.grid[shipX + x][shipY + y]->isCargo = true;
					ship.setAmountOfCargo(ship.getAmountOfCargo() - 1);
				}
			}
		}
	}




		/* Sets the ships cargo to be the size of the ship
		for (int x = -ship.getWidth() / 2 / level.getCellSize(); x < ship.getWidth() / level.getCellSize() / 2; x++)
		{
			for (int y = -ship.getHeight() / 2 / level.getCellSize(); y < ship.getHeight() / level.getCellSize() / 2; y++)
			{
				if(shipX + x > 0 && shipX - x < level.getLevelWidth() && shipY + y > 0 && shipY + y< level.getLevelHeight())
					level.grid[shipX + x][shipY + y]->isGoal = true;
			}
		}
		*/
	
	if(ship.getAmountOfCargo() < 0)
	{
		//Detach ship
	}
}


void ShipManager::moveShipToDock(Level& level, Ship& ship, int direction)
{
	ship.setX(ship.getX() + direction);

	if (level.grid[ship.getX() / level.getCellSize()][ship.getY() / level.getCellSize()]->isVerticalAirlock)
	{
		ship.setX(ship.getX());
		ship.isDocked = true;
		shipDocked(level, ship);
	}
}
