#pragma once
#include "Level.h"
#include "Cell.h"

class RoomDesign
{
public:
	RoomDesign();
	~RoomDesign();

	void designRoom(Level& grid, int cellX, int cellY);

	bool checkCenterCell(Level& room, int cellX, int cellY);
};

