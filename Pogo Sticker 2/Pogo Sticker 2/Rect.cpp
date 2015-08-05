#include "Rect.h"
#include <math.h>

namespace gameEngine {
	Rect::Rect() {
		x = y = h = w = 0; 
	}

	Rect::Rect(int xx, int yy, int ww, int hh) {
		x = xx; y = yy; w = ww; h = hh;
		angle = 0;
	}

	bool Rect::contains(int xx, int yy) const {
		return xx >= x && xx <= x + w && yy >= y && yy <= y + h;
	}

	int Rect::centeredX() {
		return x + w / 2;
	}

	int Rect::centeredY() {
		return y + h / 2;
	}

	Rect Rect::centeredRect(int width, int height) const {
		return Rect(x + w / 2 - width / 2, y + h / 2 - height / 2, width, height);
	}

	bool Rect::overlaps(const Rect& other) const {
		int left			= x;					// left side of the rect
		int other_left		= other.x;				// other rect's left side
		int right			= x + w;				// etc...
		int other_right		= other.x + other.w;
		int top				= y;
		int other_top		= other.y;
		int bottom			= y + h;
		int other_bottom	= other.y + other.h;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}

	void Rect::setRect(int xx, int yy, int ww, int hh) {
		x = xx;
		y = yy;
		w = ww;
		h = hh;
	}

	/* COPY PASTAERINO */ 
	inline void RotateVector2DClockwise(Rect* v, float ang)
	{
		float t,
			cosa = cos(ang),
			sina = sin(ang);
		t = v->x; v->x = t*cosa + v->y*sina; v->y = -t*sina + v->y*cosa;
	}

	struct _Vector2D {
		float x, y;
	};

	inline void AddVectors2D(_Vector2D * v1, _Vector2D * v2)
	{
		v1->x += v2->x; v1->y += v2->y;
	}

	inline void SubVectors2D(_Vector2D * v1, _Vector2D * v2)
	{
		v1->x -= v2->x; v1->y -= v2->y;
	}

	// Rotated Rectangles Collision Detection, Oren Becker, 2001
	int Rect::RotRectsCollision(Rect * rr1, Rect * rr2)
	{
		_Vector2D A, B,   // vertices of the rotated rr2
			C,      // center of rr2
			BL, TR; // vertices of rr2 (bottom-left, top-right)

		float ang = rr1->angle - rr2->angle, // orientation of rotated rr1
			cosa = cos(ang),           // precalculated trigonometic -
			sina = sin(ang);           // - values for repeated use

		float t, x, a;      // temporary variables for various uses
		float dx;           // deltaX for linear equations
		float ext1, ext2;   // min/max vertical values

		// move rr2 to make rr1 cannonic
		
		_Vector2D rr2C = { rr2->centeredX(), rr2->centeredY() };
		C = rr2C;
		_Vector2D rr1C = { rr1->centeredX(), rr1->centeredY() };
		SubVectors2D(&C, &rr1C);

		// rotate rr2 clockwise by rr2->ang to make rr2 axis-aligned
		RotateVector2DClockwise(rr2, rr2->angle);

		// calculate vertices of (moved and axis-aligned := 'ma') rr2
		BL = TR = C;
		_Vector2D rr2S = { rr2->w, rr2->h };
		SubVectors2D(&BL, &rr2S);
		AddVectors2D(&TR, &rr2S);

		_Vector2D rr1S = { rr1->w, rr1->h };
		// calculate vertices of (rotated := 'r') rr1
		A.x = -rr1->h*sina; B.x = A.x; t = rr1->w*cosa; A.x += t; B.x -= t;
		A.y = rr1->h*cosa; B.y = A.y; t = rr1->w*sina; A.y += t; B.y -= t;

		t = sina*cosa;

		// verify that A is vertical min/max, B is horizontal min/max
		if (t < 0)
		{
			t = A.x; A.x = B.x; B.x = t;
			t = A.y; A.y = B.y; B.y = t;
		}

		// verify that B is horizontal minimum (leftest-vertex)
		if (sina < 0) { B.x = -B.x; B.y = -B.y; }

		// if rr2(ma) isn't in the horizontal range of
		// colliding with rr1(r), collision is impossible
		if (B.x > TR.x || B.x > -BL.x) return 0;

		// if rr1(r) is axis-aligned, vertical min/max are easy to get
		if (t == 0) { ext1 = A.y; ext2 = -ext1; }
		// else, find vertical min/max in the range [BL.x, TR.x]
		else
		{
			x = BL.x - A.x; a = TR.x - A.x;
			ext1 = A.y;
			// if the first vertical min/max isn't in (BL.x, TR.x), then
			// find the vertical min/max on BL.x or on TR.x
			if (a*x > 0)
			{
				dx = A.x;
				if (x < 0) { dx -= B.x; ext1 -= B.y; x = a; }
				else       { dx += B.x; ext1 += B.y; }
				ext1 *= x; ext1 /= dx; ext1 += A.y;
			}

			x = BL.x + A.x; a = TR.x + A.x;
			ext2 = -A.y;
			// if the second vertical min/max isn't in (BL.x, TR.x), then
			// find the local vertical min/max on BL.x or on TR.x
			if (a*x > 0)
			{
				dx = -A.x;
				if (x < 0) { dx -= B.x; ext2 -= B.y; x = a; }
				else       { dx += B.x; ext2 += B.y; }
				ext2 *= x; ext2 /= dx; ext2 -= A.y;
			}
		}

		// check whether rr2(ma) is in the vertical range of colliding with rr1(r)
		// (for the horizontal range of rr2)
		return !((ext1 < BL.y && ext2 < BL.y) ||
			(ext1 > TR.y && ext2 > TR.y));
	}
}