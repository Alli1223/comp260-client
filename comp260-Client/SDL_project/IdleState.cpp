#include "stdafx.h"
#include "IdleState.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

// Checks and updates character state
void IdleState::update(Character& character, const Uint8* keyboardState)
{
	timer = timer + (1 / FRAME_RATE); 
	
	if (character.health == 0)
	{
		character.state = std::make_shared<DeadState>();
		character.isAlive = false;
	}
	// If the oxygenLevel in a cell is beneath the lowOxygenThershold the character changes to the Suffocating state
	else if (character.getOxygenLevel(character.getX(), character.getY()) < character.lowOxygenThershold)
	{
		character.state = std::make_shared<SuffocatingState>();
		// Character move speed is reduced 
		character.setSpeed(character.suffocatingSpeed); 
	}
	// If the user has pressed WASD the character enters the PlayerControlledState
	else if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_D])
	{
		character.state = std::make_shared<PlayerControlledState>();
		character.moveCharacter(keyboardState);
	}
	// If the character is in the Idle state for too long it changes to the WanderingState
	else if (timer > END_IDLE_TIME)
	{ 
		character.state = std::make_shared<WanderingState>();
		character.isWandering = true;
		character.moveCharacter(keyboardState);
	}
	// If the character has reached the goal the game ends
	if (character.reachedGoal(character.getX(), character.getY()))
	{
		character.state = std::make_shared<ReachedGoalState>();
	}
}
