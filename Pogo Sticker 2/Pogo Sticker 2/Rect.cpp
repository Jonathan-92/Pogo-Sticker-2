#include "Rect.h"

namespace gameEngine {
	Rect::Rect(){
		x = y = h = w = 0; 
	}

	Rect::Rect(int xx, int yy, int ww, int hh){
		x = xx; y = yy; w = ww; h = hh;
	}

	bool Rect::contains(int xx, int yy) const{
		return xx >= x && xx <= x + w && yy >= y && yy <= y + h;
	}

	int Rect::centeredX() {
		return x + w / 2;
	}

	int Rect::centeredY() {
		return y + h / 2;
	}

	Rect Rect::centeredRect(int width, int height) const{
		return Rect(x + w/2 - width/2, y + h/2 - height/2, width, height);
	}

	bool Rect::overlaps(const Rect& other) const{
		int left1   = x;
		int left2   = other.x;
		int right1  = x + w;
		int right2  = other.x + other.w;
		int top1    = y;
		int top2    = other.y;
		int bottom1 = y + h;
		int bottom2 = other.y + other.h;

		if (bottom1 < top2) return false;
		if (top1 > bottom2) return false;

		if (right1 < left2) return false;
		if (left1 > right2) return false;

		return true;
	}

	void Rect::setRect(int xx, int yy, int ww, int hh) {
		x = xx;
		y = yy;
		w = ww;
		h = hh;
	}
}