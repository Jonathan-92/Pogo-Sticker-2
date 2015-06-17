#include "Character.h"
#include "GameEngine.h"
#include <vector>

Character::Character(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false)
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

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
	if (mPosX < x)
		mVelX += 1;
	if (mPosX > x)
		mVelX -= 1;
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 4.5;	
}


void Character::tick()
{	
	if (rect.y + rect.h > 640)
	{
		mVelY -= 2;
	}

	mVelY += 0.05f;
	
	rect.y += mVelY;
	

	//rect.x += mVelX;
	//rect.y = (int)mPosY;
}