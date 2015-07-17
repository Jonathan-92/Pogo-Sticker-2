#include "Character.h"
#include "GameEngine.h"
#include <vector>

using namespace gameEngine;

Character::Character(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false, "Character")
{
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	chargeMeter = 100;
	chargeMeterTick = 0;
}

Character::~Character(void)
{
}

void Character::mouseMotion(int x, int y)
{
	if (mVelX >= CHARACTER_VEL)
		mVelX -= 2;
	if (rect.x < x)
		mVelX += 1;
	if (rect.x > x)
		mVelX -= 1;
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 4.5;	
}

void Character::draw()
{
	rect.x = rect.x - ge().getCamera().rect.x;
	rect.y = rect.y - ge().getCamera().rect.y;
	SDL_RenderCopy(gameEngine::ge().getRenderer(), texture, nullptr, &rect);
}

void Character::tick()
{	
	if (rect.y + rect.h > 640 || rect.y + rect.h < 0)
	{
		mVelY -= 2;
	}

	std::list<Sprite*> sprites = ge().getSprites();
	for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		if (rect.overlaps((*it)->rect) && (*it)->getType() == "Tile")
		{
			mVelY -= 2;
		}
	}

	mVelY += 0.05f;
	
	rect.y += mVelY;	
	
	//rect.x += mVelX;
	//rect.y = (int)mPosY;
}