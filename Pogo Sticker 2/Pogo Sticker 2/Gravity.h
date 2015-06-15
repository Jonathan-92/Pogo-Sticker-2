#ifndef GRAVITY_H
#define GRAVITY_H

namespace gameEngine {

	class Gravity
	{
	public:
		Gravity(float force, float mass, float acceleration);
		~Gravity();
		float applyGravity(float mVelY, float mPosY);
		float jump(float force);
		void resetTime();
	protected:

	private:
		float force;
		float mass;	
		float acceleration;
		float time;
		float timeStep;
	};

}
#endif