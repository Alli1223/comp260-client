#pragma once
#include "Level.h"
#include "Point.h"
#include "PathFinder.h"
#include "NPC.h"
#include "TraversePath.h"

class ObjectiveManager
{
public:
	ObjectiveManager();
	~ObjectiveManager();

	void ObjectiveManager::RetrieveCrateObjective(Level& level, Character& npc);
	void ObjectiveManager::SpawnObjective(Level& level, Character& npc);
	void ObjectiveManager::NPCRetrieveCrate(Level& level, Character& npc, Pathfinder pathfinder, TraversePath& traversepath);
	void ObjectiveManager::PickRandomCell(Level& level, Point& GoalPoint, bool thereIsAGoal);
	void ObjectiveManager::SearchForObjective(Level& level);

	std::vector<Point> path;
	Point GoalPoint;
	Point point;

	bool pathToGoal = false;
	bool thereIsAGoal = false;
	bool foundRandomLolcation = false;

private:
	Point startPoint; Point endPoint;
};

