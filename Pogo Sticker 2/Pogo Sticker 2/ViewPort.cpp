#include "ViewPort.h"
#include "SDL_image.h"
#include "GameEngine.h"

using namespace gameEngine;
using namespace std;

ViewPort::ViewPort()
{
}

ViewPort::~ViewPort()
{
}

void ViewPort::load()
{
	currentGameEngine().load(background, sprites);
}

void ViewPort::setBackground(SDL_Surface* surface)
{
	background = SDL_CreateTextureFromSurface(currentGameEngine().getRenderer(), surface);
	SDL_FreeSurface(surface);
}