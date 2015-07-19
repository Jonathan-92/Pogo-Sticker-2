#include "SDL.h"
#include "SDL_image.h"
#include "MainMenu.h"
#include "Label.h"
#include <iostream>
#include "Level.h"
#include "G_Button.h"
#include "GameEngine.h"

using namespace gameEngine;

MainMenu* MainMenu::getInstance()
{
	static MainMenu mainMenu;
	return &mainMenu;
}

MainMenu::MainMenu()
{

}
MainMenu::~MainMenu()
{

}

void switchToLevel()
{
	Level* level1 = new Level();
	level1->load();
}

void Level::load()
{
	ge().load(background, sprites, this);
}

void Level::setBackground(SDL_Surface* surface)
{
	background = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
	SDL_FreeSurface(surface);
}

void MainMenu::init()
{
	SDL_Surface* surface = IMG_Load("../images/white.png");
	setBackground(surface);

	Label* label = Label::getInstance(50, 50, 150, 50, "Main Menu");
	sprites.push_back(label);

	G_Button* button = new G_Button(100, 100, 200, 100, "../images/start_level_1.png", switchToLevel);
	sprites.push_back(button);
}
