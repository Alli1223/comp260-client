#pragma once
#include "CharacterState.h"
#include "PlayerControlledState.h"
//! WanderingState makes the character move around the room randomly
/*!
If there is no danger or player input the character will be moved around the room in a random direction
*/
class WanderingState :
	public CharacterState
{
public:
	//! A constructor
	WanderingState();
	//! A destructor
	~WanderingState();

	//! The update function that checks and updates the character state.
	/*!
	Runs on every frame of the game to check the level and update the character state.
	It takes in the character which needs it's state updating and keyboardState to check whether the user has
	pressed the keyboard since the last update
	*/
	void update(Character& character, const Uint8* keyboardState);
};

