#pragma once
#ifndef Trap_H
#define Trap_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Entity.h"

class Trap : public Entity
{
public:
	Trap(int x, int y, int xLimit, int yLimit, std::string spriteFile, int penaltyLevel);   // parameterized constructor
	int getScoreUpdate(int timeDelay);    // update the score for the Trap
	string say();   //set the message for the Trap

private:
	int penaltyLevel;
	sf::Sound entitySound;      // to play the sound
	sf::SoundBuffer entitySoundBuffer;
};
#endif