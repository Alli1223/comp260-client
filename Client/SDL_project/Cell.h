#pragma once
#include "Texture.h"
//! 
/*!

*/
class Cell
{
public:
	//! A constructor
	Cell();
	//! An alternate constructor
	/*!
	This constructor requires an X and Y for the Cell 
	*/
	Cell(int x, int y);
	//! A destructor 
	~Cell();

	// Getter functions
	//! Gets the Cell's X value
	int getX() const { return x; }
	//! Gets the Cell's Y value
	int getY() const { return y; }
	//! Gets the Cell's oxygenLevel
	int getOxygenLevel() { return oxygenLevel; }
	
	// Setter functions
	//! Sets the Cells X value
	int setX(int newX) { return x = newX; }
	//! Sets the Cells Y value
	int setY(int newY) { return y = newY; }
	//! Sets the Cell's oxygenLevel
	int setOxygenLevel(int newOxygenLevel) { return oxygenLevel = newOxygenLevel; }

	//! Whether the cell is part of a room
	bool isRoom = false;
	//! Whether the cell is walkable
	bool isWalkable = false;
	//! Whether the cell is a door is open
	bool isOpenDoor = false;
	//! Whether the cell door is closed
	bool isClosedDoor = false;
	//! Represents the goal for the player
	bool isGoal = false;
	//! The oxygenLevel of the cell
	int oxygenLevel = 100;
	//! Whether the cell is on fire
	bool isOnFire = false;
	//! Whether the cell is a hull breach
	bool isHullBreach = false;
	//! Whether the cell is an oxygen tank
	bool isOxygenTank = false;
	//! Whether the cell is an Fire extengusher
	bool isHealthPack = false;
	//!Whether the cell is the dockingpath
	bool isDockingPath = false;
	//! Whether the cell is part of the ships cargo bay
	bool isShipCargoBay = false;
	//! Whether the cell is a vertical airlock
	bool isVerticalAirlock = false;
	//! Whether the cell is a airlock side
	bool isAirlockWall = false;
	//! Whetehr the cell is cargo
	bool isCargo = false;
	//! Whether the cell is a hydroponics bay
	bool isHydroponicsBay = false;
	std::string hydroponicsOrientation = "NA";

	double noiseValue = 0;

	//! Whether the cell is a bed
	bool isBed = false;
	//! Wehther the cell is a bed and in use
	bool isOccupiedBed = false;
	//! Whether the cell is a toilet
	bool isToilet = false;
	//! Whether the cell is a toilet and in use
	bool isOccupiedToilet = false;
	//! Whether the cell is a kitchen
	bool isKitchen = false;

	

	//! cell Orientation
	int cellOrientation = 9;

private:
	//! The Cells X and Y values
	int x = 0, y = 0;
};