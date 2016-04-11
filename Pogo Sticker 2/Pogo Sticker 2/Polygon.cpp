#include "Polygon.h"

using namespace gameEngine;

Polygon::Polygon(float x, float y)
{
	vectors.push_back(new Vector2D(x, y));
}

Polygon::Polygon(float x, float y, float width, float height)
{
	vectors.push_back(new Vector2D(x, y));
	Polygon::addVector(x + width, y);
	Polygon::addVector(x, y + height);
	Polygon::addVector(x + width, y + height);
	boundaryRectangle = new Rect(x, y, width, height);
}

void Polygon::addVector(float x, float y)
{
	vectors.push_back(new Vector2D(x, y));
}

std::list<Vector2D*> Polygon::getVectors() const {
	return vectors;
}
