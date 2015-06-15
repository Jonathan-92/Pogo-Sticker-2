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
	//Move the dot left or right
	mPosX += mVelX;

	//Count up the charge ticker
	++chargeMeterTick;

	if (chargeMeterTick == 5)
	{
		if (mPosY <= 400)
			mPosY = gravity.applyGravity(mVelY, mPosY);
		else
		{
			mVelY = 0;
			mVelY += gravity.jump(chargeMeter);
			mPosY -= mVelY;
			gravity.resetTime();
		}
		chargeMeterTick = 0;
		chargeMeter -= 0.5;
		if (chargeMeter < 0)
			chargeMeter = 0.1;
	}

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + CHARACTER_WIDTH > 800))
	{
		//Move back
		mPosX -= mVelX;
	}

	//mPosY += mVelY;
 
	//If the dot went too far up or down 
	if ((mPosY < 0) || (mPosY + rect.h > 640))
	{
		//Move back
		mPosY -= mVelY;
	}

	rect.x = (int)mPosX;
	rect.y = (int)mPosY;
}