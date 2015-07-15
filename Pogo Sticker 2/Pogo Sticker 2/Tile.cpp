#include "Tile.h"

Tile::Tile(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false, "Tile")
{

}

Tile::~Tile(void)
{
}

SDL_Rect Tile::getBox() 
{ 
	return mBox; 
}