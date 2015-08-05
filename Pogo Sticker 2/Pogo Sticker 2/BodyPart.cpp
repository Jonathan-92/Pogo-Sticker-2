#include "BodyPart.h"
#include "GameEngine.h"

using namespace gameEngine;

BodyPart::BodyPart(int x, int y, int w, int h, std::string imgPath, std::string type) : Sprite(x, y, w, h, imgPath, false, type)
{

}

BodyPart::~BodyPart(void)
{

}

void BodyPart::draw()
{
	SDL_Rect drawingRect = { rect.x - ge().getCamera().rect.x, rect.y - ge().getCamera().rect.y, rect.w, rect.h };
	SDL_RenderCopyEx(gameEngine::ge().getRenderer(), texture, nullptr, &drawingRect, angle, NULL, SDL_FLIP_NONE);
}
