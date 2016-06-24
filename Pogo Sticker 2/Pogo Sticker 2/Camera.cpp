#include "Camera.h"
#include "GameEngine.h"
#include "SDL.h"

using namespace gameEngine;

Camera::Camera()
{
	rect = { 0, 0, 800, 640 };
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
	//TODO: Change screensize to variables
	rect.updateXYvalues(character->rect.centeredX() - 800 / 2, character->rect.centeredY() - 640 / 2);

	//Keep the camera in bounds
	if (rect.getX() < 0)
	{
		rect.updateXYvalues(0, rect.getY());
	}
	if (rect.getY() < 0)
	{
		rect.updateXYvalues(rect.getX(), 0);
	}
	if (rect.getX() > level->getWidth() - rect.getWidth())
	{
		rect.updateXYvalues(level->getWidth() - rect.getWidth(), rect.getY());
	}
	if (rect.getY() > level->getHeight() - rect.getHeight())
	{
		rect.updateXYvalues(rect.getX(), level->getHeight() - rect.getHeight());
	}
}