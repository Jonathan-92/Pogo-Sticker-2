#include "Level.h"
#include <SDL_image.h>
#include "G_Button.h"
#include "MainMenu.h"
#include "Character.h"
#include "Timer.h"
#include "Tile.h"
#include "GameEngine.h"

using namespace gameEngine;

Level::Level()
{
	init();
	levelHeight = 2000;
	levelWidth = 2000;
	fileReader = new ReadFile("../Pogo Sticker 2/Text.txt");
	fileReader->readData();
}


Level::~Level()
{
}

void switchToMenu()
{
	MainMenu* mainMenu = MainMenu::getInstance();
	mainMenu->load();
}

int Level::getHeight()
{
	return levelHeight;
}

int Level::getWidth()
{
	return levelWidth;
}

void Level::init()
{
	//SDL_Surface* surface = IMG_Load("../images/black.png");
	//setBackground(surface);
	SDL_Surface* surface = IMG_Load("../images/white.png");
	setBackground(surface);

	G_Button* button = new G_Button(100, 100, 100, 100, "../images/button_up.png", switchToMenu);
	sprites.push_back(button);

	Character* character = new Character(500, 200, 100, 100, "../images/black.png");
	sprites.push_back(character);

	/*int i = 0;
	std::list<int*> data = fileReader->getData();
	for (std::list<int*>::iterator it = data.begin(); it != data.end(); it++)
	{
		if (&it == 0)
			continue;
		Tile* tile = new Tile(100 + 50 * i, 500, 100, 100, "../images/black.png");
		sprites.push_back(tile);
		++i;
	}*/

	//Floor
	for (int i = 0; i < 15; ++i)
	{
		Tile* tile = new Tile(100+50*i, 500, 100, 100, "../images/black.png", 1);
		sprites.push_back(tile);
	}
	//Roof
	for (int i = 0; i < 15; ++i)
	{
		Tile* tile = new Tile(100 + 50 * i, 0, 100, 100, "../images/black.png", 1);
		sprites.push_back(tile);
	}	
	//Left wall
	for (int i = 0; i < 10; ++i)
	{
		Tile* tile = new Tile(100, 0 + 50 * i, 100, 100, "../images/black.png", 1);
		sprites.push_back(tile);
	}



	Tile* tile = new Tile(900, 500, 100, 100, "../images/Goal.png", 2);
	sprites.push_back(tile);

	ge().getCamera().setCharacter(character);
	ge().getCamera().setLevel(this);

	Timer* timer = new Timer(10, 01, 100, 50, "hej");
	sprites.push_back(timer);
}