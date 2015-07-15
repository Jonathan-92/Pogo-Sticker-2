#ifndef TILE_H
#define TILE_H
#include "SDL.h"
#include "Sprite.h"
//The tile
class Tile : public gameEngine::Sprite
{
public:
	//Initializes position and type
	Tile(int x, int y, int w, int h, std::string imgPath);
	~Tile();

	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the collision box
	SDL_Rect getBox();

private:
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};
#endif