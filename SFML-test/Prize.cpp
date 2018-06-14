#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Prize.h"
    // parameterized constructor calling the base constructor
Prize::Prize(int x, int y, int xLimit, int yLimit, std::string spriteFile, int prizeLevel) :Entity(x, y, xLimit, yLimit, spriteFile, PRIZE)
{
	this->prizeLevel = prizeLevel;
	if (!entitySoundBuffer.loadFromFile("resources/Cha_Ching.wav")) {
		std::cout << "cannot open audio";
		//sf::sleep(sf::seconds(5));
		//return EXIT_FAILURE;
	}
	entitySound = sf::Sound(entitySoundBuffer);
}
int Prize::getScoreUpdate(int timeDelay)   //This willl update the score according to the timeDelay
{
	cout << "Prize: ";
	cout << (prizeLevel / (1 + timeDelay));
	return prizeLevel * 100 / (1 + timeDelay);
	
}
string Prize::say()
{
	entitySound.play();
	string message = "Magic potion increases your energy to win!";      // Set message and return the message
	return message;
}