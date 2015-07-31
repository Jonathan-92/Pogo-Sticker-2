#include "Character.h"
#include "GameEngine.h"
#include <vector>

using namespace gameEngine;

Character::Character(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false, "Character")
{
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	angle = 0;

	chargeMeter = 0.5;
	chargeMeterTick = 0;
}

Character::~Character(void)
{
}

void Character::mouseMotion(int x, int y)
{
	SDL_Point point = { rect.x / 2, rect.y / 2 };
	int deltaY = y - point.x;
	int deltaX = x - point.y;
	angle = atan2(deltaY, deltaX) * 180 / 3.141;
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 0.5;	
}

void Character::draw()
{
	SDL_Rect drawingRect = { rect.x - ge().getCamera().rect.x, rect.y - ge().getCamera().rect.y, rect.w, rect.h };
	SDL_Point point = { rect.x / 2, rect.y / 2 };
	SDL_RenderCopyEx(gameEngine::ge().getRenderer(), texture, nullptr, &drawingRect, angle, &point, SDL_FLIP_NONE);
}

void Character::tick()
{	
	std::list<Tile*> tiles = ge().getTiles();
	for (std::list<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		if (rect.overlaps((*it)->rect) && (*it)->getType() == "Tile")
		{
			if ((*it)->getTileType() == 28)
			{
				ge().getLevel()->levelCompleted();
			}
			mVelX = angle / 100 + chargeMeter;
			if (mVelY > 0)
				mVelY -= 2;
		}
	}

	//TODO: Apply gravity here
	//mVelX = angle/100 + chargeMeter;
	mVelY += 0.05f;

	if (angle > 0)
		angle -= 0.1;
	else
	{
		angle += 0.1;
	}
	
	applyMotion();
}

void Character::applyMotion()
{
	rect.y += mVelY;
	rect.x += mVelX;
}