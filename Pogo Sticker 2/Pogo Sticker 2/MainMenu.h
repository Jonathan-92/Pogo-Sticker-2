#ifndef MAINMENU_H
#define MAINMENU_H
#include "Sprite.h"
#include <list>
#include "SDL_ttf.h"

namespace mainMenu {

	class MainMenu {
	public:
		MainMenu();
		~MainMenu();
		int start();
		bool init();
		bool loadMedia();
	private:
		SDL_Window* screen;
		SDL_Renderer* renderer;
		TTF_Font* font;
		int fps;
	};

	void throwException(std::string, const char* (*errorFunc)());
}

#endif