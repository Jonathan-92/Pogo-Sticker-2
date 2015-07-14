#ifndef SPRITE_H
#define SPRITE_H
#include "Rect.h"
#include <string>

namespace gameEngine {

	class Sprite {
	public:
		virtual ~Sprite();
		Rect rect;
		virtual void draw(Sprite* cameraRect);
		virtual void tick(){}
		virtual void mouseDown(int x, int y){}
		virtual void mouseMotion(int x, int y){}
		virtual void keyDown(SDL_Event& e){}
		virtual void keyUp(SDL_Event& e){}
		virtual void collisonCheck(gameEngine::Sprite *sprites[]){}
		virtual int getPosX();
		virtual int getPosY();
		virtual std::string getType();
	protected:
		SDL_Texture* texture;
		std::string type;
		Sprite(int x, int y, int w, int h, std::string imgPath, bool transp, std::string spriteType);
		Sprite(int x, int y, int w, int h, SDL_Surface* surface, std::string spriteType);
		Sprite();
	private:
		Sprite(const Sprite&);
		const Sprite& operator=(const Sprite&);
	};

}

#endif