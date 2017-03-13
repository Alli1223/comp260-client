#include "stdafx.h"
#include "Oxygen.h"
#include "Cell.h"
#include "MainCharacter.h"
#include "Level.h"
#include "Map.h"
#include "Fire.h"
#include "PlayerInteraction.h"



Oxygen::Oxygen()
{
}

Oxygen::~Oxygen()
{

}

//Increases oxygen in a selected cell (only if the cell is a room)
void Oxygen::addOxygen(int mouseX, int mouseY, int cellSize, Level grid)
{
	//get the cell of where the mouse was clicked
	int cellX = mouseX / cellSize;
	int cellY = mouseY / cellSize;
	grid.grid[cellX][cellY]->oxygenLevel++;
	

}

//Decreases oxygen in a selected cell
void Oxygen::removeOxygen(Level& grid)
{

	
}

//Loops through the cells to balance out the oxygen values
void Oxygen::update(Level& grid, int cellX, int cellY)
{
	point = Point(cellX, cellY);
	//OxygenLevel is set to the current cell in the loop
	int oxygenLevel = grid.grid[cellX][cellY]->getOxygenLevel();
	int oxygenReserve = getOxygenReserves();


	//Loops through the rooms but not the doors
	if (grid.grid[cellX][cellY]->isRoom && !grid.grid[cellX][cellY]->isOpenDoor)
	{
		//check cells are within level
		if (point.getX() - 1 >= 0 && point.getX() + 1 <= grid.getLevelWidth() && point.getY() - 1 >= 0 && point.getY() + 1 <= grid.getLevelHeight())
		{
			//gets neighbour cells around the point
			for (auto neighbour : getNeighbourCells(point, grid))
			{
				//check cells are within level
				if (neighbour.getX() - 1 >= 0 && neighbour.getX() + 1 <= grid.getLevelWidth() && neighbour.getY() - 1 >= 0 && neighbour.getY() + 1 <= grid.getLevelHeight())
				{
					// Cannot go thrugh closed doors
					if (!grid.grid[point.getX()][point.getY()]->isOpenDoor || !grid.grid[neighbour.getX()][neighbour.getY()]->isOpenDoor || !grid.grid[point.getX()][point.getY()]->isClosedDoor || !grid.grid[neighbour.getX()][neighbour.getY()]->isClosedDoor)
					{
						/*if the neighbour has 100 oxygen and current point has less than 100 increase current point
						if (grid.grid[point.getX()][point.getY()]->getOxygenLevel() < 100 && grid.grid[neighbour.getX()][neighbour.getY()]->getOxygenLevel() == 100)
						{
							grid.grid[point.getX()][point.getY()]->setOxygenLevel(grid.grid[point.getX()][point.getY()]->getOxygenLevel() + oxygenSpreadRate);
						}
						*/

						if (grid.grid[point.getX()][point.getY()]->getOxygenLevel() < grid.grid[neighbour.getX()][neighbour.getY()]->getOxygenLevel())
						{
							grid.grid[point.getX()][point.getY()]->setOxygenLevel(grid.grid[neighbour.getX()][neighbour.getY()]->getOxygenLevel());
						}
						
						if (grid.grid[point.getX()][point.getY()]->isOnFire)
						{
							grid.grid[point.getX()][point.getY()]->oxygenLevel = 0;
						}

					}
				}
			}
		}

	}
}
	

std::vector<Point> Oxygen::getNeighbourCells(Point point, Level& grid)
{
	//Retuns neighbouring cells
	std::vector<Point> result;

	Point leftPoint(point.getX() - 1, point.getY());
	Point rightPoint(point.getX() + 1, point.getY());
	Point topPoint(point.getX(), point.getY() - 1);
	Point bottomPoint(point.getX() - 1, point.getY() + 1);

	result.push_back(leftPoint);
	result.push_back(topPoint);
	result.push_back(rightPoint);
	result.push_back(bottomPoint);

	return result;

}