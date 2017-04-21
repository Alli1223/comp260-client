#pragma once
#include "Point.h"
#include "PathFinder.h"

class Agent
{
public:
	Agent();
	~Agent();



	//! Update method for Agent
	void Agent::Update(Level& level);
	//! Movement method for Agent
	void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint);

	
	//Getter methods
	//! Gets the characters X value
	int getX() { return x; }
	//! Gets the characters Y value
	int getY() { return y; }
	//! Gets the characters X value
	int getCellX() { return cellX; }
	//! Gets the characters Y value
	int getCellY() { return cellY; }
	//! Gets the characters size
	int getSize() { return size; }
	//! Gets the characters speed
	double getSpeed() { return speed; }

	//Setter methods
	//! Sets the characters X value
	int setX(int newX) { return x = newX; }
	//! Sets the characters Y value
	int setY(int newY) { return y = newY; }
	//! Sets the characters cellX value
	int setCellX(int newCellX) { return cellX = newCellX; }
	//! Sets the characters cellY value
	int setCellY(int newCellY) { return cellY = newCellY; }
	//! Sets the position that takes 2 arguments, x and y
	int setPosition(int newX, int newY) { return x = newX, y = newY; }
	//! Sets the characters current speed
	double setSpeed(double newSpeed) { return speed = newSpeed; }
	
	//! Gets and sets the agents point location
	Point getAgentPointLocation() { return agentPointLocation; }
	Point setAgentPointLocation(Point newPointLocation) { return agentPointLocation = newPointLocation; }

	//! Character Type
	std::string characterType = "NPC";
	
	//! Agent ID
	std::string getID() { return ID; }
	std::string setID(std::string newID) { return ID = newID; }

	//!* CHARACTER PATHFINDING */
	//! Create an instance of pathfinder
	Pathfinder pathfinder;
	//! Conains the list of nodes that makes the path
	std::vector<Point> path;

	//! Contains what the current status of the agent is doing
	/*! Types of agent state: (Idle, FoundPath, Dead...)*/
	//std::string agentStatus = "Idle";
	enum agentMovementStatus { Idle, TraversingPath, Waiting };
	agentMovementStatus movementStatus = Idle;

	//! Contains what the agent needs to do the most
	/*! Types of agent state: (Food, WC, Bed...)*/
	enum agentServicesStatus { NA, Hungry, Tired, WC, Suffocating };
	agentServicesStatus agentNeed = NA;

	bool isMoving = false;

	//! Gets and Sets the agents health
	double getHealth() { return health; }
	double setHealth(double newHealth) { return health = newHealth; }

	//! Gets and Sets the agents hunger
	double getHunger() { return hunger; }
	double setHunger(double newHunger) { return hunger = newHunger; }

	//! Gets and Sets the agents tiredness (Tiredness increaes from 0)
	double getTiredness() { return tiredness; }
	double setTiredness(double newTiredness) { return tiredness = newTiredness; }

	//! Gets and Sets the agents tiredness (Tiredness increaes from 0)
	double getToietNeed() { return toiletLevel; }
	double setToiletNeed(double newToiletNeed) { return toiletLevel = newToiletNeed; }

	//! Gets and Sets the agents oxygen level
	double getOxygenLevel() { return oxygenLevel; }
	double setOxygenLevel(double newOxygenLevel) { return oxygenLevel = newOxygenLevel; }

	//! Boolean for whether character is alive
	bool isAlive = true;

	bool agentWonderWhenIdle = true;

	bool agentCanRotate = true;
	int agentRotation = 0;

private:
	std::string ID = "";
	//! Integers for the agent's X and Y position
	int x = 0; int y = 0;
	//! Integers for the agent's cellX and cellY positions below agent
	int cellX = 0; int cellY = 0;
	//! Point for where the agent is located
	Point agentPointLocation;
	//! Integer for the agent's size when rendered
	int size = 35;
	//! Integer for the agent current speed
	float speed = 2.0;
	//! A double for the agents's health
	double health = 100.0;
	//! Double to store agent hunger
	double hunger = 1.0;
	//! Integer to store agent tiredness
	double tiredness = 0.0;
	//! A Double for toilet level
	double toiletLevel = 0.0;
	//! A int for the agents's stored oxygen
	double oxygenLevel = 100.0;
	

	//! A double for storing agents health decay rate
	double healthDecayRate = 0.1;
	//! A double for storing agents hunger decay rate
	double hungerDecayRate = 0.001;
	//! A double for toilet decay rate
	double toiletDecayRate = 0.0004;
	//! A double for storing agents tiredness decay rate
	double tirednessDecayRate = 0.00010;
	//! A double for storing agents oxygen decay rate
	double oxygenDecayRate = 0.01;

	//! Stores where the agent is along the path
	int pathPointIterator = 0;
};

