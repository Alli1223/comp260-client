#include "stdafx.h"
#include "DeadState.h"


DeadState::DeadState()
{
}


DeadState::~DeadState()
{
}

// Character can not leave the dead state 
void DeadState::update(Character& character, const Uint8* keyboardState)
{
	character.isAlive = false;
}
