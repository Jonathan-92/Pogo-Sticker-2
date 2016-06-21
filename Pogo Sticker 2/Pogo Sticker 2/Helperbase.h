#ifndef HELPERBASE_H
#define HELPERBASE_H
#include <math.h>

//base class for points;
class Helperbase
{
public:
	enum Type { UNKNOWN, INPUTS, INSERT, START, END, MERGE, SPLIT, REGULAR_UP, REGULAR_DOWN };
};
#endif