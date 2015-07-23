#ifndef TILE_H
#define TILE_H
#include "SDL.h"
#include "Sprite.h"

/*Tile types
0 - Empty
1 - Normal
2 - Goal
3 - Ice
4 - ...
*/

class Tile : public gameEngine::Sprite
{
public:
	//Initializes position and type
	Tile(int x, int y, int w, int h, SDL_Rect* sourceRect, std::string imgPath, int tileType);
	~Tile();

	//Get the collision box
	void draw();
	int getTileType();
	void tick();

private:
	//The tile type
	int tileType;
};
#endif