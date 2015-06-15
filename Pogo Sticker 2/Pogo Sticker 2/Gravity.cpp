#include "Gravity.h"
#include "GameEngine.h"

namespace gameEngine {
	Gravity::Gravity(float f, float m, float a)
	{
		//Initialize the offsets
		force = f;
		mass = m;
		acceleration = a;
		time = 0;
		timeStep = 0;
	}

	Gravity::~Gravity(void)
	{
	}

	float Gravity::applyGravity(float mVelY, float mPosY)
	{
		++timeStep;
		time += timeStep;
		mPosY += timeStep * (force + timeStep * acceleration / 2);
		force += timeStep * acceleration;
		// add other forces in for taste - usual suspects include air resistence
		// proportional to the square of velocity, against the direction of movement. 
		// this has the effect of capping max speed.

		return mPosY;
	}

	float Gravity::jump(float force)
	{
		float mVelY = force;
		return mVelY;
	}

	void Gravity::resetTime()
	{
		time = 0;
		timeStep = 0;
	}
}