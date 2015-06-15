#ifndef MAINMENU_H
#define MAINMENU_H
#include "Sprite.h"
#include <list>
#include "SDL_ttf.h"
#include "ViewPort.h"

class MainMenu : public ViewPort {
public:
	static MainMenu* getInstance();
	~MainMenu();
	void init();
private:
	MainMenu();
};


#endif