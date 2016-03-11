#include "MainMenu.h"
#include "GameEngine.h"
#include <gl/freeglut.h>

using namespace gameEngine;

MainMenu* mainMenu = MainMenu::getInstance();


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);

	mainMenu->init();
	mainMenu->load();

	currentGameEngine().run();

	return 0;
}