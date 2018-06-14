#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Trap.h"

  // parameterized trap constructor calling the base constructor
Trap::Trap(int x, int y, int xLimit, int yLimit, std::string spriteFile, int penaltyLevel) : Entity(x, y, xLimit, yLimit, spriteFile, TRAP)
{
	this->penaltyLevel = penaltyLevel;

	if (!entitySoundBuffer.loadFromFile("resources/foom.wav")) {
		std::cout << "cannot open audio";
		//sf::sleep(sf::seconds(5));
		//return EXIT_FAILURE;
	}
	entitySound = sf::Sound (entitySoundBuffer);
}
int Trap::getScoreUpdate(int timeDelay)
{
	return - (penaltyLevel * 10);         // update the score based on the panelty level
}
string Trap::say()
{
	entitySound.play();
	string message = "Falling down a deep abyss causes you bodily damage";    //setting the trap message and return te=he message
	return message;
}