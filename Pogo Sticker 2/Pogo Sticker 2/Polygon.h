#ifndef POLYGON_H
#define POLYGON_H
#include "Pointbase.h"
#include "Rect.h"

//
class Polygon {
protected:
	~Polygon()
	{
	}
	PointbaseMap points; //all vertices
public:
	Polygon();
	Polygon(float x, float y);
	Polygon(float x, float y, float width, float height);
	gameEngine::Rect* boundaryRectangle;
	virtual void addPoint(int id, float x, float y);
	PointbaseMap getPoints() const;
};
#endif
