#include "Pointbase.h"

Pointbase::Pointbase(const Pointbase& pb)
{
	this->id = pb.id;
	this->x = pb.x;
	this->y = pb.y;
	this->type = pb.type;
	this->left = pb.left;
}

//----------------------------------------------------------------------------
//operator ( ==, >, < and != ) overloading for pointbase class
//----------------------------------------------------------------------------
bool operator==(const Pointbase& pa, const Pointbase& pb)
{
	return (pa.x == pb.x && pa.y == pb.y);
}

//----------------------------------------------------------------------------
bool operator>(const Pointbase& pa, const Pointbase& pb)
{
	return((pa.y > pb.y) || ((pa.y == pb.y) && (pa.x < pb.x)));
}

//----------------------------------------------------------------------------
bool operator<(const Pointbase& pa, const Pointbase& pb)
{
	return((pa.y < pb.y) || ((pa.y == pb.y) && (pa.x > pb.x)));
}

//----------------------------------------------------------------------------
bool operator!=(const Pointbase& pa, const Pointbase& pb)
{
	return !(pa.x == pb.x && pa.y == pb.y);
}