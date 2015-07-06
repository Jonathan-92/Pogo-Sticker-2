#include "Camera.h"
#include "GameEngine.h"
#include "SDL.h"

Camera::Camera()
{
	camera = { 0, 0, 800, 600 };
}

Camera::~Camera(void)
{
}

void Camera::tick(gameEngine::Sprite character, gameEngine::Level level)
{
	//800 600 skärmen ändra
	mPosX = (character.getPosX() + character.rect.h / 2) - 800 / 2;
	mPosY = (character.getPosY() + character.rect.w / 2) - 600 / 2;

	//Keep the camera in bounds
	if (mPosX < 0)
	{
		mPosX = 0;
	}
	if (mPosY < 0)
	{
		mPosY = 0;
	}
	if (mPosX > level.getWidth() - camera.w)
	{
		mPosX = level.getWidth() - camera.w;
	}
	if (mPosY > level.getHeight() - camera.h)
	{
		mPosY = level.getHeight() - camera.h;
	}
}