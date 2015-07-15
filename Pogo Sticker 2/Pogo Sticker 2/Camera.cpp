#include "Camera.h"
#include "GameEngine.h"
#include "SDL.h"

using namespace gameEngine;

Camera::Camera()
{
	rect = { 0, 0, 800, 600 };
}

Camera::~Camera(void)
{
}

void Camera::setCharacter(Character* character)
{
	this->character = character;
}

void Camera::setLevel(Level* level)
{
	this->level = level;
}

void Camera::tick()
{
	if (character == nullptr || level == nullptr)
		return;
	//800 600 skärmen ändra
	rect.x = (character->rect.x + character->rect.w / 2) - 800 / 2;
	rect.y = (character->rect.y + character->rect.h / 2) - 600 / 2;

	//Keep the camera in bounds
	if (rect.x < 0)
	{
		rect.x = 0;
	}
	if (rect.y < 0)
	{
		rect.y = 0;
	}
	if (rect.x > level->getWidth() - rect.w)
	{
		rect.x = level->getWidth() - rect.w;
	}
	if (rect.y > level->getHeight() - rect.h)
	{
		rect.y = level->getHeight() - rect.h;
	}
}