#include "Vector2D.h"

namespace gameEngine {
	Vector2D::Vector2D() {
		x = y = 0;
	}

	Vector2D::Vector2D(float xx, float yy) {
		x = xx; y = yy;
	}
}