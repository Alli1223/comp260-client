#include "stdafx.h"
#include "PlayerInteraction.h"
#include "Character.h"
#include "level.h"
#include "Oxygen.h"



PlayerInteraction::PlayerInteraction()
{
}


PlayerInteraction::~PlayerInteraction()
{
}

void PlayerInteraction::Interaction(Level& level, Character& character, Oxygen& oxygen)
{
	
	//Gets the player X and Y values
	int pX = character.getX();
	int pY = character.getY();
	int playerX = pX / level.getCellSize();
	int playerY = pY / level.getCellSize();

	if(level.grid[playerX][playerY]->getOxygenLevel() < 100 && level.grid[playerX][playerY]->getOxygenLevel() > 0)
		level.grid[playerX][playerY]->oxygenLevel = level.grid[playerX][playerY]->getOxygenLevel() - 1;

	// If the player walks near to the door, open it
	if (playerX - doorOpenDistance > 0 && playerX + doorOpenDistance < level.getLevelWidth() && playerY - doorOpenDistance > 0 && playerY + doorOpenDistance)
	{
		for (int x = -doorOpenDistance; x < doorOpenDistance; x++)
		{
			for (int y = -doorOpenDistance; y < doorOpenDistance; y++)
			{
				if (x > (-doorOpenDistance + 1) && y >(-doorOpenDistance + 1))
				{
					if (level.grid[playerX + x][playerY + y]->isOpenDoor == true)
					{
						level.grid[playerX + x][playerY + y]->isOpenDoor = false;
						level.grid[playerX + x][playerY + y]->isClosedDoor = true;
					}
				}
			}

			if (level.grid[playerX - doorOpenDistance][playerY + x]->isClosedDoor)
			{
				level.grid[playerX - doorOpenDistance][playerY + x]->isClosedDoor = false;
				level.grid[playerX - doorOpenDistance][playerY + x]->isOpenDoor = true;
			}
			else if (level.grid[playerX + 3][playerY + x]->isClosedDoor)
			{
				level.grid[playerX + doorOpenDistance][playerY + x]->isClosedDoor = false;
				level.grid[playerX + doorOpenDistance][playerY + x]->isOpenDoor = true;
			}
			if (level.grid[playerX + x][playerY + doorOpenDistance]->isClosedDoor)
			{
				level.grid[playerX + x][playerY + doorOpenDistance]->isClosedDoor = false;
				level.grid[playerX + x][playerY + doorOpenDistance]->isOpenDoor = true;
			}
			else if (level.grid[playerX + x][playerY - 3]->isClosedDoor)
			{
				level.grid[playerX + x][playerY - doorOpenDistance]->isClosedDoor = false;
				level.grid[playerX + x][playerY - doorOpenDistance]->isOpenDoor = true;
			}
		}
	}

	// If the player walks over an oxygen tank, remove it
	if (level.grid[playerX][playerY]->isOxygenTank == true)
	{
		int currentOxygen = oxygen.getOxygenReserves();
		oxygen.setOxygenReserves(currentOxygen + 1000);
		level.grid[playerX][playerY]->isOxygenTank = false;
	}
	
	if (level.grid[playerX][playerY]->isHealthPack == true)
	{
		level.grid[playerX][playerY]->isHealthPack = false;	
		character.health = 100;
	}

	
	



}
