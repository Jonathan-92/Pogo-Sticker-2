#ifndef CAMERA_H
#define CAMERA_H
#include <SDL.h>
#include "Sprite.h"
#include "Level.h"
#include "Character.h"

//The camera that will move around on the screen
class Camera : public gameEngine::Sprite
{
public:
	//Maximum axis velocity of the dot
	static const int CAMERA_VEL = 0;

	//Initializes the variables
	Camera();
	~Camera(void);

	void tick();
	void setCharacter(Character* character);
	void setLevel(gameEngine::Level* level);
private:
	Character* character;
	gameEngine::Level* level;
	//The velocity of the camera
	float mVelX, mVelY;
};
#endif