#include "MainMenu.h"
#include "GameEngine.h"
#include <gl/freeglut.h>

using namespace gameEngine;

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);

	MainMenu* mainMenu = MainMenu::getInstance();
	mainMenu->init();
	mainMenu->load();

	currentGameEngine().run();

	return 0;
}