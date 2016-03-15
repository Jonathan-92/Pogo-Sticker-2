#ifndef LINEBASE_H
#define LINEBASE_H
#include "defs.h"
#include "splay.h"

class Linebase
{
public:
	//constructors and destructor	  
	Linebase();
	Linebase(Pointbase* ep1, Pointbase* ep2, Type type);
	Linebase(const Linebase& line);
	~Linebase() {};

	unsigned int id() const { return _id; }

	//two end points 
	Pointbase*   endPoint(int i) const { return _endp[i]; }
	Type         type() const { return _type; }
	double       keyValue() const { return _key; }
	void         setKeyValue(double y);
	//slightly increased the key to avoid duplicated key for searching tree. 
	void         increaseKeyValue(const double diff) { _key += diff; }
	//reverse a directed line segment; reversable only for inserted diagonals
	void         reverse();

	//set and return helper of a directed line segment;
	void         setHelper(unsigned int i) { _helper = i; }
	unsigned int helper() { return _helper; }

	//operator overloading             
	friend ostream &operator<<(ostream &os, const Linebase& line);

protected:
	unsigned int _id;           //id of a line segment;
	Pointbase*   _endp[2];      //two end points;

	Type         _type;         //type of a line segement, input/insert
	double       _key;          //key of a line segment for splay tree searching
	unsigned int _helper;       //helper of a line segemnt
};

#endif
