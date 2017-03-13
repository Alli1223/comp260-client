#include "stdafx.h"
#include "ToolBar.h"


ToolBar::ToolBar()

	: toolBarBackground("Resources\\Toolbar\\toolbarBackground.png"),
	roomCell("Resources\\roomSprites\\center.png"), emptyCell("Resources\\roomSprites\\emptyCell.png"), 
	emptyCellIcon("Resources\\Toolbar\\empty.png"),
	DoorTexture("Resources\\door_sprite.png"),
	HydroponicsIconTexture("Resources\\Toolbar\\hydroponicsIcon.png")
{

}


ToolBar::~ToolBar()
{
}

void ToolBar::RenderToolbar(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, int mouseX, int mouseY)
{
	
	toolbarSizeX = WINDOW_WIDTH - (WINDOW_WIDTH / 4);
	toolbarSizeY = WINDOW_HEIGHT / 15;
	toolbarXpos = WINDOW_WIDTH / 2;
	toolbarYpos = (WINDOW_HEIGHT - toolbarSizeY);
	int toobarIconXPos = toolbarXpos + (toolbarIconSize * 2);
	if (doOnce)
	{

		// Set the icons position and ID
		for (int i = 1; i <= numberOfIcons; i++)
		{
			Icon icon;

			auto sharedIcon = std::make_shared<Icon>(icon);
			sharedIcon->setX(toobarIconXPos);
			sharedIcon->setY(toolbarYpos);
			toobarIconXPos = toobarIconXPos + toolbarIconSize * 2;

			sharedIcon->setIconID(i);

			allIcons.push_back(sharedIcon);
		}
		doOnce = false;
	}
	
	/*
	int toobarIconXPos = toolbarXpos + (toolbarIconSize * 2);
	int iconOneXpos = toolbarXpos;
	int iconOneYpos = toolbarYpos;
	toobarIconXPos = toolbarXpos + toolbarIconSize * 2;

	int iconTwoXpos = toobarIconXPos;
	int iconTwoYpos = toolbarYpos;
	toobarIconXPos = toobarIconXPos + toolbarIconSize * 2;

	int iconThreeXpos = toobarIconXPos;
	int iconThreeYpos = toolbarYpos;
	toobarIconXPos = toobarIconXPos + toolbarIconSize * 2;

	int iconFourXpos = toobarIconXPos;
	int iconFourYpos = toolbarYpos;
	*/
	//toolBarBackground.alterTransparency(20);
	toolBarBackground.render(renderer, toolbarXpos, toolbarYpos, toolbarSizeX, toolbarSizeY);

	for each (auto icon in allIcons)
	{

		//ICON ONE
		if (icon->getIconID() == 1)
		{
			roomCell.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);


			if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
			{
				roomCell.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
				if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					setToolbarSelection(1);
				}
			}
		}
		if (icon->getIconID() == 2)
		{
			// ICON TWO
			emptyCellIcon.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
			if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
			{
				emptyCellIcon.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
				if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					setToolbarSelection(2);
				}
			}
		}
		// ICON THREE
		if (icon->getIconID() == 3)
		{
			if (numberOfItem3 > 0)
			{
				DoorTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
				if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
				{
					DoorTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						setToolbarSelection(3);
					}
				}
			}
		}
		//ICON FOUR
		if (icon->getIconID() == 4)
		{
			if (numberOfItem4 > 0)
			{
				HydroponicsIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
				if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
				{

					HydroponicsIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						setToolbarSelection(4);
					}
				}
			}
		}

		// ICON FIVE
		if (icon->getIconID() == 5)
		{
			if (numberOfItem5 > 0)
			{
				HydroponicsIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
				if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
				{

					HydroponicsIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						setToolbarSelection(5);
					}
				}
			}
		}
	}

}

void ToolBar::ToolBarFunctionality(Level& room, RoomDesign& designroom, SDL_Renderer* renderer,  int mouse_X, int mouse_Y)
{
	int toolbarSelection = getToolbarSelection();
	//Toolbar functionality
	
	if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT) && toolbarSelection == 1)
	{
		if (numberOfItem1 > 0)
		{
			if (mouse_X / room.getCellSize() - 3 > 0 && mouse_X / room.getCellSize() + 3 < room.getLevelWidth() && mouse_Y / room.getCellSize() - 3 > 0 && mouse_Y / room.getCellSize() + 3 < room.getLevelHeight())
			{
				for (int mX = (mouse_X / room.getCellSize()) - 1; mX < (mouse_X / room.getCellSize()) + 2; mX++)
				{
					for (int mY = (mouse_Y / room.getCellSize()) - 2; mY < (mouse_Y / room.getCellSize()) + 1; mY++)
					{
						room.grid[mX][mY]->isRoom = true;
					}
				}
				for (int mX = (mouse_X / room.getCellSize()) - 3; mX < (mouse_X / room.getCellSize()) + 3; mX++)
				{
					for (int mY = (mouse_Y / room.getCellSize()) - 3; mY < (mouse_Y / room.getCellSize()) + 3; mY++)
					{
						designroom.designRoom(room, mX, mY);

					}
				}
			}
		}
	}
	// Place Item 2
	
	if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT) && toolbarSelection == 2)
	{
		if (numberOfItem2 > 0)
		{
			room.grid[mouse_X / room.getCellSize()][mouse_Y / room.getCellSize()]->isRoom = false;
			room.grid[mouse_X / room.getCellSize()][mouse_Y / room.getCellSize()]->isOpenDoor = false;
			room.grid[mouse_X / room.getCellSize()][mouse_Y / room.getCellSize()]->isClosedDoor = false;
			for (int mX = (mouse_X / room.getCellSize()) - 4; mX < (mouse_X / room.getCellSize()) + 4; mX++)
			{
				for (int mY = (mouse_Y / room.getCellSize()) - 4; mY < (mouse_Y / room.getCellSize()) + 4; mY++)
				{
					designroom.designRoom(room, mX, mY);
				}
			}
		}
	}
	// Place Item 3
	if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT) && toolbarSelection == 3)
	{
		if (numberOfItem3 > 0 && !room.grid[mouse_X / room.getCellSize()][mouse_Y / room.getCellSize()]->isOpenDoor)
		{
			room.grid[mouse_X / room.getCellSize()][mouse_Y / room.getCellSize()]->isOpenDoor = true;
			numberOfItem3--;
		}
	}
	
	//Place Item 5
	if (SDL_GetMouseState(&mouse_X, &mouse_Y) && toolbarSelection == 5)
	{
		
	}
	
	

	if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		room.grid[mouse_X / room.getCellSize()][mouse_Y / room.getCellSize()]->oxygenLevel = 100;
	}
}