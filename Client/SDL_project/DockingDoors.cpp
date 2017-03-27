#include "stdafx.h"
#include "DockingDoors.h"


DockingDoors::DockingDoors() : overlayTexture("Resources\\GUI\\Docking\\overlay.png")
{
}


DockingDoors::~DockingDoors()
{
}

void DockingDoors::placeDockingDoors(SDL_Renderer* renderer, Level& level)
{
	changeOrientation();

	renderOverlay(renderer, level);

}

void DockingDoors::placeAirlockDoor(Level& level, int x, int y, int mouseY)
{
	level.grid[x][mouseY / level.getCellSize() + y]->isVerticalAirlock = true;


	if (y == -1)
	{
		level.grid[x][mouseY / level.getCellSize() + y]->isAirlockWall = true;
		level.grid[x][mouseY / level.getCellSize() + y]->isRoom = false;
	}
	else if (y == 1)
	{
		level.grid[x][mouseY / level.getCellSize() + y]->isAirlockWall = true;
		level.grid[x][mouseY / level.getCellSize() + y]->isRoom = false;
	}
	else
	{
		level.grid[x][mouseY / level.getCellSize() + y]->isClosedDoor = false;
		level.grid[x][mouseY / level.getCellSize() + y]->isOpenDoor = true;
	}
}

void DockingDoors::placeEntryPath(Level& level, int orientation)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if(mouseY < level.getLevelHeight() * level.getCellSize() - 100)
	if (orientation == 0)
	{
		for (int x = 0; x < mouseX / level.getCellSize(); x++)
		{
			if (x >= 0 && x <= level.getLevelWidth())
			{
				level.grid[x][mouseY / level.getCellSize()]->isDockingPath = true;


				if (level.grid[x][mouseY / level.getCellSize()]->isRoom)
				{

					for (int y = -1; y <= 1; y++)
					{
						placeAirlockDoor(level, x, y, mouseY);

					}
				}

			}
		}
	}
	else if (orientation == 1)
	{
		for (int x = mouseX / level.getCellSize(); x < level.getLevelWidth(); x++)
		{
			if (x >= 0 && x <= level.getLevelWidth())
			{
				level.grid[x][mouseY / level.getCellSize()]->isDockingPath = true;
				if (level.grid[x][mouseY / level.getCellSize()]->isRoom)
				{

					for (int y = -1; y <= 1; y++)
					{
						placeAirlockDoor(level, x, y, mouseY);

					}
				}
			}

		}
	}

}

void DockingDoors::renderOverlay(SDL_Renderer* renderer, Level& level)
{
	// left
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int cellSize = level.getCellSize();
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (dockOrientation == 0)
	{
		for (int x = 0; x <= mouseX / level.getCellSize(); x++)
		{
			for (int y = -1; y < 2; y++)
			{
				int xPos = x * level.getCellSize();
				int yPos = mouseY + y * level.getCellSize();


				overlayTexture.alterTransparency(50);
				overlayTexture.render(renderer, xPos, yPos, level.getCellSize(), level.getCellSize());

				if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					placeEntryPath(level, dockOrientation);
				}

			}

		}
	}

	if (dockOrientation == 1)
	{

		for (int x = mouseX / level.getCellSize(); x <= level.getLevelWidth(); x++)
		{
			for (int y = -1; y < 2; y++)
			{
				int xPos = x * level.getCellSize();
				int yPos = mouseY + y * level.getCellSize();


				overlayTexture.alterTransparency(50);
				overlayTexture.render(renderer, xPos, yPos, level.getCellSize(), level.getCellSize());

				if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					placeEntryPath(level, dockOrientation);
				}

			}


		}
	}
}

void DockingDoors::changeOrientation()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	// Left
	if (state[SDL_SCANCODE_1])
	{
		dockOrientation = 0;
	}
	// Right
	if (state[SDL_SCANCODE_2])
	{
		dockOrientation = 1;
	}
}