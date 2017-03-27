#pragma once
#include "Map.h"
#include "Point.h"

enum class NodeStatus { None, Closed, Open };

class Node
{
public:
	Point point;
	NodeStatus status = NodeStatus::None;
	double g = 0, h = 0;
	std::shared_ptr<Node> cameFrom;

	Node(Point& point)
		: point(point)
	{
	}

	Node(int x, int y)
		: point(x, y)
	{
	}
};

struct CompareNodeByGPlusH
{
	bool operator()(const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right)
	{
		return left->g + left->h > right->g + right->h;
	}
};

class Pathfinder
{
public:
	//! Finds a path from point a to point b
	std::vector<Point> findPath(Level& map, const Point& start, const Point& goal);
	//! Returns the path that has been found
	std::vector<Point> reconstructPath(std::shared_ptr<Node> goalNode);

private:
	//! A vector of nodes that is within the level that can be searched
	std::vector<std::vector<std::shared_ptr<Node>>> nodes;
	//! This will go through the path and remove unnessasary nodes in the path
	std::vector<Point> Pathfinder::StringPulling(std::vector<Point> path, Level& level);
	//! Checks whether the path between two points is obstructed
	bool Pathfinder::isPathObsructed(Level& level, Point firstPoint, Point secondPoint);

	//! Add to closed and open set
	void addToClosedSet(std::shared_ptr<Node> node);
	void addToOpenSet(std::shared_ptr<Node> node);

	//! Get the element that is closest to the goal
	std::shared_ptr<Node> getOpenSetElementWithLowestScore();

	//! returns the nodes that are surrounding the current node
	std::vector<std::shared_ptr<Node>> getNeighbours(std::shared_ptr<Node> node, Level& level);
	//! Will get a node or create it if it doesn't exist
	std::shared_ptr<Node> getOrCreateNode(int x, int y);
	std::shared_ptr<Node> getOrCreateNode(const Point& point);
	bool isInClosedSet(Point& point);

	//! A bool that enables stringpulling
	bool StringPullPath = true;
	//! A bool that enables pathfinding to use diagonal paths
	bool diagonalPaths = true;
};

class PathfinderError : public std::exception
{
};
