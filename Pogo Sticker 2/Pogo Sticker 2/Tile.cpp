#include "Tile.h"
#include "GameEngine.h"

using namespace gameEngine;

Tile::Tile(int x, int y, int w, int h, SDL_Rect* sourceRect, SDL_Surface* surface, int type) : 
		Sprite(x, y, w, h, sourceRect, surface, false, "Tile")
{
	tileType = type;
}

Tile::~Tile(void)
{
}

int Tile::getTileType()
{
	return tileType;
}

void Tile::draw()
{
	SDL_Rect drawingRect = { rect.x - currentGameEngine().getCamera().rect.x, rect.y - currentGameEngine().getCamera().rect.y, rect.w, rect.h };
	if (rect.overlaps(currentGameEngine().getCamera().rect))
		SDL_RenderCopy(currentGameEngine().getRenderer(), texture, NULL, &drawingRect);
	else
		return;
}

void Tile::tick()
{
	//if (rect.overlaps(currentGameEngine().))
}