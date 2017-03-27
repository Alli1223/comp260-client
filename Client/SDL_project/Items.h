#pragma once
#include "Texture.h"
#include "Level.h"

class Items
{
public:
	//! Constructor
	Items();
	//! Destructor
	~Items();

	int getX() { return x; }
	int setX(int newX) {return x = newX;}

	int getY() { return y; }
	int setY(int newY) { return y = newY; }

	int getwidth() { return width; }
	int setwidth(int newwidth) { return width = newwidth; }

	int getheight() { return height; }
	int setheight(int newheight) { return height = newheight; }

	float getHealth() { return health; }
	float setHealth(int newhealth) { return health = newhealth; }

	Level level;
	

private:
	int x; int y;

	int width = level.getCellSize(); int height = level.getCellSize();

	int health = 100;
};

