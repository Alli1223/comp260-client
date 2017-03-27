#include "stdafx.h"
#include "Map.h"


void Map::LoadMap(std::string filename, Level room)
//(filename, grid to load into) loads map from text file into grid
{

	int cellSize = room.getCellSize();
	std::ifstream mapFile(filename);
	std::vector<std::string> lines;
	width = 0;
	for (int i = 0; i < room.grid.size(); i++)
	{
		//make a vector containing all the lines in the file
		std::string line;
		std::getline(mapFile, line);
		lines.push_back(line);

		if (line.length() > width)
			width = line.length();
	}
	height = lines.size();

	RoomDesign roomdesign;
	for (int y = 0; y < height; y++)
	{
		const std::string& line = lines[y];
		for (int x = 0; x < width; x++)
		{
			char character;
			if (x < line.length())
			{
				character = line[x];
			}
			if (character == ' ')
			{
				room.grid[x][y]->isRoom = true;
			}
			if (character == '@')
			{
				room.grid[x][y]->isGoal = false;
			}
			if (character == 'D')
			{
				room.grid[x][y]->isRoom = true;
				room.grid[x][y]->isOpenDoor = true;
			}
		}
	}

	// Loop through the level and change the orientation of each cell
	for (int x = 0; x < room.grid.size() - 1; x++)
	{
		for (int y = 0; y < room.grid[x].size() - 1; y++)
		{
			roomdesign.designRoom(room, x, y);
		}
	}
}


//returns a random value
int Map::random(int smallestValue, int largestValue)
{
	std::srand(time(nullptr));
	return (rand() % (largestValue - smallestValue)) + smallestValue;
}

//Rounds a value to the nearest whole number rather than just rounding down
int roundToNearestWhole(double number) 
{
	if (number + 0.5 >= int(number) + 1)
	{
		return int(number) + 1;
	}
	else
	{
		return int(number);
	}
}

bool Map::generateRoom(Level level, int size, int entranceX, int entranceY, char direction)
{

	std::vector<std::vector<std::shared_ptr<Cell>>> room;
	double topLeftX;
	double topLeftY;
	//Finds where the top left corner of the room is when the room is being placed north
	if (direction == 'n')
	{
		topLeftX = entranceX - roundToNearestWhole(size / 2);
		topLeftY = entranceY - size;
	}
	//Finds where the top left corner of the room is when the room is being placed south
	else if (direction == 's')
	{
		topLeftX = entranceX - roundToNearestWhole(size / 2);
		topLeftY = entranceY + 1;
	}
	//Finds where the top left corner of the room is when the room is being placed east
	else if (direction == 'e')
	{
		topLeftX = entranceX + 1;
		topLeftY = entranceY - roundToNearestWhole(size / 2);
	}
	//Finds where the top left corner of the room is when the room is being placed west
	else
	{
		topLeftX = entranceX - size;
		topLeftY = entranceY - roundToNearestWhole(size / 2);
	}

	for (int x = topLeftX; x < topLeftX + size; x++)
	{
		//Detects if the room goes out the level horizontally
		if (x < 0 || x >= level.grid.size())
		{
			return false;
		}
		std::vector<std::shared_ptr<Cell>> column;
		for (int y = topLeftY; y < topLeftY + size; y++)
		{
			//Detects if the room goes out the level vertically
			if (y < 0 || y >= level.grid[0].size())
			{
				return false;
			}
			//Detects if room overlaps
			if (level.grid[x][y]->isRoom == true)
			{
				return false;
			}
			column.push_back(level.grid[x][y]);
		}
		room.push_back(column);
	}

	// Checks if it is the first room and sets the relevant oxygen level.
	int oxygenLevel;
	if (roomVector.empty())
	{
		oxygenLevel = 100;

	}
	else
	{
		int randomRoomChance = rand() % (0 - oxygenatedRoomChance);
		if (randomRoomChance == 0)
			oxygenLevel = 100;
		else
			oxygenLevel = 0;
	}

	//Gives all the cells in the room it's properties
	for (int x = 0; x < room.size(); x++)
	{
		for (int y = 0; y < room[0].size(); y++)
		{
			room[x][y]->oxygenLevel = oxygenLevel;
			room[x][y]->isRoom = true;


			// Spawn random hull breach and oxygen tanks
			int randomHullBreachChance = rand() % (0 - hullBreachSpawnChance);
			int randomOxygenTankChance = rand() % (0 - oxygenTankSpawnChance);
			int randomInitialFireSpawnChance = rand() % (0 - initialFireSpawnChance);
			int randomHealthPackChance = rand() % (0 - healthPackSpawnChance);

			// Spawns objects within the room
			if (randomHullBreachChance == 0 && !roomVector.empty())
			{
				room[x][y]->isHullBreach = true;
				room[x][y]->oxygenLevel = 0;
			}
			if (randomOxygenTankChance == 0 && !roomVector.empty())
			{
				room[x][y]->isOxygenTank = true;
				room[x][y]->setOxygenLevel(100);
			}
			if (randomHealthPackChance == 0 && room[x][y]->isOxygenTank == false)
			{
				room[x][y]->isHealthPack = true;
				room[x][y]->setOxygenLevel(100);
			}
			if (randomInitialFireSpawnChance == 0 && !roomVector.empty() && room[x][y]->isHullBreach == false && room[x][y]->oxygenLevel == 0)
			{
				room[x][y]->isOnFire = true;
				room[x][y]->setOxygenLevel(0);
			}
		}
	}
	roomVector.push_back(room);
	return true;
}

void Map::generateMap(Level level, RoomDesign& roomdesign)
{

	//Creates a seed to use
	std::srand(time(nullptr));
	//Clear a starting room(room 0)
	generateRoom(level, 3, 1, -1, 's');
	bool thereIsSpace = true;
	int roomBase = 0;

	//Makes a list of sizes to make sure that all sizes are attempted
	std::vector<int> randomSizes;

	randomSizes.push_back(3);
	randomSizes.push_back(4);
	randomSizes.push_back(5);
	randomSizes.push_back(6);
	randomSizes.push_back(7);
	randomSizes.push_back(8);
	randomSizes.push_back(9);
	randomSizes.push_back(7);
	randomSizes.push_back(8);
	randomSizes.push_back(9);

	//Makes a list of sizes to make sure that all sizes are attempted
	std::vector<int> randomDirections;

	randomDirections.push_back(0);
	randomDirections.push_back(1);
	randomDirections.push_back(2);
	randomDirections.push_back(3);
	
	//loop that makes sure to make rooms until all rooms have had all branches attempted
	while (thereIsSpace)
	{
		//loop that trys all directions
		std::random_shuffle(randomDirections.begin(), randomDirections.end());
		for (int DirectionIterator = 0; DirectionIterator < randomDirections.size(); DirectionIterator++)
		{
			int direction = randomDirections[DirectionIterator];

			//loop that trys all sizes
			std::random_shuffle(randomSizes.begin(), randomSizes.end());
			for (int sizeIterator = 0; sizeIterator < randomSizes.size(); sizeIterator++)
			{
				int size = randomSizes[sizeIterator];

				//Attempt to place a door north
				if (direction == 0)
				{
					int north = roomVector[roomBase][0][0]->getY();
					if (north > 0)
					{
						bool safe = true;
						int yOfDoor = roomVector[roomBase][0][0]->getY() - 1;
						int xStart = roomVector[roomBase][0][0]->getX();
						int halfRoomSize = roundToNearestWhole(roomVector[roomBase].size() / 2);
						int xOfDoor = xStart + halfRoomSize;
						if (xOfDoor >= level.grid.size() || xOfDoor < 0 || yOfDoor >= level.grid[0].size() || yOfDoor < 0)
						{
							safe = false;
						}
						if (safe)
						{
							if (level.grid[xOfDoor][yOfDoor]->isRoom == false)
							{
								if (generateRoom(level, size, xOfDoor, yOfDoor, 'n'))
								{
									level.grid[xOfDoor][yOfDoor]->isRoom = true;
									level.grid[xOfDoor][yOfDoor]->isOpenDoor = true;
								}
							}
						}
					}
				}
				//Attempt to place a door east
				else if (direction == 1)
				{
					int east = roomVector[roomBase][0][0]->getY();
					if (east < level.grid.size())
					{	
						bool safe = true;
						int xSize = roomVector[roomBase].size();
						int xOfDoor = roomVector[roomBase][0][0]->getX() + xSize;
						int yStart = roomVector[roomBase][0][0]->getY();
						int halfRoomSize = roundToNearestWhole(roomVector[roomBase][0].size() / 2);
						int yOfDoor = yStart + halfRoomSize;
						if (xOfDoor >= level.grid.size() || xOfDoor < 0 || yOfDoor >= level.grid[0].size() || yOfDoor < 0)
						{
							safe = false;
						}
						if (safe)
						{
							if (level.grid[xOfDoor][yOfDoor]->isRoom == false)
							{
								if (generateRoom(level, size, xOfDoor, yOfDoor, 'e'))
								{
									level.grid[xOfDoor][yOfDoor]->isRoom = true;
									level.grid[xOfDoor][yOfDoor]->isOpenDoor = true;
								}
							}
						}
					}
				}
				//Attempt to place a door south
				else if (direction == 2)
				{
					int south = roomVector[roomBase][0].size() + roomVector[roomBase][0][0]->getY() + 1;
					if (south < level.grid[0].size())
					{
						bool safe = true;
						int yOfDoor = roomVector[roomBase][0].size() + roomVector[roomBase][0][0]->getY();
						int xStart = roomVector[roomBase][0][0]->getX();
						int halfRoomSize = roundToNearestWhole(roomVector[roomBase].size() / 2);
						int xOfDoor = xStart + halfRoomSize;
						if (xOfDoor >= level.grid.size() || xOfDoor < 0 || yOfDoor >= level.grid[0].size() || yOfDoor < 0)
						{
							safe = false;
						}
						if (safe)
						{
							if (level.grid[xOfDoor][yOfDoor]->isRoom == false)
							{
								if (generateRoom(level, size, xOfDoor, yOfDoor, 's'))
								{
									level.grid[xOfDoor][yOfDoor]->isRoom = true;
									level.grid[xOfDoor][yOfDoor]->isOpenDoor = true;
								}
							}
						}
					}
				}
				//Attempt to place a door west
				else
				{
					int west = roomVector[roomBase].size() + roomVector[roomBase][0][0]->getX() + 1;
					if (west < level.grid.size())
					{
						bool safe = true;
						int xSize = roomVector[roomBase].size();
						int xOfDoor = roomVector[roomBase][0][0]->getX() - 1;
						int yStart = roomVector[roomBase][0][0]->getY();
						int halfRoomSize = roundToNearestWhole(roomVector[roomBase][0].size() / 2);
						int yOfDoor = yStart + halfRoomSize;
						if (xOfDoor >= level.grid.size() || xOfDoor < 0 || yOfDoor >= level.grid[0].size() || yOfDoor < 0)
						{
							safe = false;
						}
						if (safe)
						{
							if (level.grid[xOfDoor][yOfDoor]->isRoom == false)
							{
								if (generateRoom(level, size, xOfDoor, yOfDoor, 'w'))
								{
									level.grid[xOfDoor][yOfDoor]->isRoom = true;
									level.grid[xOfDoor][yOfDoor]->isOpenDoor = true;
								}
							}
						}
					}
				}
			}
		}
		//Check if you can attempt to place a new room
		roomBase++;
		if (roomBase  >= roomVector.size())
		{
			thereIsSpace = false;
			//Places Goal in last room generated
			roomVector[roomVector.size() - 1][roomVector[0].size() / 2][roomVector[0][0].size() / 2] ->isGoal = true;
			roomVector[roomVector.size() - 1][roomVector[0].size() / 2][roomVector[0][0].size() / 2] ->isOpenDoor = false;
			roomVector[roomVector.size() - 1][roomVector[0].size() / 2][roomVector[0][0].size() / 2]->isHullBreach = false;
			roomVector[roomVector.size() - 1][roomVector[0].size() / 2][roomVector[0][0].size() / 2]->oxygenLevel = 100;
		}
	}

	//Loops through all the cells and sets the orientation of the cells
	for (int x = 0; x < level.grid.size() - 1; x++)
	{
		for (int y = 0; y < level.grid[x].size() - 1; y++)
		{
			roomdesign.designRoom(level, x, y);
		}
	}
	
}
Map::Map()
{
}

Map::~Map()
{
}
