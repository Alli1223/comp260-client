#include "stdafx.h"
#include "AgentBehaviour.h"


AgentBehaviour::AgentBehaviour()
{
}


AgentBehaviour::~AgentBehaviour()
{
}

//Decides what the agent will do based on level info and agent needs
void AgentBehaviour::DecideTask(Level& level, Agent& agent)
{
	bool ThereisPathtobed = false;
	bool ThereisPathtoToilet = false;

	

		// Set whether the actions are possible //TODO: make this run once every few seconds, not every frame
		// Level has bed and agent is tired
		if (levelHasBed && agent.getTiredness() > tirednessThreshold && agent.isMoving == false)
		{
			// Find path to bed
			std::vector<Point> testpath = agent.pathfinder.findPath(level, agent.getAgentPointLocation(), emptyBedLocations[0]);
			if (testpath.size() > 0)
			{
				ThereisPathtobed = true;
			}
		}

		// Level has toilet and agent needs it
		if (LevelHasToilet && agent.getToietNeed() > toiletThreshold && agent.isMoving == false)
		{
			// Find path to toilet
			std::vector<Point> testpath = agent.pathfinder.findPath(level, agent.getAgentPointLocation(), emptyToiletLocations[0]);
			if (testpath.size() > 0)
			{
				ThereisPathtoToilet = true;
			}
		}

	// Initalise behaviour tree and all the possible actions
	BehaviourTree agentServicesBehaviourTree;

	// A list of leaf nodes
	//BED ACTIONS
	Action Bed(agentServicesBehaviourTree, "bed", levelHasBed), PathToBed(agentServicesBehaviourTree, "bed", ThereisPathtobed);

	//WC ACTIONS
	Action Toilet(agentServicesBehaviourTree, "wc", LevelHasToilet), PathToToilet(agentServicesBehaviourTree, "wc", ThereisPathtoToilet);


	//Create 1 selector
	BehaviourTree::Selector selector[1];

	// Create 2 sequencers
	BehaviourTree::Sequence sequence[2];

	// Set root node & add a selector that has 2 sequences 
	agentServicesBehaviourTree.setRootChild(&selector[0]);
	selector[0].addChildren({ &sequence[0], &sequence[1] });

	// Sequence of if there is a bed and the agent can walk to it
	sequence[0].addChildren({ &Bed, &PathToBed });


	// Sequence of if there is toilet and agent can walk to it
	sequence[1].addChildren({ &Toilet, &PathToToilet });


	//if the behaviour tree runs
	if (agentServicesBehaviourTree.run())
	{
		// If bed tree runs then move
		if (sequence[0].run())
			agent.Move(level, agent.getAgentPointLocation(), emptyBedLocations[0]);
		
		// else if toilet tree runs then move
		else if (sequence[1].run())
			agent.Move(level, agent.getAgentPointLocation(), emptyToiletLocations[0]);
	}
}

// Updates the local class stats about the level
void AgentBehaviour::UpdateLevelInfo(Level& level, int cellX, int cellY)
{
	if (level.grid[cellX][cellY]->isBed)
	{
		levelHasBed = true;
		emptyBedLocations.push_back(Point(cellX, cellY));
	}
	if (level.grid[cellX][cellY]->isToilet)
	{
		LevelHasToilet = true;
		emptyToiletLocations.push_back(Point(cellX, cellY));
	}
}

// Will search an area around the agent to find a cell of cellType
Point AgentBehaviour::FindNearestCelltoAgent(Agent& agent, Level& level, std::string cellType)
{
	Point endPoint;
	
	while (localSearchSize < level.grid.size())
	{
		// Do a local search of nearest cells 
		for (int x = agent.getCellX() - localSearchSize; x <= agent.getCellX() + localSearchSize; x++)
		{
			for (int y = agent.getCellY() - localSearchSize; y <= agent.getCellY() + localSearchSize; y++)
			{
				// If within grid
				if (x > 0 && y > 0 && x < level.grid.size() && y < level.grid[x].size())
				{
					if (cellType == "BED" || cellType == "Bed")
					{
						if (level.grid[x][y]->isBed)
						{
							endPoint = Point(x, y);
							return endPoint;
						}
					}
					else if (cellType == "TOILET" || cellType == "Toilet")
					{
						if (level.grid[x][y]->isToilet)
						{
							endPoint = Point(x, y);
							return endPoint;
						}
					}
				}
			}
		}
		// Double search size if not found
		localSearchSize = localSearchSize * 2;
	}
	localSearchSize = 2;

}

