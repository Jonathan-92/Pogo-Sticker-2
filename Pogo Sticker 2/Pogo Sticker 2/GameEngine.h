#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include "Camera.h"
#include "Tile.h"
#include "CollisionHandling.h"
#include <list>
#include "SDL_ttf.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <future>

namespace gameEngine {

	class GameEngine {
	public:
		GameEngine();
		~GameEngine();
		void add(Sprite* sprite);
		void remove(Sprite* sprite);
		void setBackground(const char* path);
		void setVideoMode(int w, int h);
		void setFps(int i);
		void load(SDL_Texture* background, std::list<Sprite*> sprites, std::list<Tile*> tiles, Level* level, std::list<WorldObject*> worldObjectsArg);
		void load(SDL_Texture* background, std::list<Sprite*> sprites);
		void delay(int ticks);
		void setEndstate(bool state);
		void run();
		std::list<Sprite*> getSprites() const;
		std::list<Tile*> getTiles() const;
		std::list<WorldObject*> getWorldObjects() const;
		std::deque<std::packaged_task<void()>> tasks;
		std::mutex tasks_mutex;
		SDL_Renderer* getRenderer();
		TTF_Font* getFont();
		Camera& getCamera();
		SDL_Window* getScreen();
		Level* getLevel();
		CollisionHandling* getCollider();
		SDL_GLContext getMaincontext();
		bool switched;
	private:
		SDL_Window* screen;
		SDL_GLContext maincontext;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Camera* camera;
		Level* level;
		CollisionHandling* collision;
		bool exited;
		bool paused;
		bool endstate;
		int fps;
		SDL_Texture* background;
		std::list<Sprite*> sprites;
		std::list<Tile*> tiles;
		std::list<WorldObject*> worldObjects;
		std::list<Sprite*>::iterator it2;
		std::list<Sprite*>::iterator itTick;
		void forAll(void (Sprite::*membrPtr)(int, int), int x, int y);
		void checkPause();
		void drawSprites();
		void drawWorldObjects();
		void executeTasks();
		void handleEvents();
		void handleTicks();
		void runDrawCalls();
		void runPhysicsCalls();
		void runEventCalls();
	};

	GameEngine& currentGameEngine();
	void throwException(std::string, const char* (*errorFunc)());
}

#endif