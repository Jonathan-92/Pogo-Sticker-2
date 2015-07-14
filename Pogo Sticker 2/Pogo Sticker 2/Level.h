#ifndef LEVEL_H
#define LEVEL_H
#include "ViewPort.h"

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
		int getHeight();
		int getWidth();
	private:
		int levelHeight;
		int levelWidth;
	};
}

#endif