#include "Tile.h"

Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = 50;
	mBox.h = 50;

	//Get the tile type
	mType = tileType;
}

int Tile::getType() 
{ 
	return mType; 
} 

SDL_Rect Tile::getBox() 
{ 
	return mBox; 
}