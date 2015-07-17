#include "Tile.h"
#include "GameEngine.h"

using namespace gameEngine;

Tile::Tile(int x, int y, int w, int h, std::string imgPath, int type) : Sprite(x, y, w, h, imgPath, false, "Tile")
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
	rect.x = rect.x - ge().getCamera().rect.x;
	rect.y = rect.y - ge().getCamera().rect.y;

	if (rect.overlaps(ge().getCamera().rect))
		SDL_RenderCopy(ge().getRenderer(), texture, NULL, &rect);
	else
		return;
}