#include "Sprite.h"
#include "GameEngine.h"
#include "SDL_image.h"

namespace gameEngine {

	Sprite::Sprite(int x, int y, int w, int h, std::string imgPath, bool transp, std::string spriteType) :
		rect(x, y, w, h)
	{
		SDL_Surface* surface = IMG_Load(imgPath.c_str());
		if (surface == nullptr)
			throw std::runtime_error("surface is null");

		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		if (texture == nullptr)
			throw std::runtime_error("texture is null");
		
		type = spriteType;

		SDL_FreeSurface(surface);
	}

	Sprite::Sprite(int x, int y, int w, int h, SDL_Surface* surface, std::string spriteType) :
		rect(x, y, w, h)
	{
		type = spriteType;
		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	// "invisible" sprite
	Sprite::Sprite() {
		texture = nullptr;
	}

	void Sprite::draw(Sprite* cameraRect) {
		SDL_RenderCopy(ge().getRenderer(), texture, &cameraRect->rect, &rect);
	}

	Sprite::~Sprite()
	{
		if (texture != nullptr)
			SDL_DestroyTexture(texture);
	}

	int Sprite::getPosX()
	{
		return rect.x;
	}

	int Sprite::getPosY()
	{
		return rect.y;
	}

	std::string Sprite::getType()
	{
		return type;
	}

}