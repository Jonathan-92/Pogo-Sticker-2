#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>
#include "Label.h"

// A timer that keeps track of how long the player has played the level.
class Timer : public gameEngine::Label
{
public:
	//Initializes the variables
	Timer(int x, int y, int w, int h, std::string imgPath);
	~Timer(void);

	virtual void tick();

private:
	void setTimeLabel();
	Uint32 startTime = 0, lastTime;
	bool timerStarted = false;
	int milliseconds, seconds, minutes;
};
#endif