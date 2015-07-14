#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include "Camera.h"
#include "Viewport.h"
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
		void load(SDL_Texture* background, std::list<Sprite*> sprites, Level* level);
		void load(SDL_Texture* background, std::list<Sprite*> sprites);
		void delay(int ticks);
		std::list<Sprite*> getSprites() const;
		SDL_Renderer* getRenderer();
		TTF_Font* getFont();
		bool switched;
	private:
		SDL_Window* screen;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Camera* camera;
		Level* level;
		int fps;
		SDL_Texture* background;
		std::list<Sprite*> sprites;
		std::list<Sprite*>::iterator it2;
		std::list<Sprite*>::iterator itTick;
		void forAll(void (Sprite::*membrPtr)(int, int), int x, int y);
	};

	GameEngine& ge();
	void throwException(std::string, const char* (*errorFunc)());
}

#endif