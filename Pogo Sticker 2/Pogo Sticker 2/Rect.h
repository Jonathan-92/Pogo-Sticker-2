#ifndef RECT_H
#define RECT_H
#include "Vector2D.h"

namespace gameEngine {
	/* Acts as the bounds and position which Sprites will be displayed on.
	Extends SDL_Rect and provides additional operations. */
	class Rect {
	private:
		double x, y, width, height;

		/* The angle of the rectangles rotation */
		float angle;
	public:
		Rect();		
		
		/*
		param "xx" = x coordinate position in pixels
		param "yy" = y coordinate position in pixels
		param "ww" = width in pixels
		param "hh" = height in pixels */
		Rect(double xParameter, double yParameter, double widthParameter, double heightParameter);

		int RotRectsCollision(Rect * rr1, Rect * rr2);

		/* Checks whether another Rect is within this Rect's bounds. */
		bool contains(int xx, int yy) const;

		/* Returns the x coordinate in the middle of this instance */
		int centeredX();

		/* Returns the y coordinate in the middle of this instance */
		int centeredY();

		double maxXvalue();
		double maxYvalue();

		double getX()
		{
			return x;
		};
		double getY()
		{
			return y;
		};
		double getWidth()
		{
			return width;
		}
		double getHeight()
		{
			return height;
		}

		void applyMotion(double xMotion, double yMotion);

		void updateXYvalues(double xx, double yy);

		void draw();

		Vector2D centerPoint();

		/* Creates a new rectangle that is centered on this instance */
		Rect centeredRect(int width, int height) const;

		/* Returns true if the other rectangle overlaps this instance */
		bool overlaps(const Rect& other) const;

		/* Changes the location and size of this instance according to the
		arguments supplied. */
		void setRect(double xParameter, double yParameter, double widthParameter, double heightParameter);
	};
}

#endif
