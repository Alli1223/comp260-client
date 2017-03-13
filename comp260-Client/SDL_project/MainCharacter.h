#pragma once

#include "Character.h"
#include "Level.h"

//!  The MainCharacter that will be controlled by the user
/*!
This class is for the games main character that the user will control. It inherites from the character class.
*/
class MainCharacter: public Character
{ 
public:
	//! A constructor
	MainCharacter();
	//! A destructor
	~MainCharacter();
};

