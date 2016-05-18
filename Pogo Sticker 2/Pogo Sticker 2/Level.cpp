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
	fileReader = new ReadFile("../Pogo Sticker 2/Text2.txt");
	fileReader->readData();

	levelHeight = fileReader->dataContext["height"]*32;
	levelWidth = fileReader->dataContext["width"]*32;
	tileHeight = fileReader->dataContext["tileheight"];
	tileWidth = fileReader->dataContext["tilewidth"];

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

void Level::levelCompleted()
{
	G_Button* button = new G_Button(100, 100, 100, 100, "../images/button_up.png", switchToMenu);
	currentGameEngine().add(button);
	int time = timer->getTime();
	Label* label = Label::getInstance(200, 200, 200, 25, "grats m8 ur time is: " + std::to_string(time));
	currentGameEngine().add(label);
	currentGameEngine().setEndstate(true);
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
	SDL_Surface* surface = IMG_Load("../images/white.png");
	setBackground(surface);

	Character* character = new Character(250, 250, 30, 60, "../images/character.png");
	sprites.push_back(character);

	SDL_Surface* surface2 = IMG_Load("../images/tiletemplate.png");
	if (surface2 == nullptr)
		throwException("surface2 is null ", SDL_GetError);

	WorldObject* worldObject = new WorldObject(2, 2);
	worldObjects.push_back(worldObject);
		
	int x = 0;
	int y = 0;
	std::list<int> data = fileReader->getData();
	for (std::list<int>::iterator it = data.begin(); it != data.end(); it++)
	{
		if (x >= levelWidth)
		{
			x = 0;
			y += tileHeight;
		}
		if (it._Ptr->_Myval == 0)
		{
			x += tileWidth;
			continue;
		}
		else
		{
			int tileMapWidth = surface2->w / 32;
			int tileMapHeight = surface2->h / 32;
			int tilePosition = it._Ptr->_Myval;
			int a;
			if (tilePosition < tileMapWidth)
				a = tilePosition - 1;
			else
			{
				a = int(tilePosition) % tileMapWidth;
			}
			int b = int(tilePosition) / tileMapHeight;
			//xy = Starting point on the tilemap
			//wh = How big the tile is
			SDL_Rect srcRect = { a*32, b*32, tileHeight, tileWidth };
			Tile* tile = new Tile(x, y, tileWidth, tileHeight, &srcRect, surface2, it._Ptr->_Myval);
			sprites.push_back(tile);
			tiles.push_back(tile);
		}
		x += tileWidth;
	}

	currentGameEngine().getCamera().setCharacter(character);
	currentGameEngine().getCamera().setLevel(this);

	timer = new Timer(10, 01, 100, 50, "hej");
	sprites.push_back(timer);
}
