#pragma once
#include "CharacterState.h"
#include "DeadState.h"
#include "IdleState.h"
//! The suffocating class is for when the character is on a cell with a low oxygen level
/*!
This class alters the characters speed and health depending on the oxygen level of the cell it's currently on 
*/

class SuffocatingState :
	public CharacterState
{
public:
	//! A constructor
	SuffocatingState();
	//! A destructor
	~SuffocatingState();
	//! The update function that checks and updates the character state.
	/*!
	Runs on every frame of the game to check the level and update the character state.
	It takes in the character which needs it's state updating and keyboardState to check whether the user has
	pressed the keyboard since the last update
	*/
	void update(Character& character, const Uint8* keyboardState);

private:
	//! Decreases the character's health
	void decreaseHealth(Character& character);
	void decreaseOxygenreserves(Character& character);
	void increaseOxygenreserves(Character& character);

};

