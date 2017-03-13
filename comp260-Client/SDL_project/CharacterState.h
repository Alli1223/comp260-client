#pragma once
#include"Character.h"
#include"Level.h"

//!  The character state class is used to store the character's current state
/*!
This class is the class all the other states inherit from. It is used in the Character to store the current state
*/

class CharacterState
{
public:
	//! A constructor
	CharacterState();
	//! A destructor
	~CharacterState();

	//! The update function checks and updates the character state.
	/*!
		Runs on every frame of the game to check the level and update the character state.
		It takes in the character which needs it's state updating and keyboardState to check whether the user has 
		pressed the keyboard since the last update
	*/
	virtual void update(Character& character, const Uint8* keyboardState) = 0;

	//! Used to time how long the character has been in a state
	double timer = 0;

 };