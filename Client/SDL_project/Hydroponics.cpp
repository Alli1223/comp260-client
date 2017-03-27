#include "stdafx.h"
#include "Hydroponics.h"


Hydroponics::Hydroponics() :hydroponicsTexture("Resources\\SpawnItems\\goal2.png"), leftHydroponics("Resources\\SpawnItems\\Hydroponics\\HydroLeft.png"), centerHydroponics("Resources\\SpawnItems\\Hydroponics\\HydroCentre.png"), rightHydroponics("Resources\\SpawnItems\\Hydroponics\\HydroRight.png")
{
	
}


Hydroponics::~Hydroponics()
{
}

void Hydroponics::spawnHydroponicBase(SDL_Renderer* renderer, Level& level, std::vector<Hydroponics>& allHydroponicsFarms, int x, int y)
{
	if (level.grid[x / level.getCellSize()][y / level.getCellSize()]->isRoom)
	{
		Hydroponics hydroponics;
		int xPos = x / level.getCellSize();
		int yPos = y / level.getCellSize();

		if (xPos > 0 && yPos > 0 && xPos < level.getLevelWidth() && yPos < level.getLevelHeight())
		{


			// if there is hydro item to the left and right
			if (level.grid[xPos + 1][yPos]->isHydroponicsBay && level.grid[xPos - 1][yPos]->isHydroponicsBay)
			{

				hydroponics.Orientation = "Center";
			}


			// If there is no hydro item to the left
			if (!level.grid[xPos - 1][yPos]->isHydroponicsBay && level.grid[xPos + 1][yPos]->isHydroponicsBay)
			{
				hydroponics.Orientation = "Left";
			}
			//if there is no hydro item to right
			else if (!level.grid[xPos + 1][yPos]->isHydroponicsBay && level.grid[xPos - 1][yPos]->isHydroponicsBay)
			{
				hydroponics.Orientation = "Right";
			}


			hydroponics.setX(xPos * level.getCellSize() + (level.getCellSize() - level.getCellSize() / 2));
			hydroponics.setY(yPos *  level.getCellSize() + (level.getCellSize() - level.getCellSize() / 2));

			level.grid[x / level.getCellSize()][y / level.getCellSize()]->isHydroponicsBay = true;

			allHydroponicsFarms.push_back(hydroponics);
		}
	}
}

void Hydroponics::update(Level& level, std::vector<Hydroponics>& allHydroponicsFarms, int& x , int& y)
{
	if (isProducingOxygen && getHealth() > 0)
	{
		level.grid[x / level.getCellSize()][y / level.getCellSize()]->setOxygenLevel(level.grid[x / level.getCellSize()][y / level.getCellSize()]->getOxygenLevel() + amountOfOxygenProducing);
	}


	if (x > 0 && y > 0 && x < level.getLevelWidth() && y < level.getLevelHeight())
	{
		
	}
}

void  Hydroponics::renderItems(SDL_Renderer* renderer, Level& level, std::vector<Hydroponics>& allHydroponicsFarms)
{
	for (int iter = 0; iter < allHydroponicsFarms.size(); iter++)
	{
		if (allHydroponicsFarms[iter].isProducingOxygen)
		{
			level.grid[allHydroponicsFarms[iter].getX() / level.getCellSize()][allHydroponicsFarms[iter].getY() / level.getCellSize()]->oxygenLevel = 100;
		}
		// if the bay is left orientation
		if (allHydroponicsFarms[iter].Orientation == "Left")
		{
			leftHydroponics.render(renderer, allHydroponicsFarms[iter].getX(), allHydroponicsFarms[iter].getY(), allHydroponicsFarms[iter].getwidth(), allHydroponicsFarms[iter].getheight());
		}
		// if the bay is center orientation
		else if (allHydroponicsFarms[iter].Orientation == "Center")
		{
			centerHydroponics.render(renderer, allHydroponicsFarms[iter].getX(), allHydroponicsFarms[iter].getY(), allHydroponicsFarms[iter].getwidth(), allHydroponicsFarms[iter].getheight());
		}
		// if the bay is right orientation
		else if (allHydroponicsFarms[iter].Orientation == "Right")
		{
			rightHydroponics.render(renderer, allHydroponicsFarms[iter].getX(), allHydroponicsFarms[iter].getY(), allHydroponicsFarms[iter].getwidth(), allHydroponicsFarms[iter].getheight());
		}


		

		
	}

}
