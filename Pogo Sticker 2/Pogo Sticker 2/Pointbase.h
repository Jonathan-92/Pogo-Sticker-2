#ifndef POINTBASE_H
#define POINTBASE_H
#include "defs.h"
#include "splay.h"

//base class for points;
class Pointbase
{
public:
	//constructors and destructor	   
	Pointbase() {}
	Pointbase(const Pointbase& pb);

	Pointbase(double xx, double yy)
		:id(0), x(xx), y(yy), type(UNKNOWN) { }

	Pointbase(int idd, double xx, double yy)
		:id(idd), x(xx), y(yy), type(UNKNOWN) { }

	Pointbase(double xx, double yy, Type ttype)
		:id(0), x(xx), y(yy), type(ttype) { }

	Pointbase(int idd, double xx, double yy, Type ttype)
		:id(idd), x(xx), y(yy), type(ttype) { }

	//rotate a point by angle theta, not used;
	void rotate(double theta)
	{
		double cosa = cos(theta), sina = sin(theta), newx, newy;

		newx = x*cosa - y*sina;
		newy = x*sina + y*cosa;
		x = newx;
		y = newy;
	}

	//operator overloading
	friend  bool operator==(const Pointbase&, const Pointbase&);
	friend  bool operator>(const Pointbase&, const Pointbase&);
	friend  bool operator<(const Pointbase&, const Pointbase&);
	friend  bool operator!=(const Pointbase&, const Pointbase&);

	//public data
	unsigned int    id;              //id of point;
	double          x, y;            //coordinates;
	Type            type;            //type of points;
	bool            left;            //left chain or not;

};
#endif
