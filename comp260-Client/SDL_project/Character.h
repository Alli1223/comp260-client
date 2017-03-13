#pragma once
#include"Level.h"
#include <boost/lambda/lambda.hpp>
class WanderingState;
class CharacterState;

//!  The abstract character class 
/*!
  This class is the base for the main character and the NPC. It contains all the functions
  needed to make the character move and react to different states.
*/
class Character
{
public:
	//! A constructor
	Character();
	//! A destructor
	~Character();
		
	//Getter methods
	//! Gets the characters X value
	int getX() { return x; }
	//! Gets the characters Y value
	int getY() { return y; }
	//! Gets the characters size
	int getSize() { return size; }
	//! Gets the characters speed
	int getSpeed() { return speed; }

	//Setter methods
	//! Sets the characters X value
	int setX(int newX) { return x = newX; }
	//! Sets the characters Y value
	int setY(int newY) { return y = newY; }
	//! Sets the characters current speed
	int setSpeed(int newSpeed) { return speed = newSpeed; }


	//! Gets and Sets the characters hunger
	double getHunger() { return Hunger; }
	double setHunger(int newHunger) { return Hunger = newHunger; }

	//Cell checking functions
	//! Checks whether a cell is a room
	bool isCellARoom(int x, int y);
	//! Checks whether a cell is a door
	bool isCellADoor(int x, int y);
	//! Gets the oxygen level of a given room
	int getOxygenLevel(int x, int y);
	//! Checks whether the player has won
	bool reachedGoal(int x, int y);
	//! Checks wether the npc has objective
	bool hasObjective = false;
	//! Checks whether the character is wandering
	bool isWandering = false;
	// Checks the keyboard input and sets a direction based on it
	void chooseDirection(const Uint8* keyboardState);
	//! Changes the character's X and Y value depending on the player's input
	void moveCharacter(const Uint8* keyboardState);


	
	
	//! An shared pointer to the character's state.
	std::shared_ptr<CharacterState> state;
	//! Shared pointer to the Level loaded in SpaceGame
	std::shared_ptr<Level> currentRoom;
	
	//! A double for the character's health
	double health = 100;
	//! A double for the character's stored oxygen
	double charactersOxygenReserves = 100;
	//! Boolean for whether character is alive
	bool isAlive = true; 
	bool hasWon = false;
	//! Integer for the random direction
	/*!
		Direction is used to decide the diretion the character 
		will move in when in the wandering state
	*/
	int direction = 1;
	//! Integer to store time spent in a state
	double timer = 0;
	//! Integers for the different movement speeds
	int suffocatingSpeed = 1, wanderSpeed = 2, walkSpeed = 3, runSpeed = 3;
	//! The three oxygen levels that are used to change alter Character's state
	int lowOxygenThershold = 40, acceptableOxygenLevel = 50, dangeroursOxygenLevel = 20;
	//! Window size decided by SpaceGame window size
	int windowWidth = 1920, windowHeight = 1080;

private:
	//! Integers for the character's X and Y position
	int x = windowWidth / 2; int y = windowHeight / 2;
	//! Integer for the character's size when rendered
	int size = 25;
	//! Integer for the characters current speed
	int speed = 3; 

	double Hunger = 100;
	int Tiredness = 0;
};

