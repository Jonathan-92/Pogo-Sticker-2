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

	head = new BodyPart(x, y-29, 35, 29, "../images/head.png", "Head");
	body = new BodyPart(x, y, w, h, "../images/body.png", "Body");
	foot = new BodyPart(x, y+y, 35, 12, "../images/foot.png", "Foot");
	debugPoint = new BodyPart(x, y + y, 50, 50, "../images/black.png", "DEBUG");

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
	rect.angle = angle;
}

void Character::mouseDown(int x, int y)
{
	chargeMeter += 0.5;	
}

void Character::draw()
{
	SDL_Point center = { rect.centeredX(), rect.centeredY() };
	debugPoint->rect.x = center.x;
	debugPoint->rect.y = center.y;
	
	debugPoint->draw(&center);
	
	head->draw(NULL);
	body->draw(NULL);
	foot->draw(NULL);
	//Head
	//SDL_Rect drawingRect = { rect.x - ge().getCamera().rect.x, rect.y - ge().getCamera().rect.y, rect.w, rect.h };
	//SDL_RenderCopyEx(gameEngine::ge().getRenderer(), texture, nullptr, &drawingRect, angle, NULL, SDL_FLIP_NONE);
	//Body
	
	//Foot
}

void Character::tick()
{	
	std::list<Tile*> tiles = ge().getTiles();
	for (std::list<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		if (rect.RotRectsCollision(&rect, &it._Ptr->_Myval->rect) == 1 && rect.overlaps((*it)->rect) && (*it)->getType() == "Tile")
		{			
			if ((*it)->getTileType() == 28)
			{
				ge().getLevel()->levelCompleted();
			}
			mVelX = angle / 100 + chargeMeter;
			if (mVelY > 0)
				mVelY -= 1;
		}
	}

	//TODO: Apply gravity here
	//mVelX = angle/100 + chargeMeter;
	mVelY += 0.05f;

	if (angle > 0)
		angle -= 0.3;
	else
	{
		angle += 0.3;
	}
	
	applyMotion();
	syncBodyParts();
}

//TODO: FIXA!
void Character::syncBodyParts()
{
	body->rect.x = rect.x;
	body->rect.y = rect.y;
	body->angle = angle;
	
	head->rect.x = body->rect.x;
	head->rect.y = body->rect.y - 29;
	head->angle = angle;

	foot->rect.x = SDL_cos(body->angle);
	foot->rect.y = SDL_sin(body->angle) + body->rect.y;
	foot->angle = angle;
}

void Character::applyMotion()
{
	rect.y += mVelY;
	rect.x += mVelX;
}