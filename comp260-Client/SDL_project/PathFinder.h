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
	std::vector<Point> findPath(Level& map, const Point& start, const Point& goal);
	std::vector<Point> reconstructPath(std::shared_ptr<Node> goalNode);

private:
	std::vector<std::vector<std::shared_ptr<Node>>> nodes;
	

	void addToClosedSet(std::shared_ptr<Node> node);
	void addToOpenSet(std::shared_ptr<Node> node);

	std::shared_ptr<Node> getOpenSetElementWithLowestScore();

	std::vector<std::shared_ptr<Node>> getNeighbours(std::shared_ptr<Node> node, Level& level);
	std::shared_ptr<Node> getOrCreateNode(int x, int y);
	std::shared_ptr<Node> getOrCreateNode(const Point& point);
	bool isInClosedSet(Point& point);
};

class PathfinderError : public std::exception
{
};
