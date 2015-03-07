#include "Sprite.h"
#include "GameEngine.h"

namespace gameEngine {

	Sprite::Sprite(int x, int y, int w, int h, std::string imgPath, bool transp) :
		rect(x, y, w, h)
	{
		SDL_Surface* surface = SDL_LoadBMP(imgPath.c_str());
		if (surface == nullptr)
			throw std::runtime_error("surface is null");
		
		if (transp) {
			Uint32 transp = *(Uint32*)surface->pixels;
			SDL_SetColorKey(surface, SDL_RLEACCEL, transp); 
		}

		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		if (texture == nullptr)
			throw std::runtime_error("texture is null");
		
		SDL_FreeSurface(surface);
	}

	Sprite::Sprite(int x, int y, int w, int h, SDL_Surface* surface) :
		rect(x, y, w, h)
	{
		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	// "invisible" sprite
	Sprite::Sprite() {
		texture = nullptr;
	}

	void Sprite::draw() {
		SDL_RenderCopy(ge().getRenderer(), texture, nullptr, &rect);
	}

	Sprite::~Sprite()
	{
		if (texture != nullptr)
			SDL_DestroyTexture(texture);
	}

}