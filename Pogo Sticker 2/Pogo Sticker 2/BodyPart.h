#ifndef BODYPART_H
#define BODYPART_H
#include "Sprite.h"
#include <SDL.h>

//The camera that will move around on the screen
class BodyPart : public gameEngine::Sprite
{
public:
	//Maximum axis velocity of the dot
	static const int CAMERA_VEL = 0;

	//Initializes the variables
	BodyPart(int x, int y, int w, int h, std::string imgPath, std::string type);
	~BodyPart(void);

	void draw(SDL_Point* center);
	int angle;

private:

};
#endif