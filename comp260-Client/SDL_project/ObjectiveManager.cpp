#include "stdafx.h"
#include "ObjectiveManager.h"


ObjectiveManager::ObjectiveManager()
{
}


ObjectiveManager::~ObjectiveManager()
{
}


void ObjectiveManager::SpawnObjective(Level& level, Character& npc)
{
	RetrieveCrateObjective(level, npc);
}

void ObjectiveManager::SearchForObjective(Level& level)
{
	//Search map to see if there is an objective
	for (int x = 0; x < level.grid.size(); x++)
	{
		for (int y = 0; y < level.grid.size(); y++)
		{
			if (level.grid[x][y]->isGoal)
			{
				thereIsAGoal = true;
				GoalPoint = Point(x, y);
			}
		}
	}
}
void ObjectiveManager::RetrieveCrateObjective(Level& level, Character& npc)
{
	SearchForObjective(level);

	/*Spawn a objective at random location
	if (!thereIsAGoal)
	{
		
		while (foundRandomLolcation == false)
		{
			int randomCellX = rand() % (1 + (level.grid.size() - 1));
			int randomCellY = rand() % (1 + (level.grid.size() - 1));
			if (level.grid[randomCellX][randomCellY]->isRoom && !level.grid[randomCellX][randomCellY]->isOpenDoor)
			{
				level.grid[randomCellX][randomCellY]->isGoal = true;
				thereIsAGoal = true;
				GoalPoint = Point(randomCellX, randomCellY);
				foundRandomLolcation = true;
			}
			else
				foundRandomLolcation = false;
		}

	}*/

	//if the npc reaches the goal start heading back to spawn
	if (npc.getX() / level.getCellSize() == GoalPoint.getX() && npc.getY() / level.getCellSize() == GoalPoint.getY())
	{
		//set the goal as the spawn
		GoalPoint = Point(1, 1);
		npc.hasObjective = true;

		//Drop off the objective
		if (npc.getX() / level.getCellSize() == 1 && npc.getY() / level.getCellSize() == 1)
		{
			npc.hasObjective = false;
		}
	}
}

void ObjectiveManager::NPCRetrieveCrate(Level& level, Character& npc, Pathfinder pathfinder, TraversePath& traversepath)
{
	startPoint = Point(npc.getX() / level.getCellSize(), npc.getY() / level.getCellSize());
	endPoint = GoalPoint;

	if (!pathToGoal)
	{
		path.erase(path.begin(), path.end());
		path = pathfinder.findPath(level, startPoint, endPoint);
		pathToGoal = true;
	}

	//if there is a path go along it & the npc isnt already doing an objective
	else if (pathToGoal && !npc.hasObjective)
	{
		point = traversepath.getNextPoint(path);
		traversepath.Move(npc, point);
	}

	//walk the path back if the npc has the objective
	else if (npc.hasObjective)
	{
		point = traversepath.getNextPoint(path);
		traversepath.Move(npc, point);
	}

	//when the npc reaches the goal
	if (npc.getX() / level.getCellSize() == GoalPoint.getX() && npc.getY() / level.getCellSize() == GoalPoint.getY())
	{
		level.grid[npc.getX() / level.getCellSize()][npc.getY() / level.getCellSize()]->isGoal = false;
		npc.hasObjective = true;
		pathToGoal = false;
		//erase the path and start a new one back
		path.erase(path.begin(), path.end());
		startPoint = Point(npc.getX() / level.getCellSize(), npc.getY() / level.getCellSize());
		endPoint = Point(1, 1);
		path = pathfinder.findPath(level, startPoint, endPoint);
	}

	if (npc.getX() / level.getCellSize() == 1 && npc.getY() / level.getCellSize() == 1)
	{
		npc.hasObjective = false;
		level.grid[1][1]->isGoal = true;
		thereIsAGoal = false;
	}
}

void ObjectiveManager::PickRandomCell(Level& level, Point& GoalPoint, bool thereIsAGoal)
{
	

}