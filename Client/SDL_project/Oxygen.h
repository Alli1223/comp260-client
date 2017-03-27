#pragma once
#include "Level.h"
#include "Cell.h"
#include "Point.h"
/*!
This class manages how the oxygen spreads through the room cells and how much oxygen is able to be placed.
*/
class Oxygen
{
public:
	//! A constructor
	Oxygen();
	//! A destructor
	~Oxygen();
	Point point;
	//! Update method updates the oxygen level each frame
	void Oxygen::update(Level& grid, int cellX, int cellY);

	//! Adds oxygen based on where the mouse was clicked
	void addOxygen(int mouseX, int mouseY, int cellSize, Level grid);

	//! Removes oxygen based on where the mouse was clicked
	void removeOxygen(Level& grid);

	//! Getter for getting the oxygen reserve level
	int getOxygenReserves() { return oxygenReserves; }
	//! Setter for setting the oxygen reserve level
	int setOxygenReserves(int newOxygenReserveLevel) { return oxygenReserves = newOxygenReserveLevel; }

	//! Gets the neighbouring cells
	std::vector<Point> Oxygen::getNeighbourCells(Point& point, Level& grid);

	//! oxygen spread rate
	int oxygenSpreadRate = 10;

	//! Initialising cellX and cellY for cell loop
	int cellX, cellY;
private:

	//! To store oxygen reserve that user can place
	int oxygenReserves = 4000;
};