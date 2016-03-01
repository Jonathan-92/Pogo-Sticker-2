#include "Character.h"
#include "GameEngine.h"
#include "OverlapSourceEnum.h"
#include <vector>

using namespace gameEngine;

Character::Character(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false, "Character")
{
	//Initialize the velocity
	movementVelocityX = 0;
	movementVelocityY = 0;
	spriteAxisAngle = 0;

	/*head = Sprite::getInstance(32, 32, 15, 15, "../images/head.png", false, "Head");
	body = new Sprite(32, 32, 15, 15, "../images/body.png", false, "Head");
	foot = new Sprite(32, 32, 15, 15, "../images/foot.png", false, "Head");*/

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
	spriteAxisAngle = atan2(deltaY, deltaX) * 180 / 3.141;
	rect.angle = spriteAxisAngle;
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 0.5;	
}

void Character::draw()
{
	SDL_Rect drawingRect = { rect.x - ge().getCamera().rect.x, rect.y - ge().getCamera().rect.y, rect.w, rect.h };
	SDL_RenderCopyEx(gameEngine::ge().getRenderer(), texture, nullptr, &drawingRect, spriteAxisAngle, NULL, SDL_FLIP_NONE);
}

void Character::tick()
{	
	handleCollision();

	//TODO: Apply gravity here
	//mVelX = spriteAxisAngle/100 + chargeMeter;
	movementVelocityY += 0.05f;

	straightenUp();
	applyMotion();
}

void Character::handleCollision()
{
	std::list<Tile*> tiles = ge().getTiles();
	for (std::list<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		if (ge().getCollider()->overlaps(&rect, &(*it)->rect) && (*it)->getType() == "Tile")
		{
			OverlapSourceEnum overlapSourceEnum = ge().getCollider()->overlapSource(&rect, &(*it)->rect);
			if ((*it)->getTileType() == 28)
			{
				ge().getLevel()->levelCompleted();
			}

			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsTop)
			{
				movementVelocityY -= 5;
			}			
			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsBottom)
			{
				movementVelocityY += 5;
			}			
			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsLeft)
			{
				movementVelocityX += 1;
			}			
			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsRight)
			{
				movementVelocityX -= 1;
			}

			//movementVelocityX = spriteAxisAngle / 100 + chargeMeter;
		}
	}
}

void Character::applyMotion()
{
	rect.y += movementVelocityY;
	rect.x += movementVelocityX;
}

void Character::straightenUp()
{
	if (spriteAxisAngle > 0)
		spriteAxisAngle -= 0.1;
	else
	{
		spriteAxisAngle += 0.1;
	}
}