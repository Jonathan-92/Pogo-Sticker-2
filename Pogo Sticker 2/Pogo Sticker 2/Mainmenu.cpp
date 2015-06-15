#include "SDL.h"
#include "SDL_image.h"
#include "MainMenu.h"
#include "Label.h"
#include <iostream>
#include "Level.h"
#include "G_Button.h"

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

void MainMenu::init()
{
	SDL_Surface* surface = IMG_Load("../images/white.png");
	setBackground(surface);

	Label* label = Label::getInstance(50, 50, 50, 50, "hejsan");
	sprites.push_back(label);

	G_Button* button = new G_Button(100, 100, 100, 100, "../images/button_up.png", switchToLevel);
	sprites.push_back(button);
}
