#pragma once
#include"CharacterState.h"
#include "DeadState.h"
#include "SuffocatingState.h"
#include"PlayerControlledState.h"
#include"WanderingState.h"
#include"ReachedGoalState.h"

//!  The IdleState is for when there is no danger and the player is not controlling the character 
/*!
This class inherits from the CharacterState class.  The character does not do anything in the IdleState it just checks
for when it should update to another state
*/

class IdleState: public CharacterState
{
public:
	//! A constructor
	IdleState();
	//! A destructor
	~IdleState();

	//! Used to add to the timer
	double FRAME_RATE = 60;
	//! The update function that checks and updates the character state.
	/*!
	Runs on every frame of the game to check the level and update the character state.
	It takes in the Character which needs it's state updating and keyboardState to check whether the user has
	pressed the keyboard since the last update
	*/
	void update(Character& character, const Uint8* keyboardState);
private:
	//! Maxmimum time that the character should be in the Idle state
	int END_IDLE_TIME = 10;
};

