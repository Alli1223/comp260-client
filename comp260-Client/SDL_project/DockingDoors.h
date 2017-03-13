#pragma once
#include "Level.h"
#include "Texture.h"
class DockingDoors
{
public:
	DockingDoors();
	~DockingDoors();

	Texture overlayTexture;
	int dockOrientation = 0;

	void DockingDoors::placeDockingDoors(SDL_Renderer* renderer, Level& level);
	void DockingDoors::changeOrientation();
	void DockingDoors::renderOverlay(SDL_Renderer* renderer, Level& level);
	void DockingDoors::placeEntryPath(Level& level, int orientation);
	void DockingDoors::placeAirlockDoor(Level& level, int x, int y, int mouseY);

	bool placeOnlyOnce = true;
};

