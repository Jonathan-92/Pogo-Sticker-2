#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Sprite.h"
#include <list>

class ViewPort
{
public:
	ViewPort();
	~ViewPort();
	virtual void init() = 0;
	void load();
	void setBackground(SDL_Surface* surface);
protected:
	std::list<gameEngine::Sprite*> sprites;
private:
	SDL_Texture* background;
};

#endif