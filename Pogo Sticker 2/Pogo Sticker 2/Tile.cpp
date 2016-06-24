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
	SDL_Rect drawingRect = { rect.getX() - currentGameEngine().getCamera().rect.getX(), rect.getY() - currentGameEngine().getCamera().rect.getY(), rect.getWidth(), rect.getHeight() };
	if (rect.overlaps(currentGameEngine().getCamera().rect))
	{
		float w = rect.getWidth();
		float h = rect.getHeight();

		SDL_GL_BindTexture(texture, &w, &h);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor3ub(255, 255, 255);

		rect.draw();
	}
	else
		return;
}

void Tile::tick()
{
	//if (rect.overlaps(currentGameEngine().))
}