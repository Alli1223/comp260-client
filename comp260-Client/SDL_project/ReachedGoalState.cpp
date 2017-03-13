#include "stdafx.h"
#include "ReachedGoalState.h"

ReachedGoalState::ReachedGoalState()
{
}

ReachedGoalState::~ReachedGoalState()
{
}

void ReachedGoalState::update(Character& character, const Uint8* keyboardState)
{
	character.hasWon = true;
}