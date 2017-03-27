#include "stdafx.h"
#include "PlayerStats.h"


PlayerStats::PlayerStats() : playerStatsBackgroundTexture("Resources\\GUI\\PlayerStats\\Background.png"), playerHealth("Resources\\GUI\\PlayerStats\\PlayerHealth.png"), playerOxygen("Resources\\GUI\\PlayerStats\\PlayerOxygen.png"),
playerHunger("Resources\\GUI\\PlayerStats\\PlayerHunger.png"), healthText("Resources\\GUI\\Text\\healthText.png"), oxygenText("Resources\\GUI\\Text\\oxygenText.png")
{
}


PlayerStats::~PlayerStats()
{
}

void PlayerStats::renderAndUpdatePlayerStats(SDL_Renderer* renderer, AgentManager& character, int windowWidth, int windowHeight)
{
	
	
}