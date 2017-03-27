#pragma once
#include "GUI.h"
#include "Level.h"
#include "Icon.h"



class ToolBar : public GUI
{
public:
	ToolBar();
	~ToolBar();
	
	//! Function that renders the toolbar
	void ToolBar::RenderToolbar(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, int mouseX, int mouseY);


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

	std::vector<std::shared_ptr<Icon>> allIcons;

	// IconSize
	int toolbarIconSize = 50;

	int numberOfIcons = 5;

	// How much they increase in size when mouseover
	int mouseOverSizeIncrease = 10;

	int numberOfItem1 = 15;
	int numberOfItem2 = 15;
	int numberOfItem3 = 15;
	int numberOfItem4 = 15;
	int numberOfItem5 = 15;

	bool doOnce = true;


private:
	int toolbarSelection = 1;

	int toolbarSizeX, toolbarSizeY, toolbarXpos, toolbarYpos;

};

