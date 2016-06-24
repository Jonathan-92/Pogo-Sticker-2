#include "Character.h"
#include "GameEngine.h"
#include "Hitbox.h"
#include <SDL_image.h>

using namespace gameEngine;

Character::Character(int x, int y, int w, int h, std::string imgPath) : Sprite(x, y, w, h, imgPath, false, "Character")
{
	//Initialize the velocity
	movementVelocityX = 0;
	movementVelocityY = 0;
	spriteAxisAngle = 0;
	cursorDistanceFromCharacter = 0;

	hitboxes.push_back(new Hitbox(x, y, w, h, HitboxEnum::HitboxEnums::characterHead));
	hitboxes.push_back(new Hitbox(x, y+10, w, h, HitboxEnum::HitboxEnums::characterBody));
	hitboxes.push_back(new Hitbox(x, y+50, w, h, HitboxEnum::HitboxEnums::characterFoot));

	chargeMeter = 0.2;
	chargeMeterTick = 0;
}

Character::~Character(void)
{

}

void Character::mouseMotion(int x, int y)
{
	SDL_Point point = { rect.centeredX(), rect.centeredY()};
	int deltaY = y - point.x;
	int deltaX = x - point.y;
	spriteAxisAngle = atan2(deltaY, deltaX) * 180 / M_PI;
	//rect.angle = spriteAxisAngle;
	cursorDistanceFromCharacter = setCursorDistanceFromCharacter(x, y);
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 0.2;	
}

void Character::draw()
{
	SDL_Rect drawingRect = { rect.getX() - currentGameEngine().getCamera().rect.getX(), rect.getY() - currentGameEngine().getCamera().rect.getY(), rect.getWidth(), rect.getHeight() };
	//SDL_RenderCopyEx(currentGameEngine().getRenderer(), texture, nullptr, &drawingRect, spriteAxisAngle, NULL, SDL_FLIP_NONE);

	float w = rect.getWidth();
	float h = rect.getHeight();

	SDL_GL_BindTexture(texture, &w, &h);

	rect.draw();

	//Draw hitboxes for debugging
	SDL_Surface* surface = IMG_Load("../images/hitbox.png");
	if (surface == nullptr)
		throw std::runtime_error("surface is null");

	SDL_Texture* textureTemp = SDL_CreateTextureFromSurface(currentGameEngine().getRenderer(), surface);
	for (std::list<Hitbox*>::iterator hitboxIterator = hitboxes.begin(); hitboxIterator != hitboxes.end(); ++hitboxIterator)
	{
		//SDL_RenderCopyEx(currentGameEngine().getRenderer(), textureTemp, nullptr, hitboxIterator._Ptr->_Myval, spriteAxisAngle, NULL, SDL_FLIP_NONE);
	}
}

void Character::tick()
{	
	handleCollision();

	//TODO: Apply gravity here
	movementVelocityY += 0.05f;

	//straightenUp();
	applyMotion();
	syncHitboxes();
}

void Character::syncHitboxes()
{
	for (std::list<Hitbox*>::iterator hitboxIterator = hitboxes.begin(); hitboxIterator != hitboxes.end(); hitboxIterator++)
	{	
		Hitbox* hitbox = hitboxIterator._Ptr->_Myval;
		hitbox->applyMotion(movementVelocityX, movementVelocityY);
		//hitbox->applyRotation(rect.centeredX(), rect.centeredY(), rect.angle);
	}
}

void Character::handleCollision()
{
	std:list<WorldObject*> worldObjects = currentGameEngine().getWorldObjects();
	for (auto worldObjectIterator = worldObjects.begin(); worldObjectIterator != worldObjects.end(); ++worldObjectIterator)
	{
		for (auto hitboxIterator = hitboxes.begin(); hitboxIterator != hitboxes.end(); ++hitboxIterator)
		{
			if (currentGameEngine().getCollider()->intersect(hitboxIterator._Ptr->_Myval, worldObjectIterator._Ptr->_Myval))
			{
				Rect* movingObject = hitboxIterator._Ptr->_Myval;
				Rect* stationaryObject = (*worldObjectIterator)->boundaryRectangle;
				
				// what side of the stationaryObject does the movingObject collide on?
				bool intersectsTop = false;
				bool intersectsRight = false;

				if (movingObject->getX() > stationaryObject->getX())
					intersectsRight = true;
				// y up is neg
				if (movingObject->getY() < stationaryObject->getY())
					intersectsTop = true;

				// the height & width of the intersection rectangle
				short int height, width;

				if (intersectsTop)
					height = abs(stationaryObject->getY() - (movingObject->getY() + movingObject->getHeight()));
				else
					height = abs(stationaryObject->getY() + stationaryObject->getHeight() - movingObject->getY());
				if (intersectsRight)
					width = abs(stationaryObject->getX() + stationaryObject->getWidth() - movingObject->getX());
				else
					width = abs(stationaryObject->getX() - (movingObject->getX() + movingObject->getWidth()));

				bool moveInXDirection = height > width ? true : false;

				// adjust moving object's position accordingly
				if (moveInXDirection)
				{
					if (intersectsRight)
					{
						movementVelocityX += width;
					}
					else
					{
						movementVelocityX -= width;
					}
				}
				else
				{
					if (intersectsTop)
					{
						movementVelocityY -= height;
					}
					else
					{
						movementVelocityY += height;
					}
				}

				//if ((*worldObjectIterator)->getTileType() == 28)
				//{
				//	currentGameEngine().getLevel()->levelCompleted();
				//}

				//Sinus and cosinus
				movementVelocityX += sin(spriteAxisAngle * M_PI / 180) + cursorDistanceFromCharacter;
				movementVelocityY += cos(spriteAxisAngle * M_PI / 180) + chargeMeter;
			}
		}
	}
}

int Character::setCursorDistanceFromCharacter(int x, int y)
{
	SDL_Point point = { rect.centeredX(), rect.centeredY() };
	int cursorDistanceFromCharacter = (x - point.x) / 200;
	return cursorDistanceFromCharacter;
}

void Character::straightenUp()
{
	if (spriteAxisAngle > 0)
		spriteAxisAngle -= 0.1f;
	else
	{
		spriteAxisAngle += 0.1f;
	}
}