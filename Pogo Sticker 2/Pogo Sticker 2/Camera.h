#include <SDL.h>
#include "Sprite.h"
#include "Level.h"

//The camera that will move around on the screen
class Camera : public gameEngine::Sprite
{
public:
	//Maximum axis velocity of the dot
	static const int CAMERA_VEL = 0;

	//Initializes the variables
	Camera();
	~Camera(void);

	void tick(gameEngine::Sprite character, gameEngine::Level level);

private:
	//The X and Y offsets of the camera
	int mPosX, mPosY;

	//The velocity of the camera
	float mVelX, mVelY;
};