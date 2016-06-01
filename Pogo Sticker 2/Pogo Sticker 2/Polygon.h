#ifndef POLYGON_H
#define POLYGON_H
#include "Vector2D.h"
#include <list>
#include "Rect.h"
#include "Pointbase.h"

//
class Polygon {
protected:
	~Polygon()
	{
	}
	PointbaseMap points; //all vertices
public:
	Polygon(float x, float y);
	Polygon(float x, float y, float width, float height);
	gameEngine::Rect* boundaryRectangle;
	virtual void addPoint(int id, float x, float y);
	PointbaseMap getPoints() const;
};
#endif
