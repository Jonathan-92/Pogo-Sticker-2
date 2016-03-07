#include "MainMenu.h"
#include "Label.h"
#include "G_Button.h"
#include "GameEngine.h"

using namespace gameEngine;

MainMenu* mainMenu = MainMenu::getInstance();


int main(int argc, char** argv) 
{
	mainMenu->init();
	mainMenu->load();

	currentGameEngine().run();

	return 0;
}