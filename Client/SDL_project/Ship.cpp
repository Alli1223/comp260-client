#include "stdafx.h"
#include "Ship.h"



Ship::Ship() : CargoShipTexture("Resources\\Ships\\ShipOne.png")
{
}


Ship::~Ship()
{
}


void Ship::RenderShip(SDL_Renderer* renderer, Ship& ship)
{
	CargoShipTexture.render(renderer, ship.getX(), ship.getY(), ship.getWidth(), ship.getHeight());
}