#pragma once
#include "GUI.h"
#include "Level.h"
#include "RoomDesign.h"
#include "Hydroponics.h"
#include "Icon.h"
#include "DockingDoors.h"


class ToolBar : public GUI
{
public:
	ToolBar();
	~ToolBar();

	bool toolbarRender = false;
	
	//! Function that renders the toolbar
	void ToolBar::RenderToolbar(SDL_Renderer* renderer, int& WINDOW_WIDTH, int& WINDOW_HEIGHT, int& mouseX, int& mouseY);

	void ToolBar::ToolBarFunctionality(Level& level, RoomDesign& designroom, DockingDoors& dockingdoors,Hydroponics& hydroponics, std::vector<Hydroponics>& allHydroponicsFarms, SDL_Renderer* renderer, int& mouseX, int& mouseY);

	//! The getters and setters for the toolbar selection
	int getToolbarSelection() const { return toolbarSelection; }
	int setToolbarSelection(int newToolbarSelection) { return toolbarSelection = newToolbarSelection; }

	//! Getters
	int getToolbarSizeX() { return toolbarSizeX; }
	int getToolbarSizeY() { return toolbarSizeY; }
	int getToolbarXpos() { return toolbarXpos; }
	int getToolbarYpos() { return toolbarYpos; }

	// Setters
	int setToolbarSizeX(int newsizeX) { return toolbarSizeX = newsizeX; }
	int setToolbarSizeY(int newsizeY) { return toolbarSizeY = newsizeY; }
	int setToolbarXpos(int newXpos) { return toolbarXpos; }
	int setToolbarYpos(int newYpos) { return toolbarXpos; }
		

	//! Is the texture for the toolbar background
	Texture toolBarBackground;
	//! Is the texture for the room cell
	Texture roomCell;
	//! Is the texture for teh empty cell
	Texture emptyCell;
	//! Is the texture for the empty cell icon
	Texture emptyCellIcon;
	//! Is the texture for the door
	Texture DoorTexture;
	//! Is the texture for the door
	Texture HydroponicsIconTexture;
	//! Is the texture for the bed
	Texture BedIconTexture;
	//! Is the texture for the shipDock
	Texture ShipDockTexture;
	//! Is the texture for the toilet
	Texture ToiletIconTexture;

	std::vector<std::shared_ptr<Icon>> allIcons;

	//! IconSize
	int toolbarIconSize = 50;

	//! Numer of icons on the toolbar
	int numberOfIcons = 7;

	// How much they increase in size when mouseover
	int mouseOverSizeIncrease = 10;

	int numberOfItem1 = 15;
	int numberOfItem2 = 15;
	int numberOfItem3 = 15;
	int numberOfItem4 = 15;
	int numberOfItem5 = 15;
	int numberOfItem6 = 15;

	bool fillLevelWithCells = true;


private:
	int toolbarSelection = 1;

	int toolbarSizeX, toolbarSizeY, toolbarXpos, toolbarYpos;

};

