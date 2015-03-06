#include "SDL.h"
#include <iostream>

//The window we'll be rendering to 
SDL_Window* gWindow = NULL; 
//The surface contained by the window 
SDL_Surface* gScreenSurface = NULL; 
//The image we will load and show on the screen 
SDL_Surface* gHelloWorld = NULL;

const int SCREEN_HEIGHT = 860;
const int SCREEN_WIDTH = 600;

bool init() { 
	//Initialization flag 
	bool success = true; 
	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); success = false; 
	} 
	else { 
		//Create window 
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		if( gWindow == NULL ) { 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); success = false; 
		} 
		else { 
			//Get window surface 
			gScreenSurface = SDL_GetWindowSurface( gWindow ); 
		} 
	} 
	return success; 
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		return 1;
	}
	init();

	bool quit = false;

	SDL_Event sdl_event;

	while (!quit)
	{
		while (SDL_PollEvent(&sdl_event) != 0) 
		{ 
			//User requests quit 
			if( sdl_event.type == SDL_QUIT ) { 
				quit = true; 
			} 
		}
	}
	SDL_Quit();
	
	return 0;
}