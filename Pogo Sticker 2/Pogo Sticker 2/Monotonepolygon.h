#pragma once
#ifndef MONOTONEPOLYGON_H
#define MONOTONEPOLYGON_H
#include "Polygon.h"

namespace gameEngine {
	class Monotonepolygon : public Polygon {
	public:
		Monotonepolygon();
		Monotonepolygon(Pointbase* pointOne, Pointbase* pointTwo, Pointbase* pointThree);
		~Monotonepolygon()
		{
		}
	protected:
	private:

	};
}

#endif