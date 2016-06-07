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
	{
		float w = rect.w;
		float h = rect.h;

		SDL_GL_BindTexture(texture, &w, &h);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor3ub(255, 255, 255);

		glBegin(GL_QUADS);

		// Top Left
		glTexCoord2f(0, 1);
		glVertex2f(rect.x, rect.y);

		// Top Right
		glTexCoord2f(1, 1);
		glVertex2f(rect.x + rect.w, rect.y);

		// Bottom Right
		glTexCoord2f(1, 0);
		glVertex2f(rect.x + rect.w, rect.y + rect.h);

		// Bottom Left
		glTexCoord2f(0, 0);
		glVertex2f(rect.x, rect.y + rect.h);

		glEnd();
	}
	else
		return;
}

void Tile::tick()
{
	//if (rect.overlaps(currentGameEngine().))
}