#pragma once
#include "Texture.h"
class EscapeMenu
{
public:
	EscapeMenu();
	~EscapeMenu();


	//! Is the texture for the menu background
	Texture menuBackgroundTexture;
	//! Is the texture for the exit button on the menu
	Texture exitButtonTexture;
	//! Is the texture for the highlited exit button
	Texture exitButtonHighlighted;
	//! Is the texture for the restart button
	Texture restartButtonTexture;
	//! Is the texuture for the highlighted restart button
	Texture restartButtonHighlighted;

	bool restart = false;
	bool exit = false;

	void EscapeMenu::RunEscapeMenu(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, int mouse_X, int mouse_Y, bool running);
};

