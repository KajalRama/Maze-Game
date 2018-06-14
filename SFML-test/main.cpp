
/****************************************************************
File:			main.cpp
Description:	Adventure Game
Author:			Kajalben Patel
Class:			CSCI 120
Date:			3/14/2017
I hereby certify that this program is entirely my own work.
*****************************************************************/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>
#include "Entity.h"
#include "Prize.h"
#include "Trap.h"

using namespace std;

const int NUM_HORIZONTAL = 15;	// number of adventure game sprites horizontally tiled
const int NUM_VERTICAL = 10;	// number of adventure game sprites vertically tiled
const int SIZE_SPRITE = 48;		// size of a sprite (square)
const int WIDTH = SIZE_SPRITE * NUM_HORIZONTAL;	// width of the game window
const int HEIGHT = SIZE_SPRITE * (NUM_VERTICAL + 2);	// height of the game window (including score and message board)
enum Direction {NONE, UP, DOWN, LEFT, RIGHT};
// Variable that I added

int x, y;
int totalScore = 0;
string MSG = "Message: None";
//string score = "Score: 0";

/*
 * Determines and returns the type of collision between a player and another entity 
 * in a given vector. The location is based on the current position of the player 
 * moving towards the given direction of movement. In the case of colliding with 
 * a prize entity, the entity is removed from the vector.
 * @param entityPtrVector vector containing pointers to entities in the game
 * @param x x-coordinate of the current player location 
 * @param y y-coordinate of the current player location
 * @param dir direction of the player movement
 */
EntityType checkCollision(Entity* entityPtrGrid[NUM_HORIZONTAL][NUM_VERTICAL], int x, int y, Direction dir, int delay) {
	if (dir == UP) {
		y--;
	}
	else if (dir == DOWN) {
		y++;
	}
	else if (dir == LEFT) {
		x--;
	}
	else if (dir == RIGHT) {
		x++;
	}
	if (x >= 0 && y >= 0 && x < NUM_HORIZONTAL && y < NUM_VERTICAL && entityPtrGrid[x][y] != NULL) {	
		Entity* entity = entityPtrGrid[x][y];
		// Following will check if collision type is prize then print the message and score accordingly
			if (entity->getType() == PRIZE)
			{
				totalScore += entity->getScoreUpdate(delay);     // Call the getScoreUpdate function to undate the score
				cout << "print the delay: " << delay;
				cout << "\n The score is: " << totalScore;
				MSG = entity->say();	// Call the Say function to print the message
			
				cout << "\nmessage ========" << MSG << endl;
				delete entity;
				entityPtrGrid[x][y] = NULL;
				return PRIZE;
			}
			// Following will check if collision type is Trap then print the message and score accordingly
			if (entity-> getType() == TRAP)
			{
				totalScore += entity->getScoreUpdate(delay);	// Call the getScoreUpdate function to undate the score
				cout << "\n The score is: " << totalScore;
				MSG = entity->say();							// Call the Say function to print the message
				cout << "\nmessage ========" << MSG << endl;
				delete entity;
				entityPtrGrid[x][y] = NULL;
				return TRAP;
			}
			if (entity->getType() == DESTINATION)				// Check if the collision is with the destination
			{
				system("PAUSE");								// Player will stop moving when reaches the destination
			}
			else
				return entityPtrGrid[x][y]->getType();
		}

	return UNKNOWN;
}

int main()
{
	Entity* entityPtrGrid[NUM_HORIZONTAL][NUM_VERTICAL];		// vector containing all game entities (player, prizes, walls)
	
	for (int i = 0; i < NUM_HORIZONTAL; ++i)
		for (int j = 0; j < NUM_VERTICAL; ++j)
			entityPtrGrid[i][j] = NULL;

	srand((unsigned int)time(0));

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CSCI 120 - Maze Adventure Project");

	// create player entity
	Entity player(0, 0, NUM_HORIZONTAL - 1, NUM_VERTICAL - 1, "resources/alice.png", PLAYER);
	entityPtrGrid[0][0] = &player;

	// create 20 wall entity

	for (int i = 0; i < 20; i++)
	{
		x = rand() % NUM_HORIZONTAL;		// Will generate random X value on the grid 
		y = rand() % NUM_VERTICAL;			// Will generate random Y value on the grid 
		while (entityPtrGrid[x][y] != NULL)   // to check if its overlapping or not
		{
			x = rand() % NUM_HORIZONTAL;     // if it overlapps then generate new x and y untill it finds new unoccupied space
			y = rand() % NUM_VERTICAL;
		}
		entityPtrGrid[x][y] = new Entity(x, y, NUM_HORIZONTAL - 1, NUM_VERTICAL - 1, "resources/wall.png", WALL); // This will create new pointer for the wall entity
	}
	
	
	// create  5 prize entities
	for (int i = 0; i < 5; i++)
	{
		x = rand() % NUM_HORIZONTAL;		//Will generate random X value on the grid 
		y = rand() % NUM_VERTICAL;			//Will generate random Y value on the grid 
		while (entityPtrGrid[x][y] != NULL)   // to check if its overlapping or not
		{
			x = rand() % NUM_HORIZONTAL;     // if it overlapps then generate new x and y untill it finds new unoccupied space
			y = rand() % NUM_VERTICAL;
		}
		entityPtrGrid[x][y] = new Prize(x, y, NUM_HORIZONTAL - 1, NUM_VERTICAL - 1, "resources/burger.png", 5); // This will create new pointer for the prize entity
	}
	
	
	// create trap entities
	for (int i = 0; i < 5; i++)
	{
		x = rand() % NUM_HORIZONTAL;			//Will generate random X value on the grid 
		y = rand() % NUM_VERTICAL;				//Will generate random Y value on the grid 
		while (entityPtrGrid[x][y] != NULL)   // to check if its overlapping or not
		{
			x = rand() % NUM_HORIZONTAL;     // if it overlapps then generate new x and y untill it finds new unoccupied space
			y = rand() % NUM_VERTICAL;
		}
		entityPtrGrid[x][y] = new Trap(x, y, NUM_HORIZONTAL - 1, NUM_VERTICAL - 1, "resources/pac.png", 6); //// This will create new pointer for the Trap entity

	}
	
	// create destination entity
	x = rand() % NUM_HORIZONTAL;			//Will generate random X value on the grid 
	y = rand() % NUM_VERTICAL;				//Will generate random Y value on the grid 
	while (entityPtrGrid[x][y] != NULL)   // to check if its overlapping or not
	{
		x = rand() % NUM_HORIZONTAL;     // if it overlapps then generate new x and y untill it finds new unoccupied space
		y = rand() % NUM_VERTICAL;
	}
	entityPtrGrid[x][y] = new Entity(x, y, NUM_HORIZONTAL - 1, NUM_VERTICAL - 1, "resources/door.png", DESTINATION);

	// load the background

	sf::Texture texture;
	if (!texture.loadFromFile("resources/background.png"))   // This will load the background
	{
		cout << "Error loading background";
		return EXIT_FAILURE;
	}
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(texture);
	
	// load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/Quicksand-Regular.otf"))  // This will load the test
	{
		cout << "cannot open font";
		sf::sleep(sf::seconds(5));
		return EXIT_FAILURE;
	}

	// initialize the score board
	sf::Text scoreBoard;
	scoreBoard.setFont(font);
	scoreBoard.setCharacterSize(25);
	scoreBoard.setPosition(10.f, (NUM_VERTICAL + 1) * SIZE_SPRITE); // at the bottom of the window
	scoreBoard.setFillColor(sf::Color::Black);
	scoreBoard.setString("Score: 0");
	
	// initialize message board
	sf::Text messageBoard;
	messageBoard.setFont(font);
	messageBoard.setCharacterSize(25);
	messageBoard.setPosition(10.f, NUM_VERTICAL * SIZE_SPRITE); // at the bottom of the window
	messageBoard.setFillColor(sf::Color::Blue);
	messageBoard.setString("Message: none.");

	// load the sound used in the game
	sf::SoundBuffer backgroundSoundBuffer;
	if (!backgroundSoundBuffer.loadFromFile("resources/awesomeness.wav")) {
		std::cout << "cannot open audio";
		sf::sleep(sf::seconds(5));
		return EXIT_FAILURE;
	}
	sf::Sound backgroundSound(backgroundSoundBuffer);
	backgroundSound.play(); // play background music
	// timer for time delays
	sf::Clock clock;
	float timer = 0, delay = 0.2;
	float timeCalc = 0;          // this will calculate the total time 

	Direction dir = NONE; // direction of player move

	// main game loop
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		timeCalc += clock.getElapsedTime().asSeconds();    // This is calculating time
		clock.restart();
		timer += time;

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) // close button
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // left key
			dir = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // right key
			dir = RIGHT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // up key
			dir = UP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // down key
			dir = DOWN;
		}

		if (timer > delay) { // time delay to accomodate user key input 
			timer = 0; 

			// check for collision for prize
			EntityType collisionType = checkCollision(entityPtrGrid, player.getX(), player.getY(), dir, timeCalc);
			
				messageBoard.setString("Message: " + MSG);      // This will set the message board according to the collision type
				
				string scoreStr ("Score: " + std::to_string(totalScore));    // string concatenation to display the score on the screen as a string
				
				scoreBoard.setString("Score: " + std::to_string(totalScore));		//  This will set the score board according to the collision type
		
				// update player position based on direction
			if (collisionType != WALL) { 
				entityPtrGrid[player.getX()][player.getY()] = NULL;
				if (dir == UP) {
					player.moveUp();
				}
				else if (dir == DOWN) {
					player.moveDown();
				}
				else if (dir == LEFT) {
					player.moveLeft();
				}
				else if (dir == RIGHT) {
					player.moveRight();
				}
				entityPtrGrid[player.getX()][player.getY()] = &player;
				dir = NONE;
			}
		}

		// draw game interface
		window.clear();
		window.draw(backgroundSprite); // display background
		window.draw(scoreBoard); // display score board
		window.draw(messageBoard); // display message board

		// draw all adventure game sprites
		for (int i = 0; i < NUM_HORIZONTAL; ++i) 
			for (int j = 0; j < NUM_VERTICAL; ++j)
		{
			Entity* entity = entityPtrGrid[i][j];
			if (entity != NULL) {
				sf::Sprite sprite = entity->getSprite();
				sprite.setPosition(i * SIZE_SPRITE, j * SIZE_SPRITE);
				window.draw(sprite);
			}
		}
		window.display();
	}

	return 0;
}