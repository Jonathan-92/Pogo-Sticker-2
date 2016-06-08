#include "Polygon.h"
#include "Rect.h"

using namespace gameEngine;

Polygon::Polygon()
{

}

Polygon::Polygon(float x, float y)
{
	points[0] = new Pointbase(x, y);
}

Polygon::Polygon(float x, float y, float width, float height)
{
	points[0] = new Pointbase(x, y);
	points[1] = new Pointbase(x + width, y);
	points[2] = new Pointbase(x, y + height);
	points[3] = new Pointbase(x + width, y + height);
	boundaryRectangle = new Rect(x, y, width, height);
}

void Polygon::addPoint(int id, float x, float y) 
{
	points[id] = new Pointbase(x, y);
}

PointbaseMap Polygon::getPoints() const {
	return points;
}
