#include "stdafx.h"
#include "PlayerControlledState.h"


PlayerControlledState::PlayerControlledState()
{
}


PlayerControlledState::~PlayerControlledState()
{
}

void PlayerControlledState::update(Character& character, const Uint8* keyboardState)
{
	character.moveCharacter(keyboardState);

	// If the health reaches 0 the character enters the dead state
	if (character.health == 0)
	{
		character.state = std::make_shared<DeadState>();
	}
	// If the keyboard input is not WASD/valid returns to idle state
	else if (!(keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_D]))
	{
		character.state = std::make_shared<IdleState>();
		character.state->timer = 0;
	}
	// Character enters suffocating state if the oxygenLevel is too low
	else if (character.getOxygenLevel(character.getX(), character.getY()) < character.lowOxygenThershold)
	{
		character.state = std::make_shared<SuffocatingState>();
		character.setSpeed(character.suffocatingSpeed);
	}
	// If the character has reached the goal the game ends
	if (character.reachedGoal(character.getX(), character.getY()))
	{
		character.state = std::make_shared<ReachedGoalState>();
	}
}
