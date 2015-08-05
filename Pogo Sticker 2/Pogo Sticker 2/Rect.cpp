#include "Rect.h"

namespace gameEngine {
	Rect::Rect() {
		x = y = h = w = 0; 
	}

	Rect::Rect(int xx, int yy, int ww, int hh) {
		x = xx; y = yy; w = ww; h = hh;
	}

	bool Rect::contains(int xx, int yy) const {
		return xx >= x && xx <= x + w && yy >= y && yy <= y + h;
	}

	int Rect::centeredX() {
		return x + w / 2;
	}

	int Rect::centeredY() {
		return y + h / 2;
	}

	Rect Rect::centeredRect(int width, int height) const {
		return Rect(x + w / 2 - width / 2, y + h / 2 - height / 2, width, height);
	}

	bool Rect::overlaps(const Rect& other) const {
		int left			= x;					// left side of the rect
		int other_left		= other.x;				// other rect's left side
		int right			= x + w;				// etc...
		int other_right		= other.x + other.w;
		int top				= y;
		int other_top		= other.y;
		int bottom			= y + h;
		int other_bottom	= other.y + other.h;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}

	void Rect::setRect(int xx, int yy, int ww, int hh) {
		x = xx;
		y = yy;
		w = ww;
		h = hh;
	}
}