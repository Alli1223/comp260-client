#include "stdafx.h"
#include "RoomDesign.h"
#include "Map.h"


RoomDesign::RoomDesign()
{
}


RoomDesign::~RoomDesign()
{
}

void RoomDesign::designRoom(Level& room, int cellX, int cellY)
{

	//check cells are within level
	if (cellX - 1 >= 0 && cellX + 1 <= room.getLevelWidth() && cellY - 1 >= 0 && cellY + 2 <= room.getLevelHeight())
	{
		//RoomDesign::checkCenterCell(room, cellX, cellY);

		//sets the top and cell edges and other little edge cases
		if (cellX == 0 && room.grid[cellX][cellY]->isRoom)
		{
			room.grid[cellX][cellY]->cellOrientation = 6;
		}

		if (cellY == 0 && room.grid[cellX][cellY]->isRoom)
		{
			room.grid[cellX][cellY]->cellOrientation = 0;
		}
		if (cellY == 0 && cellX == 0)
		{
			room.grid[cellX][cellY]->cellOrientation = 7;
		}

		//Sets the top row to curved edges
		if (cellX >= 1 && room.grid[cellX][cellY]->isRoom && !room.grid[cellX - 1][cellY]->isRoom)
		{
			room.grid[cellX][cellY]->cellOrientation = 7;
		}
		if (cellX >= 1 && room.grid[cellX][cellY]->isRoom && !room.grid[cellX + 1][cellY]->isRoom)
		{
			room.grid[cellX][cellY]->cellOrientation = 1;
		}
		//sets the left edge to curved edges
		if (cellY >= 1 && room.grid[cellX][cellY]->isRoom && !room.grid[cellX][cellY - 1]->isRoom)
		{
			room.grid[cellX][cellY]->cellOrientation = 7;
		}
		if (cellY >= 1 && room.grid[cellX][cellY]->isRoom && !room.grid[cellX][cellY + 1]->isRoom)
		{
			room.grid[cellX][cellY]->cellOrientation = 5;
		}
		if (cellX == 1 && cellY == 1)
		{
			room.grid[cellX][cellY]->cellOrientation = 8;
		}



		if (cellX + 1 <= room.getLevelWidth() && cellX - 1 >= 0 && cellY + 1 <= room.getLevelHeight() && cellY - 1 >= 0)
		{
			//top
			if (room.grid[cellX][cellY]->isRoom)
			{
				if (room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX - 1][cellY]->isRoom)
					{
						if (!room.grid[cellX][cellY - 1]->isRoom)
						{
							if (room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 0;
							}
						}
					}
				}
			}




			//top and right
			if (room.grid[cellX][cellY]->isRoom)
			{
				if (!room.grid[cellX + 1][cellY]->isRoom)
				{
					if (!room.grid[cellX][cellY - 1]->isRoom)
					{
						if (room.grid[cellX][cellY + 1]->isRoom)
						{
							if (room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 1;
							}
						}
					}
				}

			}
			//right
			if (room.grid[cellX][cellY]->isRoom)
			{
				if (!room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX][cellY - 1]->isRoom)
					{
						if (room.grid[cellX][cellY + 1]->isRoom)
						{
							if (room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 2;
							}
						}
					}
				}

			}

			//right and bottom
			if (room.grid[cellX][cellY]->isRoom)
			{
				if (!room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX][cellY - 1]->isRoom)
					{
						if (!room.grid[cellX][cellY + 1]->isRoom)
						{
							if (room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 3;
							}
						}
					}
				}

			}

			//bottom

			if (room.grid[cellX][cellY]->isRoom)
			{
				if (room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX][cellY - 1]->isRoom)
					{
						if (!room.grid[cellX][cellY + 1]->isRoom)
						{
							if (room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 4;
							}
						}
					}
				}

			}

			//bottom and left

			if (room.grid[cellX][cellY]->isRoom)
			{
				if (room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX][cellY - 1]->isRoom)
					{
						if (!room.grid[cellX][cellY + 1]->isRoom)
						{
							if (!room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 5;
							}

						}
					}
				}

			}

			//left

			if (room.grid[cellX][cellY]->isRoom)
			{
				if (room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX][cellY - 1]->isRoom)
					{
						if (room.grid[cellX][cellY + 1]->isRoom)
						{
							if (!room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 6;
							}
						}
					}
				}

			}

			//left and top

			if (room.grid[cellX][cellY]->isRoom)
			{
				if (room.grid[cellX + 1][cellY]->isRoom)
				{
					if (!room.grid[cellX][cellY - 1]->isRoom)
					{
						if (room.grid[cellX][cellY + 1]->isRoom)
						{
							if (!room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 7;
							}
						}
					}
				}
			}

			//center

			if (room.grid[cellX][cellY]->isRoom)
			{
				if (room.grid[cellX + 1][cellY]->isRoom)
				{
					if (room.grid[cellX][cellY - 1]->isRoom)
					{
						if (room.grid[cellX][cellY + 1]->isRoom)
						{
							if (room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 10;
								room.grid[cellX][cellY]->isWalkable = true;
							}
						}
					}
				}
			}

			// No center
			if (!room.grid[cellX][cellY]->isRoom)
			{
				if (!room.grid[cellX + 1][cellY]->isRoom)
				{
					if (!room.grid[cellX][cellY - 1]->isRoom)
					{
						if (!room.grid[cellX][cellY + 1]->isRoom)
						{
							if (!room.grid[cellX - 1][cellY]->isRoom)
							{
								room.grid[cellX][cellY]->cellOrientation = 11;
							}
						}
					}
				}
			}
		}
	}
}


bool RoomDesign::checkCenterCell(Level& room, int cellX, int cellY)
{
	std::vector<int> directions;

	directions.push_back(-1);
	directions.push_back(0);
	directions.push_back(1);

	
	for (int x = 1; x >= -1; x--)
	{
		for (int y = -1; y <= 1; y++)
		{
			//is within the map
			if (cellX + (x)+1 <= room.getLevelWidth() && cellX + ((x) +  (-1)) >= 0 && cellY + (y) +1 <= room.getLevelHeight() && cellY + ((y) + (-1)) >= 0)
			{
				//is a room and not a door
				if (room.grid[cellX + x][cellY + y]->isRoom && !room.grid[cellX + x][cellY + y]->isOpenDoor)
				{
					
					if (room.grid[cellX + x][cellY + y]->isRoom && !room.grid[cellX][cellY]->isRoom)
					{
						room.grid[cellX + x][cellY + y]->isHullBreach = true;
						return true;
					}
				}
			}
		}
	}
}
