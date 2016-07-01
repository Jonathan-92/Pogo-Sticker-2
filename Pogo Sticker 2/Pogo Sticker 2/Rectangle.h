#ifndef RECT_H
#define RECT_H
#include "Polygon.h"

namespace gameEngine {
	/* Acts as the bounds and position which Sprites will be displayed on.
	Extends SDL_Rect and provides additional operations. */
	class Rectangle : public Polygon {
	private:
		double x, y, width, height;
		/* The angle of the rectangles rotation */
		float angle;
	public:
		Rectangle();
		
		/*
		param "xx" = x coordinate position in pixels
		param "yy" = y coordinate position in pixels
		param "ww" = width in pixels
		param "hh" = height in pixels */
		Rectangle(double xParameter, double yParameter, double widthParameter, double heightParameter);

		int RotRectsCollision(Rectangle * rr1, Rectangle * rr2);

		/* Checks whether another Rect is within this Rect's bounds. */
		bool contains(int xx, int yy) const;

		/* Returns the x coordinate in the middle of this instance */
		int centeredX();

		/* Returns the y coordinate in the middle of this instance */
		int centeredY();

		double maxXvalue();
		double maxYvalue();

		double getX() const
		{
			return points.front()->x;
		};
		double getY() const
		{
			return points.front()->y;
		};
		double getWidth()
		{
			return width;
		}
		double getHeight()
		{
			return height;
		}
		double getAngle()
		{
			return angle;
		}

		void rotate(double theta)
		{
			double cosa = cos(theta), sina = sin(theta), newx, newy;

			newx = x*cosa - y*sina;
			newy = x*sina + y*cosa;
			x = newx;
			y = newy;
		}

		void applyMotion(double xMotion, double yMotion);

		void updateXYvalues(double xx, double yy);

		void draw();

		/* Creates a new rectangle that is centered on this instance */
		Rectangle centeredRect(int width, int height) const;

		/* Returns true if the other rectangle overlaps this instance */
		bool overlaps(const Rectangle& other) const;

		/* Changes the location and size of this instance according to the
		arguments supplied. */
		void setRect(double xParameter, double yParameter, double widthParameter, double heightParameter);
	};
}

#endif
