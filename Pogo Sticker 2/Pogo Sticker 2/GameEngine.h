#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include <list>
#include "SDL_ttf.h"

namespace gameEngine {

	class GameEngine {
	public:
		GameEngine();
		~GameEngine();
		void run();
		void add(Sprite* sprite);
		void remove(Sprite* sprite);
		void setBackground(const char* path);
		void setVideoMode(int w, int h);
		void setFps(int i);
		std::list<Sprite*> getSprites() const;
		SDL_Renderer* getRenderer();
		TTF_Font* getFont();
		void delay(int ticks);
	private:
		SDL_Window* screen;
		SDL_Renderer* renderer;
		TTF_Font* font;
		int fps;
		std::string bgPath;
		std::list<Sprite*> sprites;
		std::list<Sprite*>::iterator itTick;
		void forAll(void (Sprite::*membrPtr)(int, int), int x, int y);
	};

	GameEngine& ge();
	void throwException(std::string, const char* (*errorFunc)());
}

#endif