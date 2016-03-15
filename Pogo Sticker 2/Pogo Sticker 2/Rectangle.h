#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Polygon.h"

namespace gameEngine {
	class Rectangle : public Polygon {
	public:
		Rectangle(float xx, float yy, float width, float height);
		float x, y, width, height;
	private:
	};
}

#endif