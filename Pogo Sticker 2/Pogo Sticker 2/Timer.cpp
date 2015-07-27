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

void Timer::tick()
{
	if (timerStarted == false)
	{
		startTime = SDL_GetTicks();
		timerStarted = true;
	}
	int time = SDL_GetTicks() - startTime;
	if (time > lastTime)
	{
		milliseconds += time - lastTime;
		if (milliseconds >= 1000)
		{
			milliseconds = 0;
			seconds += 1;
		}
		if (seconds == 60)
		{
			seconds = 0;
			minutes += 1;
		}
		lastTime = time;
	}

	setTimeLabel();
}

void Timer::setTimeLabel()
{
	std::ostringstream convert;
	convert << minutes << ":" << seconds << ":" << milliseconds / 10;
	Label::setText(convert.str());
}