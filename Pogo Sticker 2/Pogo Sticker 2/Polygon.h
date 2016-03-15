#ifndef POLYGON_H
#define POLYGON_H
#include "Vector2D.h"
#include <list>
//
class Polygon {
protected:
	~Polygon()
	{
	}
	std::list<gameEngine::Vector2D*> vectors;
public:
	Polygon(float x, float y);
	virtual void addVector(float x, float y);
	std::list<gameEngine::Vector2D*> getVectors() const;
};
#endif
