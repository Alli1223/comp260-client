#include "stdafx.h"
#include "EscapeMenu.h"
#include "SpaceGame.h"


EscapeMenu::EscapeMenu() : menuBackgroundTexture("Resources\\menuBackground1.png"),
exitButtonTexture("Resources\\exitButton1.png"),
exitButtonHighlighted("Resources\\exitButtonHighlighted1.png"),
restartButtonTexture("Resources\\restartButton.png"),
restartButtonHighlighted("Resources\\restartButtonHighlighted.png")
{
}


EscapeMenu::~EscapeMenu()
{
}

void EscapeMenu::RunEscapeMenu(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, int mouse_X, int mouse_Y, bool running)
{
	menuBackgroundTexture.alterTransparency(240);
	exitButtonTexture.alterTransparency(200);
	menuBackgroundTexture.render(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Variables to store the button locations
	int exitButton_X = WINDOW_WIDTH / 2;
	int exitButton_Y = WINDOW_HEIGHT / 2 + (WINDOW_HEIGHT / 4);
	int restartButton_X = WINDOW_WIDTH / 2;
	int restartButton_Y = WINDOW_HEIGHT / 2 + (WINDOW_HEIGHT / 3);

	exitButtonTexture.render(renderer, exitButton_X, exitButton_Y, 93, 36);
	restartButtonTexture.render(renderer, restartButton_X, restartButton_Y, 200, 25);

	// check to see if the mouse is on the button
	if (mouse_X > exitButton_X - 46 && mouse_X < exitButton_X + 46)
	{
		if (mouse_Y > exitButton_Y - 18 && mouse_Y < exitButton_Y + 18)
		{
			//highlight the button if the mouse is over it
			exitButtonHighlighted.render(renderer, exitButton_X, exitButton_Y, 93, 36);

			// If the user clicks close the game
			if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				exit = true;
			}
		}
	}
	// If the mouse goes over the restart button
	if (mouse_X > restartButton_X - 46 && mouse_X < restartButton_X + 46)
	{
		if (mouse_Y > restartButton_Y - 18 && mouse_Y < restartButton_Y + 18)
		{
			//Render the highlighted restart button
			restartButtonHighlighted.render(renderer, restartButton_X, restartButton_Y, 200, 25);

			//Restart the game if the user clicks on the button
			if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				restart = true;
			}
		}
	}
}
