#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include "Camera.h"
#include "Viewport.h"
#include "Tile.h"
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
		void load(SDL_Texture* background, std::list<Sprite*> sprites, std::list<Tile*> tiles, Level* level);
		void load(SDL_Texture* background, std::list<Sprite*> sprites);
		void delay(int ticks);
		std::list<Sprite*> getSprites() const;
		std::list<Tile*> getTiles() const;
		SDL_Renderer* getRenderer();
		TTF_Font* getFont();
		Camera& getCamera();
		SDL_Window* getScreen();
		Level* getLevel();
		bool switched;
	private:
		SDL_Window* screen;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Camera* camera;
		Level* level;
		bool exited;
		bool paused;
		int fps;
		SDL_Texture* background;
		std::list<Sprite*> sprites;
		std::list<Tile*> tiles;
		std::list<Sprite*>::iterator it2;
		std::list<Sprite*>::iterator itTick;
		void forAll(void (Sprite::*membrPtr)(int, int), int x, int y);
		//Loop functions
		void checkPause();
		void drawSprites();
		void handleEvents();
		void handleTicks();
	};

	GameEngine& ge();
	void throwException(std::string, const char* (*errorFunc)());
}

#endif