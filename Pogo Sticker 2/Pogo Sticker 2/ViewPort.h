#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Sprite.h"
#include "Tile.h"
#include "WorldObject.h"
#include <list>

class ViewPort
{
public:
	ViewPort();
	~ViewPort();
	virtual void init() = 0;
	virtual void load();
	virtual void setBackground(SDL_Surface* surface);
protected:
	std::list<gameEngine::Sprite*> sprites;
	std::list<gameEngine::WorldObject*> worldObjects;
	std::list<Tile*> tiles;
	SDL_Texture* background;
private:

};

#endif