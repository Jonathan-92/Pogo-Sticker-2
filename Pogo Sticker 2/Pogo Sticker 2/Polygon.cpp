#include "Polygon.h"

using namespace gameEngine;

Polygon::Polygon(float x, float y)
{
	vectors.push_back(new Vector2D(x, y));
}

void Polygon::addVector(float x, float y)
{
	vectors.push_back(new Vector2D(x, y));
}

std::list<Vector2D*> Polygon::getVectors() const {
	return vectors;
}
