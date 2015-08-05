#include "Sprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include "SDL.h"

namespace gameEngine {

	Sprite::Sprite(int x, int y, int w, int h, std::string imgPath, bool transp, std::string spriteType) :
		rect(x, y, w, h)
	{
		SDL_Surface* surface = IMG_Load(imgPath.c_str());
		if (surface == nullptr)
			throw std::runtime_error("surface is null");

		if (transp) 
		{
			Uint32 transp = *(Uint32*)surface->pixels;
			SDL_SetColorKey(surface, SDL_RLEACCEL, transp);
		}

		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		if (texture == nullptr)
			throw std::runtime_error("texture is null");
		
		type = spriteType;

		SDL_FreeSurface(surface);
	}

	//For tilemaps
	Sprite::Sprite(int x, int y, int w, int h, SDL_Rect* sourceRect, SDL_Surface* srcSurface , bool transp, std::string spriteType) :
		rect(x, y, w, h)
	{
		if (srcSurface == nullptr)
			throw std::runtime_error("surface is null");

		//32 = Current tilesize
		SDL_Surface* dstSurface = SDL_CreateRGBSurface(0, sourceRect->w, sourceRect->h, 32, 0, 0, 0, 0);
		if (dstSurface == nullptr)
			throwException("surface2 is null ", SDL_GetError);

		//Take part of an image as texture only
		SDL_BlitSurface(srcSurface, sourceRect, dstSurface, nullptr);

		if (dstSurface == nullptr)
			throwException("surface2 is null ", SDL_GetError);
			
		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), dstSurface);
		if (texture == nullptr)
			throwException("texture is null", SDL_GetError);

		type = spriteType;

		//SDL_FreeSurface(surface);
		SDL_FreeSurface(dstSurface);
	}

	Sprite::Sprite(int x, int y, int w, int h, SDL_Surface* surface, std::string spriteType) :
		rect(x, y, w, h)
	{
		type = spriteType;
		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	// "invisible" sprite
	Sprite::Sprite() 
	{
		texture = nullptr;
	}

	void Sprite::draw() 
	{
		SDL_RenderCopy(ge().getRenderer(), texture, NULL, &rect);
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
