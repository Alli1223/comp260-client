#pragma once
#include "Texture.h"
#include "GameSettings.h"
class GUI 
{
public:
	GUI();
	~GUI();

	int getX() { return x; }
	int getY() { return y; }
	int setX(int newX) { return x = newX; }
	int setY(int newY) { return y = newY; }

	int getWidth() { return width; }
	int getHeight() { return height; }
	int setWidth(int newWidth) { return width = newWidth; }
	int setHeight(int newHeight) { return height = newHeight; }
	
private:
	int x;
	int y;
	int width;
	int height;
};

