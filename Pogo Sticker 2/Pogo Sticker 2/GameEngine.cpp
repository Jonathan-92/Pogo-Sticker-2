#include "GameEngine.h"
#include <SDL.h>
#include <string>
#include <iostream>
#include "G_Button.h"

using namespace std;

namespace gameEngine {

	void throwException(string msg, const char* (*errorFunc)()) {
		msg += errorFunc();
		throw runtime_error(msg.c_str());
	}

	GameEngine& currentGameEngine() {
		static GameEngine* gameEngine = new GameEngine();
		return *gameEngine;
	}

	GameEngine::GameEngine() : fps(60) {		// l�gg till fler null checkar
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throwException("Failed initialize SDL", SDL_GetError);

		if (TTF_Init() == -1)
			throwException("Failed initialize TTF", TTF_GetError);

		font = TTF_OpenFont("C:/Windows/Fonts/arialbd.ttf", 12);
		if (font == nullptr)
			throwException("Failed to open font.", TTF_GetError);

		screen = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
			20, 800, 640, SDL_WINDOW_OPENGL);
		if (screen == nullptr)
			throwException("Failed creating window.", SDL_GetError);

		renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
			throwException("Failed creating renderer.", SDL_GetError);

		camera = new Camera();
		collision = new CollisionHandling();
		exited = false;
	}
	
	GameEngine::~GameEngine(void)
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(screen);
		SDL_Quit();
	}
	
	SDL_Renderer* GameEngine::getRenderer() {
		return renderer;
	}

	TTF_Font* GameEngine::getFont() {
		return font;
	}

	CollisionHandling* GameEngine::getCollider()
	{
		return collision;
	}

	Camera& GameEngine::getCamera()
	{
		return *camera;
	}

	SDL_Window* GameEngine::getScreen()
	{
		return screen;
	}

	void GameEngine::setVideoMode(int w, int h) {
		SDL_SetWindowSize(screen, w, h);
	}

	void GameEngine::setFps(int i) {
		fps = i;
	}

	Level* GameEngine::getLevel()
	{
		return level;
	}

	std::list<Sprite*> GameEngine::getSprites() const {
		return sprites;
	}

	std::list<Tile*> GameEngine::getTiles() const {
		return tiles;
	}

	void GameEngine::load(SDL_Texture* background2, list<Sprite*> sprites2, list<Tile*> tiles2, Level* level2)
	{
		level = level2;
		background = background2;
		sprites = sprites2;
		tiles = tiles2;
		it2 = sprites.begin();
		switched = true;
		paused = false;
		endstate = false;
	}

	void GameEngine::load(SDL_Texture* background2, list<Sprite*> sprites2)
	{
		background = background2;
		sprites = sprites2;
		it2 = sprites.begin();
		switched = true;
		paused = false;
		endstate = false;
	}

	void GameEngine::run() {
		//TODO: Dela upp koden i funktioner
		const int tickInterval = 1000 / fps;
		Uint32 nextTick;
		int delay;

		while (!exited) {
			switched = false;
			nextTick = SDL_GetTicks() + tickInterval;

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, background, nullptr, nullptr);
			
			drawSprites();
			checkPause();
			if (!paused)
			{
				handleEvents();
				if (!endstate)
				{
					handleTicks();
				}
			}

			SDL_RenderPresent(renderer);

			delay = nextTick - SDL_GetTicks();

			if (delay > 0)
				SDL_Delay(delay);
		} 
	}

	void GameEngine::setEndstate(bool state)
	{
		endstate = state;
	}

	void GameEngine::checkPause()
	{
		if (paused)
		{
			SDL_Event event;
			SDL_PollEvent(&event);
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_p)
					paused = false;
			}
		}
	}

	void GameEngine::drawSprites()
	{
		for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++) 
		{			
			(*it)->draw();
		}
	}
	void GameEngine::handleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) {
			case SDL_QUIT:
				exited = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.state == SDL_PRESSED) {
					forAll(&Sprite::mouseDown, event.button.x, event.button.y);
				}
				break;
			case SDL_MOUSEMOTION:
				forAll(&Sprite::mouseMotion, event.button.x, event.button.y);
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_p)
				{
					paused = true;
					continue;
				}
				for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++) {
					(*it)->keyDown(event);
				}
				break;
			case SDL_KEYUP:
				for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++) {
					(*it)->keyUp(event);
				}
				break;
			}
		}
	}

	void GameEngine::handleTicks()
	{
		for (itTick = sprites.begin(); itTick != sprites.end(); itTick++) {
			(*itTick)->tick();
			if ((*itTick)->getType() == "Character")
			{
				camera->tick();
			}
		}
	}
	
	void GameEngine::forAll(void (Sprite::*membrPtr)(int, int), int x, int y) {
		for (it2 = sprites.begin(); it2 != sprites.end(); it2++) {
			((*it2)->*membrPtr)(x, y);
			if (switched)
			{
				return;
			}
		}
	}

	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	void GameEngine::remove(Sprite* sprite) {
		itTick = sprites.erase(std::find(sprites.begin(), sprites.end(), sprite));
	}
}