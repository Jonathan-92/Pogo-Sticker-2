#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace gameEngine {

	struct Vector2D {
	public:
		Vector2D();
		Vector2D(float xx, float yy);
		float x, y;
	};
}

#endif