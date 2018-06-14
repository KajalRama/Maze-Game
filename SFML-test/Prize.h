#ifndef Prize_H
#define Prize_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Entity.h"


using namespace std;

class Prize : public Entity       // Prize is derived class and Entity is the base class
{

public:
	Prize(int x, int y, int xLimit, int yLimit, std::string spriteFile, int prizeLevel);    //Parameterized constructor
	virtual int  getScoreUpdate(int timeDelay);    // update the score when player gets the prize
	virtual string say();    //set the string for the prize

	
protected:
	int prizeLevel;
	sf::Sound entitySound;      // to play the sound
	sf::SoundBuffer entitySoundBuffer;
};

#endif