#ifndef LEVEL_H
#define LEVEL_H
#include "ViewPort.h"
#include "ReadFile.h"

namespace gameEngine
{
	class Level : public ViewPort
	{
	public:
		Level();
		~Level();
		void init();
		void load();
		void setBackground(SDL_Surface* surface);
		void levelCompleted();
		int getHeight();
		int getWidth();
	private:
		int levelHeight;
		int levelWidth;
		int tileHeight;
		int tileWidth;
		ReadFile* fileReader;
	};
}

#endif