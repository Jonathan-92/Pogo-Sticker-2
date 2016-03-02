#include "Character.h"
#include "GameEngine.h"
#include "OverlapSourceEnum.h"
#include <vector>

using namespace gameEngine;

Character::Character(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false, "Character")
{
	//Initialize the velocity
	movementVelocityX = -0.1;
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
	bool handeldCollision = false;
	for (std::list<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		if (ge().getCollider()->overlaps(&rect, &(*it)->rect) && (*it)->getType() == "Tile")
		{
			SDL_Rect movingObject = rect;
			SDL_Rect stationaryObject = (*it)->rect;
			// what side of the stationaryObject does the movingObject collide on?
			bool intersectsTop = false;
			bool intersectsRight = false;

			if (movingObject.x > stationaryObject.x)
				intersectsRight = true;
			// y up is neg
			if (movingObject.y < stationaryObject.y)
				intersectsTop = true;

			// the height & width of the intersection rectangle
			short int height, width;

			if (intersectsTop)
				height = abs(stationaryObject.y - (movingObject.y + movingObject.h));
			else
				height = abs(stationaryObject.y + stationaryObject.h - movingObject.y);
			if (intersectsRight)
				width = abs(stationaryObject.x + stationaryObject.w - movingObject.x);
			else
				width = abs(stationaryObject.x - (movingObject.x + movingObject.w));

			bool moveInXDirection = height > width ? true : false;

			// adjust moving object's position accordingly
			if (moveInXDirection)
			{
				if (intersectsRight)
					movementVelocityX += width;
				else
					movementVelocityX -= width;
			}
			else
			{
				if (intersectsTop)
					movementVelocityY -= height;
				else
					movementVelocityY += height;
			}
			/*OverlapSourceEnum overlapSourceEnum = ge().getCollider()->overlapSource(&rect, &(*it)->rect);
			if ((*it)->getTileType() == 28)
			{
				ge().getLevel()->levelCompleted();
			}

			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsTop)
			{
				if (!handeldCollision && movementVelocityY < 0)
				{
					handeldCollision = !handeldCollision;
					movementVelocityY *= -1;
				}
			}			
			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsBottom)
			{
				if (!handeldCollision)
				{
					handeldCollision = !handeldCollision;
					movementVelocityY -= movementVelocityY * 2;
				}
			}			
			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsLeft)
			{
				if (!handeldCollision  && movementVelocityY < 0)
				{
					handeldCollision = !handeldCollision;
					movementVelocityX *= -1;
				}
			}			
			if (overlapSourceEnum.getOverlapSouceEnum() == OverlapSourceEnum::OverlapSourceEnums::overlapsRight)
			{
				if (!handeldCollision)
				{
					handeldCollision = !handeldCollision;
					movementVelocityX -= movementVelocityX * 2;
				}
			}*/

			//movementVelocityX += spriteAxisAngle / 100 + chargeMeter;
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