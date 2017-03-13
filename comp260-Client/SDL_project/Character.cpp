#include "stdafx.h"
#include "Character.h"
#include "Level.h"

Character::Character()
{
}


Character::~Character()
{
}


// If the player doesn't move the character it will start to move around the room in randomly selected directions
void Character::moveCharacter(const Uint8* keyboardState)
{ 
	// checks for keyboard input, if there is none it assigns a random directions
	chooseDirection(keyboardState);
	// if the direction will keep the charcter on screen and is part of a room move Character down
	if (direction == 0 && getY() + getSpeed() < windowHeight && isCellARoom(getX(), getY() + getSpeed()))
	{
		// If the Characer is wandering also check is the cell is a door
		if (isWandering == true && isCellADoor(getX(), getY() + getSpeed()))
			direction = rand() % 4;
		else
			setY(getY() + getSpeed());		
	}
	// if the direction will keep the charcter on screen and is part of a room move Character up
	else if (direction == 1 && (getY() + getSpeed()) > 0 && isCellARoom(getX(), getY() - getSpeed()))
	{
		// If the Characer is wandering also check is the cell is a door
		if (isWandering == true && isCellADoor(getX(), getY() - getSpeed()))
			direction = rand() % 4;
		else
			setY(getY() - getSpeed());
	}
	// if the direction will keep the charcter on screen and is part of a room move Character right
	else if (direction == 2 && (getX() + getSpeed()) < windowWidth && isCellARoom(getX() + getSpeed(), getY()))
	{
		// If the Characer is wandering also check is the cell is a door
		if (isWandering == true && isCellADoor(getX() + getSpeed(), getY()))
			direction = rand() % 4;
		else
			setX(getX() + getSpeed());
	}
	// if the direction will keep the charcter on screen and is part of a room move Character left
	else if (direction == 3 && (getX() - getSpeed()) > 0 && isCellARoom(getX() - getSpeed(), getY()))
	{
		// If the Characer is wandering also check is the cell is a door
		if (isWandering == true && isCellADoor(getX() - getSpeed(), getY()))
			direction = rand() % 4;
		else
			setX(getX() - getSpeed());
	}
	// If Character cannot move in current direction randomly choose a new one
	else
	{
		direction = rand() % 4;
	}
}

// Sets the direction based on keyboard input
void Character::chooseDirection(const Uint8* keyboardState)
{
	if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_UP])
	{
		direction = 1;
	}
	else if (keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN])
	{
		direction = 0;
	}
	else if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT])
	{
		direction = 3;
	}
	else if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT])
	{
		direction = 2;
	}	
}

// Checks to see if a cell is a room
bool Character::isCellARoom(int x, int y)
{
	int xCell = x / (currentRoom->getCellSize());
	int yCell = y / (currentRoom->getCellSize());
	return currentRoom->grid[xCell][yCell]->isRoom;
}

// Checks to see if a cell is a door
bool Character::isCellADoor(int x, int y)
{
	int xCell = x / currentRoom->getCellSize();
	int yCell = y / currentRoom->getCellSize();
	return currentRoom->grid[xCell][yCell]->isOpenDoor;
}

// Gets the oxygen level of the specified cell
int Character::getOxygenLevel(int x, int y)
{
	int xCell = x / currentRoom->getCellSize();
	int yCell = y / currentRoom->getCellSize();
	return currentRoom->grid[xCell][yCell]->oxygenLevel;
}

// Checks whether the cell is the goal cell
bool Character::reachedGoal(int x, int y)
{
	int xCell = x / currentRoom->getCellSize();
	int yCell = y / currentRoom->getCellSize();
	return currentRoom->grid[xCell][yCell]->isGoal;
}