#include "Label.h"
#include <string>
#include "Sprite.h"
#include "GameEngine.h"

using namespace std;

namespace gameEngine {

	Label::Label(int x, int y, int w, int h, string text, FuncPtr fp) :
		Sprite(x, y, w, h, TTF_RenderText_Solid(ge().getFont(), text.c_str(), black)),
		funcPtr(fp)
	{
	}

	Label::Label(int x, int y, int w, int h, string text) :
		Label(x, y, w, h, text, nullptr)
	{
	}

	const SDL_Color Label::black = { 0, 0, 0 };

	void Label::tick() {
		if (funcPtr != nullptr)
			setText(funcPtr());
	}

	void Label::setText(string text)
	{
		SDL_DestroyTexture(texture);
		SDL_Surface* surface = TTF_RenderText_Solid(ge().getFont(), text.c_str(), black);
		texture = SDL_CreateTextureFromSurface(ge().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	Label* Label::getInstance(int x, int y, int w, int h, string text, FuncPtr fp){
		return new Label(x, y, w, h, text, fp);
	}

	Label* Label::getInstance(int x, int y, int w, int h, string text){
		return new Label(x, y, w, h, text);
	}

	Label::~Label()
	{
	}

}