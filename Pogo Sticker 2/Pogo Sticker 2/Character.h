#ifndef CHARACTER_H
#define CHARACTER_H
#include "Sprite.h"
#include "Gravity.h"
#include <list>
#include "Hitbox.h"

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

	//�rvd fr�n Sprite antar jag
	void mouseMotion(int x, int y) override;
	void mouseDown(int x, int y) override;

	void draw() override;

	void tick() override;

private:

	void straightenUp();
	void handleCollision();
	void syncHitboxes();
	int setCursorDistanceFromCharacter(int x, int y);

	//Handle how high it should bounce
	float chargeMeter;
	int cursorDistanceFromCharacter;
	int chargeMeterTick;
	float spriteAxisAngle;

	std::list<gameEngine::Hitbox*> hitboxes;
	//Gravity object
	gameEngine::Gravity gravity = gameEngine::Gravity(0.1, 0.1, 0.01);
};
#endif