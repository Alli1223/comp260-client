#pragma once
#include "GUI.h"
#include "Texture.h"
#include "Character.h"
class PlayerStats : public GUI
{
public:
	PlayerStats();
	~PlayerStats();

	Texture playerStatsBackgroundTexture;
	Texture playerHealth;
	Texture playerOxygen;
	Texture playerHunger;
	Texture healthText;
	Texture oxygenText;

	void renderAndUpdatePlayerStats(SDL_Renderer* renderer, Character& character, int windowWidth, int windowHeight);

protected:
	int barXPos, barYPos;
	int barHeight = 20; int barWidth = 10;
};

