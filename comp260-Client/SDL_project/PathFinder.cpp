#include "stdafx.h"
#include "PathFinder.h"


double euclideanDistance(const Point& a, const Point& b)
{
	double dx = a.getX() - a.getX();
	double dy = b.getY() - b.getY();
	return sqrt(dx*dx + dy*dy);
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

				/* uncomment for diagonal paths
				result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY() - 1));
				result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY() + 1));
				result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY() - 1));
				result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY() + 1));
				*/

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
				if (result == nullptr || f > lowestFScore)
				{
					result = node;
					lowestFScore = f;
				}
			}
		}
	}

	return result;
}

std::vector<Point> Pathfinder::findPath(Level& map, const Point& start, const Point& goal)
{
	//clear all the node for fresh pathfind
	nodes.clear();

	//create nodes for evert cell in the grid
	for (int x = 0; x < map.grid.size(); x++)
	{
		nodes.push_back(std::vector<std::shared_ptr<Node>>(map.grid.size(), nullptr));
	}

	auto startNode = getOrCreateNode(start);
	startNode->g = 0;
	startNode->h = euclideanDistance(start, goal);
	startNode->cameFrom = nullptr;
	addToOpenSet(startNode);


	//chooses the best neighbour cell to move to
	while (auto currentNode = getOpenSetElementWithLowestScore())
	{
		//if the current cell is the goal, make the path
		if (currentNode->point.getX() == goal.getX() && currentNode->point.getY() == goal.getY())
		{
			return reconstructPath(currentNode);
		}

		addToClosedSet(currentNode);

		//loops through each of the neighbours
		for (auto neighbour : getNeighbours(currentNode, map))
		{
			//if the cell is a room and not in closed set and not on fire
			if (map.grid[currentNode->point.getX()][currentNode->point.getY()]->isRoom && !isInClosedSet(neighbour->point))
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
	throw PathfinderError();
}

std::vector<Point> Pathfinder::reconstructPath(std::shared_ptr<Node> goalNode)
{
	std::vector<Point> result;
	for (auto currentNode = goalNode; currentNode; currentNode = currentNode->cameFrom)
	{
		result.insert(result.begin(), currentNode->point);
	}

	return result;
}
