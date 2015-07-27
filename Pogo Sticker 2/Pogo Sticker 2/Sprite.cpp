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

		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		if (texture == nullptr)
			throw std::runtime_error("texture is null");
		
		type = spriteType;

		SDL_FreeSurface(surface);
	}

	//For tilemaps
	Sprite::Sprite(int x, int y, int w, int h, SDL_Rect* sourceRect, SDL_Surface* surface , bool transp, std::string spriteType) :
		rect(x, y, w, h)
	{
		//32 = Current tilesize

		SDL_Surface* surface2 = SDL_CreateRGBSurface(0, sourceRect->w, sourceRect->h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x00000000);

		if (surface2 == nullptr)
			throwException("surface2 is null ", SDL_GetError);
			
		if (surface == nullptr)
			throw std::runtime_error("surface is null");

		//Where in the rect the drawing should start
		SDL_Rect DestR;
		DestR.x = 0;
		DestR.y = 0;
		DestR.h = sourceRect->h;
		DestR.w = sourceRect->w;

		//Take part of an image as texture only
		SDL_BlitSurface(surface, sourceRect, surface2, &DestR);


		//SDL_BlitSurface(surface, sourceRect, surface2, &DestR);
		if (surface2 == nullptr)
			throwException("surface2 is null ", SDL_GetError);
			
		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface2);
		if (texture == nullptr)
			throw std::runtime_error("texture is null");

		type = spriteType;

		//SDL_FreeSurface(surface);
		//SDL_FreeSurface(surface2);
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
