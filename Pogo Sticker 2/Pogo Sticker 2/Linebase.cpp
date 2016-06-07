#include "Linebase.h"
#include "Pointbase.h"

long Linebase::l_id = 0;
long Linebase::p_id = 0;
//----------------------------------------------------------------------------
//Linebase construct
//----------------------------------------------------------------------------
Linebase::Linebase() :_type(UNKNOWN)
{
	for (int i = 0; i < 2; i++) _endp[i] = 0;
	_id = 0;
}

//-----------------------------------------------------------------------------
//Linebase construct
//-----------------------------------------------------------------------------
Linebase::Linebase(Pointbase* sp, Pointbase* ep, Type type) :_type(type)
{
	_endp[0] = sp;
	_endp[1] = ep;
	//_key=_endp[0]->x < _endp[1]->x ? _endp[0]->x:_endp[1]->x;
	_id = ++l_id;
}

//----------------------------------------------------------------------------
//copy constructor
//----------------------------------------------------------------------------
Linebase::Linebase(const Linebase& line)
{
	this->_id = line._id;
	this->_endp[0] = line._endp[0];
	this->_endp[1] = line._endp[1];
	this->_key = line._key;
	this->_helper = line._helper;
}


//----------------------------------------------------------------------------
//reverse a directed line segment, reverseable only for insert diagonals
//----------------------------------------------------------------------------
void Linebase::reverse()
{
	assert(_type == INSERT);
	Pointbase* tmp = _endp[0];
	_endp[0] = _endp[1];
	_endp[1] = tmp;
}

void Linebase::setKeyValue(double y)
{
	if (_endp[1]->y == _endp[0]->y)
		_key = _endp[0]->x < _endp[1]->x ? _endp[0]->x : _endp[1]->x;
	else    _key = (y - _endp[0]->y) * (_endp[1]->x - _endp[0]->x) / (_endp[1]->y - _endp[0]->y) + _endp[0]->x;
}
