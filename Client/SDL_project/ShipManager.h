#pragma once
#include "CargoShip.h"
#include "Level.h"
class ShipManager
{
public:
	//! Constructor
	ShipManager();
	//! Destructor
	~ShipManager();

	//! Spawns a ship and moves it to the dock
	void moveShipToDock(Level& level, Ship& ship, int direction);

	void shipTimer(Level& level, std::vector<Ship>& allShips);
	void findShipSpawn(Level& level, Ship& ship);
	bool shipAlreadySpawned = false;
	void createShip(std::vector<Ship>& allShips);

	void renderShip(std::vector<Ship>& allships, SDL_Renderer* renderer);

	void shipDocked(Level& level, Ship& ship);
	bool thereIsDockingPath = false;

	bool fillLevelWithCells = true;
	
	
private:
};

