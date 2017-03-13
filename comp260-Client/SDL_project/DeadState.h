#pragma once
#include"CharacterState.h"
#include"Character.h"

//!  The DeadState is for when the character's health had reached 0
/*!
This class is inherits from the CharacterState class. When the character enters the dead state
they can't leave it.
*/
class DeadState: public CharacterState
{
public:
	//! A constructor
	DeadState();
	//! A deconstructor
	~DeadState();

	//! The update function that checks and updates the character state.
	/*!
	Runs on every frame of the game to check the level and update the character state.
	It takes in the character which needs it's state updating and keyboardState to check whether the user has
	pressed the keyboard since the last update
	*/
	void update(Character& character, const Uint8* keyboardState);
};

