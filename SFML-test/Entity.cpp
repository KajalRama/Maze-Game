/****************************************************************
File:			Entity.cpp
Description:	Member function definitions for class Entity
Author:			Kajalben Patel
Class:			CSCI 120
Date:			3/21/17
I hereby certify that this program is entirely my own work.
*****************************************************************/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Entity.h"

using namespace std;

Entity::Entity()				// Default constructor
{
	x = 0;
	y = 0;
	xLimit = 0;
	yLimit = 0;
	type = DEFAULT;
}
	
Entity::Entity(int x, int y, int xLimit, int yLimit, std::string spriteFile, EntityType type)   //parameterized constructor
{
	if (!texture.loadFromFile(spriteFile)) {
		cout << "Error loading " << spriteFile << endl;
	}
	sprite = sf::Sprite(texture);
	this->x = x;
	this->y = y;
	this->xLimit = xLimit;
	this->yLimit = yLimit;
	this->spriteFile = spriteFile;
	this->type = type;
}
	
int Entity::getX()  // this will return the x position on the grid
{
	return x;
}
	
int Entity::getY() // this will return the x position on the grid
{
	return y;
}

void Entity::moveUp()  // this will move the player up
{
	if (y > 0)
		y--;
}

void Entity::moveDown()   // this will move the player down
{
	if (y < yLimit)
		y++;
}

void Entity::moveLeft()  // this will move the player left
{
	if (x > 0)
		x--;
}

void Entity::moveRight()   // this will move the player right
{
	if (x < xLimit)
		x++;
}

sf::Sprite Entity::getSprite()    // This will return the sprite
{
	return sprite;
}

EntityType Entity::getType()    // this will return the type of the entity
{
	return type;
}

int Entity::getScoreUpdate(int timeDelay)   //Return 0 for the score
{
	cout << "Entity: getScoreUpdate\n";
	return 0;
}
string Entity::say()    // This will set the entityMsg to empty string
{
	entityMsg = " ";
	return entityMsg;
}