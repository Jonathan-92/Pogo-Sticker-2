#include "Rectangle.h"

using namespace gameEngine;

Rectangle::Rectangle(float xx, float yy, float w, float h) : Polygon(xx, yy)
{
	x = xx;
	y = yy;
	width = w;
	height = h;
	
	vectors.push_back(new Vector2D(x + w, y));
	vectors.push_back(new Vector2D(x, y + h));
	vectors.push_back(new Vector2D(x + w, y + h));
}