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
	SDL_Rect drawingRect = { rect.x - ge().getCamera().rect.x, rect.y - ge().getCamera().rect.y, rect.w, rect.h };

	//SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);
	if (rect.overlaps(ge().getCamera().rect))
		SDL_RenderCopy(ge().getRenderer(), texture, NULL, &drawingRect);
	else
		return;
}

void Tile::tick()
{
	//if (rect.overlaps(ge().))
}