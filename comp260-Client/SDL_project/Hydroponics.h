#pragma once
#include "Items.h"

class Hydroponics : public Items
{
public:
	Hydroponics();
	~Hydroponics();

	void Hydroponics::renderItems(SDL_Renderer* renderer, Level& level, std::vector<Hydroponics>& allHydroponicsFarms);
	void update(Level& level, std::vector<Hydroponics>& allHydroponicsFarms, int x, int y);

	bool isProducingOxygen = true;
	bool isProducingFood = true;
	bool isHydroponics = true;

	//! Texture for hydroponics
	Texture hydroponicsTexture;

	Texture leftHydroponics;
	Texture centerHydroponics;
	Texture rightHydroponics;

	std::string Orientation = "NA";

	void spawnHydroponicBase(SDL_Renderer* renderer, Level& level, std::vector<Hydroponics>& allHydroponicsFarms, int x, int y);

	int amountOfOxygenProducing = 0.1;
private:

	
};

