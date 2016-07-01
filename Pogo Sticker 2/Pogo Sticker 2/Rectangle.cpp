#include "Rectangle.h"
#include "GameEngine.h"

namespace gameEngine {
	Rectangle::Rectangle() {
		x = y = height = width = 0; 
	}

	Rectangle::Rectangle(double xParameter, double yParameter, double widthParameter, double heightParameter)
	{
		Polygon::addPoint(new Pointbase(xParameter, yParameter));
		Polygon::addPoint(new Pointbase(xParameter + widthParameter, yParameter));
		Polygon::addPoint(new Pointbase(xParameter, yParameter + heightParameter));
		Polygon::addPoint(new Pointbase(xParameter + widthParameter, yParameter + heightParameter));
		x = xParameter;
		y = yParameter;
		width = widthParameter;
		height = heightParameter;
		angle = 0;
	}

	bool Rectangle::contains(int xx, int yy) const
	{
		return xx >= points.front()->x && xx <= points.front()->x + width && yy >= points.front()->y && yy <= points.front()->y + height;
	}

	int Rectangle::centeredX()
	{
		return points.front()->x + width / 2;
	}

	int Rectangle::centeredY()
	{
		return points.front()->y + height / 2;
	}

	double Rectangle::maxXvalue()
	{
		return points.back()->x;
	}
	double Rectangle::maxYvalue()
	{
		return points.back()->y;
	}

	Rectangle Rectangle::centeredRect(int width, int height) const {
		return Rectangle(points.front()->x + width / 2 - width / 2, points.front()->y + height / 2 - height / 2, width, height);
	}

	bool Rectangle::overlaps(const Rectangle& other) const {
		int left			= getX();					// left side of the rect
		int other_left		= other.getX();				// other rect's left side
		int right			= getX() + width;				// etc...
		int other_right		= other.getX() + other.width;
		int top				= getY();
		int other_top		= other.getY();
		int bottom			= getY() + height;
		int other_bottom	= other.getY() + other.height;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}

	void Rectangle::setRect(double xParameter, double yParameter, double widthParameter, double heightParameter) {
		x = xParameter;
		y = yParameter;
		width = widthParameter;
		height = heightParameter;
	}

	void Rectangle::applyMotion(double xMotion, double yMotion)
	{
		for (auto it = points.begin(); it != points.end(); it++)
		{
			(*it)->x += xMotion;
			(*it)->y += yMotion;
		}
	}

	void Rectangle::updateXYvalues(double xx, double yy)
	{
		x = xx;
		y = yy;
	}


	void Rectangle::draw()
	{
		glBegin(GL_QUADS);

		// Top Left
		glTexCoord2f(0, 1);
		glVertex2f(points.front()->x, points.front()->y);

		// Top Right
		glTexCoord2f(1, 1);
		glVertex2f(maxXvalue(), points.front()->y);

		// Bottom Right
		glTexCoord2f(1, 0);
		glVertex2f(maxXvalue(), maxYvalue());

		// Bottom Left
		glTexCoord2f(0, 0);
		glVertex2f(points.front()->x, maxYvalue());

		glEnd();
	}
}
