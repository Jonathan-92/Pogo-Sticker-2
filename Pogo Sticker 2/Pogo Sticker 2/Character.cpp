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
		mVelX -= 0.2f;
	if (rect.x < x)
		mVelX += 0.1f;
	if (rect.x > x)
		mVelX -= 0.1f;
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 4.5;	
}

void Character::draw()
{
	SDL_Rect drawingRect = { rect.x - ge().getCamera().rect.x, rect.y - ge().getCamera().rect.y, rect.w, rect.h };
	SDL_RenderCopy(gameEngine::ge().getRenderer(), texture, nullptr, &drawingRect);	
}

void Character::tick()
{	
	if (rect.y + rect.h > 1000 || rect.y + rect.h < 0)
	{
		mVelY -= 2;
	}

	std::list<Sprite*> sprites = ge().getSprites();
	for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		if (rect.overlaps((*it)->rect) && (*it)->getType() == "Tile")
		{
			if (mVelY > 0)
				mVelY -= 2;
			else
				mVelY += 2;
		}
	}

	//TODO: Apply gravity here
	mVelY += 0.05f;
	
	rect.y += mVelY;		
	rect.x += mVelX;

}