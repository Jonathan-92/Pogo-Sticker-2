#include "GameEngine.h"
#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

namespace gameEngine {

	void throwException(string msg, const char* (*errorFunc)()) {
		msg += errorFunc();
		throw runtime_error(msg.c_str());
	}

	GameEngine& ge() {
		static GameEngine* ge = new GameEngine();
		return *ge;
	}

	GameEngine::GameEngine() : fps(60) {		// lägg till fler null checkar
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throwException("Failed initialize SDL", SDL_GetError);

		if (TTF_Init() == -1)
			throwException("Failed initialize TTF", TTF_GetError);

		font = TTF_OpenFont("C:/Windows/Fonts/arialbd.ttf", 12);
		if (font == nullptr)
			throwException("Failed to open font.", TTF_GetError);

		screen = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
			20, 800, 600, SDL_WINDOW_OPENGL);
		if (screen == nullptr)
			throwException("Failed creating window.", SDL_GetError);

		renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
			throwException("Failed creating renderer.", SDL_GetError);
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

	void GameEngine::setVideoMode(int w, int h) {
		SDL_SetWindowSize(screen, w, h);
	}

	void GameEngine::setFps(int i) {
		fps = i;
	}

	void GameEngine::setBackground(const char* path) {
		bgPath = path;
	}

	std::list<Sprite*> GameEngine::getSprites() const {
		return sprites;
	}

	void GameEngine::run() {
		SDL_Surface* bgSurface = SDL_LoadBMP(bgPath.c_str());	// undantagshantering?
		SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
		SDL_FreeSurface(bgSurface); 
		bool exited = false;

		const int tickInterval = 1000 / fps;
		Uint32 nextTick;
		int delay;

		while (!exited) {
			nextTick = SDL_GetTicks() + tickInterval;

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);
			
			for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++) {
				(*it)->draw();
			}

			SDL_Event event;
			while (SDL_PollEvent(&event)) {

				switch (event.type) {
				case SDL_QUIT:
					exited = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					forAll(&Sprite::mouseDown, event.button.x, event.button.y);
					break;
				case SDL_MOUSEMOTION:
					if (event.button.state == SDL_PRESSED) {
						forAll(&Sprite::mousePressed, event.button.x, event.button.y);
					}
					break;
				case SDL_KEYDOWN:
					for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++) {
						(*it)->keyDown(event);
					}
					break;
				}
			}

			if (event.button.state == SDL_PRESSED) {
				forAll(&Sprite::mousePressed, event.button.x, event.button.y);
			}

			for (itTick = sprites.begin(); itTick != sprites.end(); itTick++) {
				(*itTick)->tick();
			}

			SDL_RenderPresent(renderer);

			delay = nextTick - SDL_GetTicks();

			if (delay > 0)
				SDL_Delay(delay);
		} 
	}

	void GameEngine::delay(int ticks) {
		SDL_Delay(ticks);
	}
	
	void GameEngine::forAll(void (Sprite::*membrPtr)(int, int), int x, int y) {
		for (std::list<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++) {
			((*it)->*membrPtr)(x, y);
		}
	}

	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	void GameEngine::remove(Sprite* sprite) {
		itTick = sprites.erase(std::find(sprites.begin(), sprites.end(), sprite));
	}
}