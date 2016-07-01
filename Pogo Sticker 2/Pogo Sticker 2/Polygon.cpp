#include "Polygon.h"
#include "Rectangle.h"

using namespace gameEngine;

Polygon::Polygon()
{

}

Polygon::Polygon(float x, float y)
{
	points.push_back(new Pointbase(x, y));
}

void Polygon::addPoint(Pointbase* point)
{
	points.push_back(point);
}

std::vector<Pointbase*> Polygon::getPoints() const {
	return points;
}
