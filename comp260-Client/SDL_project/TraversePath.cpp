#include "stdafx.h"
#include "TraversePath.h"

TraversePath::TraversePath()
{
}


TraversePath::~TraversePath()
{
}

// Moves the player across the cell to the next cell
void TraversePath::Move(Character& characterOne, Point point)
{
	//if the x axis is the same as before, move vertically
	if (point.getX() == previousNode.getX())
		VerticalMovement(characterOne, point);

	// If the Y axis is the same as before move horizontally 
	if (point.getY() == previousNode.getY())
		HorizontalMovement(characterOne, point);

	//set the previous point to the current one
	previousNode = point;
}
void TraversePath::VerticalMovement(Character& characterOne, Point point)
{
	int pointY = point.getY() * cellSize;
	//point.getX() * (level.getCellSize() + level.getCellSize() / 2);
	//move down
	if (characterOne.getY() < pointY)
	{
		characterOne.setY(characterOne.getY() + 1);
		characterOne.direction = 0;
	}
	//move up
	if (characterOne.getY() > pointY)
	{
		characterOne.setY(characterOne.getY() - 1);
		characterOne.direction = 1;
	}
	else if (characterOne.getY() == pointY)
		IterateToNextNode(characterOne, point);
}

void TraversePath::HorizontalMovement(Character& characterOne, Point point)
{
	int pointX = point.getX() * cellSize;
	//move right
	if (characterOne.getX() < pointX)
	{
		characterOne.setX(characterOne.getX() + 1);
		characterOne.direction = 2;
	}
	//move left
	if (characterOne.getX() > pointX)
	{
		characterOne.setX(characterOne.getX() - 1);
		characterOne.direction = 3;
	}

	else if (characterOne.getX() == pointX && characterOne.getY() == point.getY())
		IterateToNextNode(characterOne, point);
}
void TraversePath::IterateToNextNode(Character& characterOne, Point point)
{
	int pointX = point.getX() * cellSize;
	int pointY = point.getY() * cellSize;
	if (characterOne.getX() == pointX && characterOne.getY() == pointY)
	{
		
		pathPointIterator++;
	}
}

Point TraversePath::getNextPoint(std::vector<Point> path)
{
	if (pathPointIterator < path.size())
		return path[pathPointIterator];

	//
	else
		pathPointIterator = 0;
		path.erase(path.begin(), path.end());
		pathComplete = false;
}