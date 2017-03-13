#include "stdafx.h"
#include "PlayerStats.h"


PlayerStats::PlayerStats() : playerStatsBackgroundTexture("Resources\\GUI\\PlayerStats\\Background.png"), playerHealth("Resources\\GUI\\PlayerStats\\PlayerHealth.png"), playerOxygen("Resources\\GUI\\PlayerStats\\PlayerOxygen.png"),
playerHunger("Resources\\GUI\\PlayerStats\\PlayerHunger.png"), healthText("Resources\\GUI\\Text\\healthText.png"), oxygenText("Resources\\GUI\\Text\\oxygenText.png")
{
}


PlayerStats::~PlayerStats()
{
}

void PlayerStats::renderAndUpdatePlayerStats(SDL_Renderer* renderer, Character& character, int windowWidth, int windowHeight)
{
	setWidth(windowWidth / 10); setHeight(windowHeight / 10);
	setX(windowWidth - getWidth()); setY(0 + (getWidth() / 2));
	playerStatsBackgroundTexture.alterTransparency(50);
	playerStatsBackgroundTexture.render(renderer, getX(), getY(), getWidth(), getHeight());

	
	barXPos = getX() + (getWidth() / 50);
	barYPos = getY() - getHeight() / 10 - 20;

	healthText.alterTransparency(200);
	healthText.render(renderer, barXPos, barYPos - barHeight, 50 + barWidth, barHeight);
	playerHealth.render(renderer, barXPos, barYPos , character.health + barWidth, barHeight);
	
	oxygenText.alterTransparency(200);
	playerOxygen.render(renderer, barXPos, barYPos + barHeight * 2, character.charactersOxygenReserves + barWidth, barHeight);
	oxygenText.render(renderer, barXPos, barYPos + barHeight, 50 + barWidth, barHeight);

	playerHunger.render(renderer, barXPos, barYPos + barHeight * 4, character.getHunger() + barWidth, barHeight);
	
}