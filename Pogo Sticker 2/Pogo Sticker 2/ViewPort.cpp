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
	ge().load(background, sprites);
}

void ViewPort::setBackground(SDL_Surface* surface)
{
	background = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
	SDL_FreeSurface(surface);
}