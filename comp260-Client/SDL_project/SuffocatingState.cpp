#include "stdafx.h"
#include "SuffocatingState.h"

SuffocatingState::SuffocatingState()
{
}

SuffocatingState::~SuffocatingState()
{
}

void SuffocatingState::update(Character& character, const Uint8* keyboardState)
{
	// If character health reaches 0 they die
	if (character.health <= 0)
	{
		character.state = std::make_shared<DeadState>();
	}	
	
	// If the oxygenLevel reaches acceptableOxygenLevel the character changes to the Idle state and moving speed increases
	if (character.getOxygenLevel(character.getX(), character.getY()) > character.acceptableOxygenLevel)
	{
		character.state = std::make_shared<IdleState>();
		character.setSpeed(character.walkSpeed);
		increaseOxygenreserves(character);
	}
	// The character can still move in the Suffocating state but speed is reduced
	else if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_D])
	{
		character.moveCharacter(keyboardState);
		
		decreaseOxygenreserves(character);
		
	}
	// Character loses health while in the suffocating state
	else
	{
		if(character.charactersOxygenReserves <= 0)
			decreaseHealth(character);
		else
		{
			decreaseOxygenreserves(character);
		}
		

	}

	// If the character has reached the goal the game ends
	if (character.reachedGoal(character.getX(), character.getY()))
	{
		character.state = std::make_shared<ReachedGoalState>();
	}
}

void SuffocatingState::decreaseHealth(Character& character)
{
		character.health = character.health - 0.4;
}

void SuffocatingState::decreaseOxygenreserves(Character& character)
{
	character.charactersOxygenReserves = character.charactersOxygenReserves - 0.4;
}
void SuffocatingState::increaseOxygenreserves(Character& character)
{
	character.charactersOxygenReserves = character.charactersOxygenReserves + 0.5;
}