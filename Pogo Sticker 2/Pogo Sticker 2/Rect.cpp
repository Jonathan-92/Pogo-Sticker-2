#include "Rect.h"
#include "GameEngine.h"

namespace gameEngine {
	Rect::Rect() {
		x = y = height = width = 0; 
	}

	Rect::Rect(double xParameter, double yParameter, double widthParameter, double heightParameter)
	{
		x = xParameter; 
		y = yParameter;
		width = widthParameter;
		height = heightParameter;
		angle = 0;
	}

	bool Rect::contains(int xx, int yy) const 
	{
		return xx >= x && xx <= x + width && yy >= y && yy <= y + height;
	}

	int Rect::centeredX() 
	{
		return x + width / 2;
	}

	int Rect::centeredY() 
	{
		return y + height / 2;
	}

	double Rect::maxXvalue()
	{
		return x + width;
	}
	double Rect::maxYvalue()
	{
		return y + height;
	}

	Vector2D Rect::centerPoint()
	{
		return Vector2D(x + width / 2, y + height / 2);
	}

	Rect Rect::centeredRect(int width, int height) const {
		return Rect(x + width / 2 - width / 2, y + height / 2 - height / 2, width, height);
	}

	bool Rect::overlaps(const Rect& other) const {
		int left			= x;					// left side of the rect
		int other_left		= other.x;				// other rect's left side
		int right			= x + width;				// etc...
		int other_right		= other.x + other.width;
		int top				= y;
		int other_top		= other.y;
		int bottom			= y + height;
		int other_bottom	= other.y + other.height;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}

	void Rect::setRect(double xParameter, double yParameter, double widthParameter, double heightParameter) {
		x = xParameter;
		y = yParameter;
		width = widthParameter;
		height = heightParameter;
	}

	void Rect::applyMotion(double xMotion, double yMotion)
	{
		x += xMotion;
		y += yMotion;
	}

	void Rect::updateXYvalues(double xx, double yy)
	{
		x = xx;
		y = yy;
	}


	void Rect::draw()
	{
		glBegin(GL_QUADS);

		// Top Left
		glTexCoord2f(0, 1);
		glVertex2f(x, y);

		// Top Right
		glTexCoord2f(1, 1);
		glVertex2f(maxXvalue(), y);

		// Bottom Right
		glTexCoord2f(1, 0);
		glVertex2f(maxXvalue(), maxYvalue());

		// Bottom Left
		glTexCoord2f(0, 0);
		glVertex2f(x, maxYvalue());

		glEnd();
	}
}