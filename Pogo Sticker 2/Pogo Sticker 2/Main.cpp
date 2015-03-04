#include "SDL.h"
#include <iostream>

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Quit();
	
	return 0;
}