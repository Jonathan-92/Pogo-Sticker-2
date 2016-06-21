#include "Triangle.h"

namespace gameEngine {
	Triangle::Triangle(Pointbase* pointOne, Pointbase* pointTwo, Pointbase* pointThree)
	{
		Polygon::addPoint(pointOne);
		Polygon::addPoint(pointTwo);
		Polygon::addPoint(pointThree);
	}
}