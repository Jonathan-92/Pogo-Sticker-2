#include <SDL.h>
#include "Label.h"

//The dot that will move around on the screen
class Timer : public gameEngine::Label
{
public:
	//Initializes the variables
	Timer(int x, int y, int w, int h, std::string imgPath);
	~Timer(void);

	//Sets the text
	virtual void setText(std::string text);

	virtual void tick();

private:
	//The X and Y offsets of the dot
	int milliseconds, seconds, minutes;
};