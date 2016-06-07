#include "Sprite.h"
#include "SDL_image.h"
#include "SDL.h"
#include "GameEngine.h"

namespace gameEngine {

	Sprite::Sprite(int x, int y, int w, int h, std::string imgPath, bool transp, std::string spriteType) :
		rect(x, y, w, h)
	{
		SDL_Surface* surface = IMG_Load(imgPath.c_str());
		if (surface == nullptr)
			throw std::runtime_error("surface is null");

		texture = SDL_CreateTextureFromSurface(currentGameEngine().getRenderer(), surface);
		if (texture == nullptr)
			throw std::runtime_error("texture is null");
		
		type = spriteType;
		movementVelocityX = 0;
		movementVelocityY = 0;

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
			
		texture = SDL_CreateTextureFromSurface(currentGameEngine().getRenderer(), dstSurface);
		if (texture == nullptr)
			throwException("texture is null", SDL_GetError);

		type = spriteType;
		movementVelocityX = 0;
		movementVelocityY = 0;

		//SDL_FreeSurface(surface);
		SDL_FreeSurface(dstSurface);
	}

	Sprite::Sprite(int x, int y, int w, int h, SDL_Surface* surface, std::string spriteType) :
		rect(x, y, w, h)
	{
		type = spriteType;
		movementVelocityX = 0;
		movementVelocityY = 0;
		texture = SDL_CreateTextureFromSurface(currentGameEngine().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	// "invisible" sprite
	Sprite::Sprite() 
	{
		texture = nullptr;
	}

	void Sprite::draw() 
	{
		float w = rect.w;
		float h = rect.h;
		
		SDL_GL_BindTexture(texture, &w, &h);

		glEnable(GL_BLEND);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor3ub(255, 255, 255);

		glBegin(GL_QUADS);

		// Top Left
		glTexCoord2f(0, 1);
		glVertex2f(rect.x, rect.y);

		// Top Right
		glTexCoord2f(1, 1);
		glVertex2f(rect.x + rect.w, rect.y);

		// Bottom Right
		glTexCoord2f(1, 0);
		glVertex2f(rect.x + rect.w, rect.y + rect.h);

		// Bottom Left
		glTexCoord2f(0, 0);
		glVertex2f(rect.x, rect.y + rect.h);

		glEnd();
		//SDL_RenderCopy(currentGameEngine().getRenderer(), texture, NULL, &rect);
	}

	void Sprite::applyMotion()
	{
		rect.x += movementVelocityX;
		rect.y += movementVelocityY;
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
