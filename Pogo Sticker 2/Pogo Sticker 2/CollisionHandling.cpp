#include "CollisionHandling.h"
#include "GameEngine.h"

namespace gameEngine {

	CollisionHandling::CollisionHandling()
	{
	}

	bool CollisionHandling::overlaps(Rect* myRect, Rect* other)
	{
		int left = myRect->x;					// left side of the rect
		int other_left = other->x;				// other rect's left side
		int right = myRect->x + myRect->w;				// etc...
		int other_right = other->x + other->w;
		int top = myRect->y;
		int other_top = other->y;
		int bottom = myRect->y + myRect->h;
		int other_bottom = other->y + other->h;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}

	inline void AddVectors2D(Vector2D * vector1, Vector2D * vector2)
	{
		vector1->x += vector2->x; vector1->y += vector2->y;
	}

	inline void SubVectors2D(Vector2D * vector1, Vector2D * vector2)
	{
		vector1->x -= vector2->x; vector1->y -= vector2->y;
	}

	inline void RotateVector2DClockwise(Vector2D * vector, float angle)
	{
		float t;
		float cosAngle = cos(angle);
		float sinAngle = sin(angle);
		t = vector->x; vector->x = t*cosAngle + vector->y*sinAngle; vector->y = -t*sinAngle + vector->y*cosAngle;
	}
	
	//Copy pasted
	bool CollisionHandling::overlapsWithAngles(Rect* myRect, Rect* other)
	{
		Vector2D A, B,   // vertices of the rotated rr2
			otherCenter,      // center of rr2
			otherBottomLeft, otherTopRight; // vertices of rr2 (bottom-left, top-right)

		float angle = myRect->angle - other->angle; // orientation of rotated rr1
		float cosAngle = cos(angle);           // precalculated trigonometic -
		float sinAngle = sin(angle);           // - values for repeated use

		float t, x, a;      // temporary variables for various uses
		float deltaX;           // deltaX for linear equations
		float ext1, ext2;   // min/max vertical values

		// move rr2 to make rr1 cannonic
		otherCenter = other->centerPoint();
		SubVectors2D(&otherCenter, &myRect->centerPoint());

		// rotate rr2 clockwise by rr2->ang to make rr2 axis-aligned
		RotateVector2DClockwise(&otherCenter, other->angle);

		// calculate vertices of (moved and axis-aligned := 'ma') rr2
		otherBottomLeft = otherTopRight = otherCenter;

		SubVectors2D(&otherBottomLeft, &other->sizePoint());
		AddVectors2D(&otherTopRight, &other->sizePoint());

		// calculate vertices of (rotated := 'r') rr1
		A.x = -myRect->sizePoint().y*sinAngle; B.x = A.x; t = myRect->sizePoint().x*cosAngle; A.x += t; B.x -= t;
		A.y = myRect->sizePoint().y*cosAngle; B.y = A.y; t = myRect->sizePoint().x*sinAngle; A.y += t; B.y -= t;

		t = sinAngle*cosAngle;

		// verify that A is vertical min/max, B is horizontal min/max
		if (t < 0)
		{
			t = A.x; A.x = B.x; B.x = t;
			t = A.y; A.y = B.y; B.y = t;
		}

		// verify that B is horizontal minimum (leftest-vertex)
		if (sinAngle < 0) { B.x = -B.x; B.y = -B.y; }

		// if rr2(ma) isn't in the horizontal range of
		// colliding with rr1(r), collision is impossible
		if (B.x > otherTopRight.x || B.x > -otherBottomLeft.x) return 0;

		// if rr1(r) is axis-aligned, vertical min/max are easy to get
		if (t == 0) { ext1 = A.y; ext2 = -ext1; }
		// else, find vertical min/max in the range [BL.x, TR.x]
		else
		{
			x = otherBottomLeft.x - A.x; a = otherTopRight.x - A.x;
			ext1 = A.y;
			// if the first vertical min/max isn't in (BL.x, TR.x), then
			// find the vertical min/max on BL.x or on TR.x
			if (a*x > 0)
			{
				deltaX = A.x;
				if (x < 0) { deltaX -= B.x; ext1 -= B.y; x = a; }
				else { deltaX += B.x; ext1 += B.y; }
				ext1 *= x; ext1 /= deltaX; ext1 += A.y;
			}

			x = otherBottomLeft.x + A.x; a = otherTopRight.x + A.x;
			ext2 = -A.y;
			// if the second vertical min/max isn't in (BL.x, TR.x), then
			// find the local vertical min/max on BL.x or on TR.x
			if (a*x > 0)
			{
				deltaX = -A.x;
				if (x < 0) { deltaX -= B.x; ext2 -= B.y; x = a; }
				else { deltaX += B.x; ext2 += B.y; }
				ext2 *= x; ext2 /= deltaX; ext2 -= A.y;
			}
		}

		// check whether rr2(ma) is in the vertical range of colliding with rr1(r)
		// (for the horizontal range of rr2)
		return !((ext1 < otherBottomLeft.y && ext2 < otherBottomLeft.y) ||
			(ext1 > otherTopRight.y && ext2 > otherTopRight.y));
	}
}