#include "Timer.h"
#include <sstream>
#include "GameEngine.h"

Timer::Timer(int x, int y, int w, int h, std::string imgPath) : Label(x, y, w, h, imgPath, false)
{
	//Initialize the offsets
	milliseconds = 0;
	seconds = 0;
	minutes = 0;
}

Timer::~Timer(void)
{
}

void Timer::setText(std::string text)
{
	SDL_DestroyTexture(texture);
	SDL_Surface* surface = TTF_RenderText_Solid(gameEngine::ge().getFont(), text.c_str(), Label::black);
	texture = SDL_CreateTextureFromSurface(gameEngine::ge().getRenderer(), surface);
	SDL_FreeSurface(surface);
}

void Timer::tick()
{
	if (milliseconds == 100)
	{
		milliseconds = 0;
		seconds += 1;
	}
	if (seconds == 60)
	{
		seconds = 0;
		minutes += 1;
	}
	milliseconds += 2;
	std::ostringstream convert;
	convert << minutes << ":" << seconds << ":" << milliseconds;
	Label::setText(convert.str());
}