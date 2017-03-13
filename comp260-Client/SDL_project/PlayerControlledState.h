#pragma once
#include "CharacterState.h"
#include "IdleState.h"
#include "DeadState.h"
#include "SuffocatingState.h"
//! The PlayerControlledState is for when the user is pressing WASD to move the character
/*!
This class checks for keyboard input and updates the character's X and Y depending on what key was pressed
*/
class PlayerControlledState :
	public CharacterState
{
	
public:
	//! A constructor
	PlayerControlledState();
	//! A destructor
	~PlayerControlledState();
	//! The update function that checks and updates the character state.
	/*!
	Runs on every frame of the game to check the level and update the character state.
	It takes in the character which needs it's state updating and keyboardState to check whether the user has
	pressed the keyboard since the last update
	*/
	void update(Character& character, const Uint8* keyboardState);
};

