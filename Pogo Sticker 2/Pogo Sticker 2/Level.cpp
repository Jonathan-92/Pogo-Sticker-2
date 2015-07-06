#include "Level.h"
#include <SDL_image.h>
#include "G_Button.h"
#include "MainMenu.h"
#include "Character.h"
#include "Timer.h"

using namespace gameEngine;

Level::Level()
{
	init();
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

	Character* character = new Character(200, 200, 100, 100, "../images/button_up.png");
	sprites.push_back(character);

	Timer* timer = new Timer(10, 01, 100, 50, "hej");
	sprites.push_back(timer);
}