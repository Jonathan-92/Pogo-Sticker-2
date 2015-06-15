#ifndef G_BUTTON_H
#define G_BUTTON_H
#include "Sprite.h"
#include <SDL.h>

namespace gameEngine {
	class G_Button : public gameEngine::Sprite {
	public:
		typedef void (*FuncPtr)();

		//
		G_Button(int x, int y, int w, int h, std::string imgPath, FuncPtr fp);
		~G_Button(void);
		void tick();
		void mouseDown(int x, int y);
		void disable();
	private:
		FuncPtr funcPtr;
		bool enabled;
	};

}

#endif