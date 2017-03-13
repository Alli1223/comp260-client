#pragma once
#include "Character.h"
#include "Point.h"
#include "Level.h"
class TraversePath
{
public:
	TraversePath();

	//! Choses which direction the player should move
	void TraversePath::Move(Character& characterOne, Point point);

	//! Gets the next node for the object to walk to
	void TraversePath::IterateToNextNode(Character& characterOne, Point point);

	//! Returns the point of the next node in the path
	Point TraversePath::getNextPoint(std::vector<Point> path);

	//! Controls how he player moves vertiacally
	void TraversePath::VerticalMovement(Character& characterOne, Point point);

	//! Controls how he player moves horizontally
	void TraversePath::HorizontalMovement(Character& characterOne, Point point);

	//! contains a point of the previous node
	Point previousNode;

	//! Used for determineing what node the player is at in the path
	int pathPointIterator = 0;

	//! Using another instance of level instead
	Level level;

	//! Gets the cell size
	int cellSize = level.getCellSize();

	// Used for determineing if the path has finished
	bool pathComplete = false;

	~TraversePath();
	
};

