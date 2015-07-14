#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL.h>
#include "Sprite.h"
#include "Gravity.h"

//The pogo guy.
class Character : public gameEngine::Sprite
{
public:
	//The dimensions of the character
	static const int CHARACTER_WIDTH = 20;
	static const int CHARACTER_HEIGHT = 20;

	//Maximum axis velocity of the character
	static const int CHARACTER_VEL = 10;

	//Maximum charge
	static const int CHARACTER_CHARGE = 20;

	//Initializes the variables
	Character(int x, int y, int w, int h, std::string imgPath);
	~Character(void);

	//Ärvd från Sprite antar jag
	virtual void mouseMotion(int x, int y);
	virtual void mouseDown(int x, int y);
	virtual void collisonCheck(gameEngine::Sprite *sprites[]);

	//Få ut positionen
	virtual int getPosX();
	virtual int getPosY();

	//Takes key presses and adjusts the dot's velocity (Sprite sköter det tydligen)
	//void handleEvent(SDL_Event& e);
	//virtual void draw(Camera* camera);

	//Moves the dot
	virtual void tick();

private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	float mVelX, mVelY;

	//CHAAAARRGEEEE!
	float chargeMeter;
	int chargeMeterTick;

	//Gravity object
	gameEngine::Gravity gravity = gameEngine::Gravity(0.1, 0.1, 0.01);
};
#endif