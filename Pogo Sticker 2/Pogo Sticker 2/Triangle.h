#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Polygon.h"

namespace gameEngine {
	class Triangle : public Polygon {
	public:
		Triangle(Pointbase* pointOne, Pointbase* pointTwo, Pointbase* pointThree);
		virtual ~Triangle()
		{
		}
	protected:

	private:

	};
}

#endif