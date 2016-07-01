#ifndef POLYGON_H
#define POLYGON_H
#include "Pointbase.h"
#include <vector>

//
class Polygon {
protected:
	~Polygon()
	{
	}
	std::vector<Pointbase*> points; //all vertices
public:
	Polygon();
	Polygon(float x, float y);
	virtual void addPoint(Pointbase* point);
	std::vector<Pointbase*> getPoints() const;
};
#endif
