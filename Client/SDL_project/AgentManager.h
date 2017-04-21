#pragma once
#include"Level.h"
#include "Point.h"
#include "PathFinder.h"
#include "Texture.h"
#include "Agent.h"
#include "AgentBehaviour.h"



//!  The abstract character class 
/*!
  This class is the controller for the Agent class and will manage how the agents behave.
*/
class AgentManager
{
public:
	//! A constructor
	AgentManager();
	//! A destructor
	~AgentManager();

	//! Create an instance of AgentBehavour
	AgentBehaviour agentBehaviour;

	//! Contains a list of all the characters
	std::vector<Agent> allAgents;

	void AgentManager::UpdateAgents(std::vector<Agent>& allAgents, SDL_Renderer* renderer, Level& level);
	void AgentManager::RenderAgents(Agent& agent, SDL_Renderer* renderer, Level& level);

	//! Spawn character function (Character types are (NPC, Player)
	void AgentManager::SpawnAgent(std::string CharacterTypeVar, std::vector<Agent>& allAgents, int x, int y);
	void AgentManager::SpawnAgent(Agent& agent);

	//! Retuns the agents number
	int AgentManager::GetAgentNumberFomID(std::string ID);

	//! Erases all the agents path.
	void AgentManager::EraseAllAgentPaths(std::vector<Agent>& allAgents);

	//! Erases all the agents in the game
	void AgentManager::EraseAllAgents(std::vector<Agent>& allAgents);

	//! Whether the game will render agent stats
	bool renderStats = true;

	//! Whether the game will draw the agent paths
	bool drawAgentPaths = false;

private:
	std::string characterTextureLocation = "Resources\\Character\\";
	std::string playerStatsTextureLocation = "Resources\\GUI\\PlayerStats\\";
	//! For the Character
	Texture characterTex;
	//! Is the textures for the default character
	Texture characterLeft;
	Texture characterRight;
	Texture characterUp;
	Texture characterDown;

	//! Are the textures for the NPC
	Texture npcLeft;
	Texture npcRight;
	Texture npcUp;
	Texture npcDown;

	//! Are the textures for the statusbars
	Texture healthBarTexture;
	Texture hungerBarTexture;
	Texture tiredBarTexture;
	Texture oxygenBarTexture;
};

