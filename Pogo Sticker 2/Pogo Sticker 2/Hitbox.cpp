#include "Hitbox.h"
#include "GameEngine.h"

namespace gameEngine {

	Hitbox::Hitbox(int x, int y, int w, int h, HitboxEnum::HitboxEnums hitboxEnum) :
		Rect(x, y, w, h)
	{
		hitboxType.setHitboxEnum(hitboxEnum);
	}

	void Hitbox::applyRotation(int centerX, int centerY, int newAngle)
	{
		angle = newAngle;
		// cx, cy - center of square coordinates
		// x, y - coordinates of a corner point of the square
		// theta is the angle of rotation

		// translate point to origin
		float tempX = x - centerX;
		float tempY = y - centerY;

		// now apply rotation
		float rotatedX = tempX*cos(angle) - tempY*sin(angle);
		float rotatedY = tempX*sin(angle) + tempY*cos(angle);

		// translate back
		x = int(rotatedX) + centerX;
		y = int(rotatedY) + centerY;
	}
}
