#ifndef RECT_H
#define RECT_H
#include <SDL.h>

namespace gameEngine {

	/* Acts as the bounds and position which Sprites will be displayed on.
	Extends SDL_Rect and provides additional operations. */
	struct Rect : public SDL_Rect {
	public:
		Rect();

		/*
		param "xx" = x coordinate position in pixels
		param "yy" = y coordinate position in pixels
		param "ww" = width in pixels
		param "hh" = height in pixels */
		Rect(int xx, int yy, int ww, int hh);

		int RotRectsCollision(Rect * rr1, Rect * rr2);

		/* Checks whether another Rect is within this Rect's bounds. */
		bool contains(int xx, int yy) const;

		/* Returns the x coordinate in the middle of this instance */
		int centeredX();

		/* Returns the y coordinate in the middle of this instance */
		int centeredY();

		/* Creates a new rectangle that is centered on this instance */
		Rect centeredRect(int width, int height) const;

		/* Returns true if the other rectangle overlaps this instance */
		bool overlaps(const Rect& other) const;

		/* Changes the location and size of this instance according to the
		arguments supplied. */
		void setRect(int x, int y, int w, int h);

		/* The angle of the rectangles rotation */
		float angle;
	};
}

#endif
