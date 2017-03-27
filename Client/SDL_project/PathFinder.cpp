#include "stdafx.h"
#include "PathFinder.h"


double euclideanDistance(const Point& a, const Point& b)
{
	double dx = a.getX() - a.getY();
	double dy = b.getX() - b.getY();
	//pythagoras(sp)
	double dist;

	dist = pow(dx, 2) + pow(dy, 2);
	dist = sqrt(dist);
	
	return dist;
}

void Pathfinder::addToClosedSet(std::shared_ptr<Node> node)
{
	node->status = NodeStatus::Closed;
}

void Pathfinder::addToOpenSet(std::shared_ptr<Node> node)
{
	node->status = NodeStatus::Open;
}

std::vector<std::shared_ptr<Node>> Pathfinder::getNeighbours(std::shared_ptr<Node> node, Level& level)
{
	std::vector<std::shared_ptr<Node>> result;
	// If the node is within the level
	if (node->point.getX() - 1 >= 0 && node->point.getX() + 1 <= level.getLevelWidth())
	{
		if (node->point.getY() - 1 >= 0 && node->point.getY() + 1 <= level.getLevelHeight())
		{
			if (node->point.getY() - 1 >= 0 && node->point.getX() - 1 >= 0)
			{
				//left
				result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY()));
				//right
				result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY()));
				//up
				result.push_back(getOrCreateNode(node->point.getX(), node->point.getY() - 1));
				//down
				result.push_back(getOrCreateNode(node->point.getX(), node->point.getY() + 1));

				// Diagonal paths
				if (diagonalPaths)
				{
					result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY() - 1));
					result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY() + 1));
					result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY() - 1));
					result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY() + 1));
				}

				return result;
			}
		}
	}
}


std::shared_ptr<Node> Pathfinder::getOrCreateNode(int x, int y)
{
	auto result = nodes[x][y];
	if (!result)
	{
		result = std::make_shared<Node>(x, y);
		nodes[x][y] = result;
	}
	return result;
}

std::shared_ptr<Node> Pathfinder::getOrCreateNode(const Point& point)
{
	return getOrCreateNode(point.getX(), point.getY());
}

bool Pathfinder::isInClosedSet(Point& point)
{
	auto node = nodes[point.getX()][point.getY()];
	return node != nullptr && node->status == NodeStatus::Closed;
}

std::shared_ptr<Node> Pathfinder::getOpenSetElementWithLowestScore()
{
	std::shared_ptr<Node> result = nullptr;
	double lowestFScore = 1e10;

	for (auto column : nodes)
	{
		for (auto node : column)
		{
			if (node != nullptr && node->status == NodeStatus::Open)
			{
				double f = node->g + node->h;
				if (result == nullptr || f < lowestFScore)
				{
					result = node;
					lowestFScore = f;
				}
			}
		}
	}

	return result;
}

std::vector<Point> Pathfinder::findPath(Level& level, const Point& start, const Point& goal)
{
	// Clear all the node for fresh pathfind
	nodes.clear();

	// Create nodes for every cell in the grid
	for (int x = 0; x < level.grid.size(); x++)
	{
		nodes.push_back(std::vector<std::shared_ptr<Node>>(level.grid.size(), nullptr));
	}

	auto startNode = getOrCreateNode(start);
	startNode->g = 0;
	startNode->h = euclideanDistance(start, goal);
	startNode->cameFrom = nullptr;
	addToOpenSet(startNode);


	// Chooses the best neighbour cell to move to
	while (auto currentNode = getOpenSetElementWithLowestScore())
	{
		//if the current cell is the goal, make the path
		if (currentNode->point.getX() == goal.getX() && currentNode->point.getY() == goal.getY())
		{
			if (StringPullPath)
				return StringPulling(reconstructPath(currentNode), level);
			else
				return reconstructPath(currentNode);
		}

		addToClosedSet(currentNode);

		// Loops through each of the neighbours
		for (auto neighbour : getNeighbours(currentNode, level))
		{
			//if the cell is a room and not in closed set and not on fire
			if (level.grid[currentNode->point.getX()][currentNode->point.getY()]->isWalkable && level.grid[currentNode->point.getX()][currentNode->point.getY()]->isRoom && !isInClosedSet(neighbour->point))
			{
				double gTentative = currentNode->g + euclideanDistance(neighbour->point, goal);

				if (neighbour->status != NodeStatus::Open || gTentative < neighbour->g)
				{
					neighbour->g = gTentative;
					neighbour->h = euclideanDistance(neighbour->point, goal);
					neighbour->cameFrom = currentNode;


					if (neighbour->status != NodeStatus::Open)
					{
						addToOpenSet(neighbour);
					}
				}
			}
		}
	}
	std::vector<Point> EmptyPath;
	return EmptyPath;
	//throw PathfinderError();
}

std::vector<Point> Pathfinder::reconstructPath(std::shared_ptr<Node> goalNode)
{
	std::vector<Point> result;
	// Goes back through the path and reconstruct it and then return the result
	for (auto currentNode = goalNode; currentNode; currentNode = currentNode->cameFrom)
	{
		result.insert(result.begin(), currentNode->point);
	}
	return result;
}

std::vector<Point> Pathfinder::StringPulling(std::vector<Point> path, Level& level)
{
	int i = 0;
	while (i + 2 < path.size())
	{
		if (isPathObsructed(level, path[i], path[i + 2]))
			path.erase(path.begin() + i + 1);
		else
			i++;
	}
	path.shrink_to_fit();
	return path;
}

// Returns false if is obstructed
bool Pathfinder::isPathObsructed(Level& level, Point firstPoint, Point secondPoint)
{
	float x1 = firstPoint.getX();
	float y1 = firstPoint.getY();
	float x2 = secondPoint.getX();
	float y2 = secondPoint.getY();

	// Bresenham's line algorithm copied and modified from internet
	//Link from source (http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B) Date accessed: 07.03.2017
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<maxX; x++)
	{
		if (steep)
		{
			if (level.grid[y][x]->isWalkable == false)
				return false;
			//SetPixel(y, x);
		}
		else
		{
			if (level.grid[x][y]->isWalkable == false)
				return false;
			//SetPixel(x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	return true;
}